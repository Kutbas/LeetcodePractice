#include <cuda_runtime.h>
#include <iostream>
#include <vector>

using namespace std;

struct RowDotFunctor
{
    const float *matrix; // 接收 GPU 端的裸指针
    const float *vec;    // 接收 GPU 端的裸指针
    int cols;            // 矩阵列数

    // 构造函数：在 CPU 端初始化，然后这个结构体会作为参数被复制到 GPU 显存中
    RowDotFunctor(
        const float *matrix_ptr,
        const float *vec_ptr,
        int cols_count)
        : matrix(matrix_ptr),
          vec(vec_ptr),
          cols(cols_count)
    {
    }

    // __host__ __device__ 告诉编译器：这个重载的括号运算符既可以在 CPU 运行，也可以在 GPU 运行
    // 每一个 GPU 线程都会调用一次这个函数，传入的 `row` 参数就相当于传统 CUDA 里的全局线程 ID
    __host__ __device__ float operator()(int row) const
    {
        float sum = 0.0f;

        // 计算当前线程负责的这一行在 1D 数组中的起始地址
        const float *row_ptr = matrix + row * cols;

        // 标志性的矩阵-向量点积内循环
        for (int col = 0; col < cols; ++col)
        {
            sum += row_ptr[col] * vec[col];
        }

        // 返回的值会自动被 Thrust 收集并写入到目标数组对应的 row 位置
        return sum;
    }
};

// Host 函数（签名保持不变，保持严格的传引用和原返回值类型）
std::vector<float> matrix_dot_vector(
    const std::vector<std::vector<float>> &matrix,
    const std::vector<float> &vec)
{
    // ---------- 1. 基本校验 ----------
    int rows = static_cast<int>(matrix.size());
    if (rows == 0)
        return {-1};

    int cols = static_cast<int>(matrix[0].size());
    if (vec.size() != static_cast<size_t>(cols))
        return {-1};

    // ---------- 2. 矩阵"拍扁" (2D vector 转 1D vector) ----------
    std::vector<float> flat_matrix(rows * cols);
    for (int i = 0; i < rows; ++i)
    {
        if (matrix[i].size() != static_cast<size_t>(cols))
            return {-1};

        // 使用标准库的高效拷贝
        std::copy(
            matrix[i].begin(),
            matrix[i].end(),
            flat_matrix.begin() + i * cols);
    }

    // 拷贝矩阵到显存
    thrust::device_vector<float> d_matrix(
        flat_matrix.begin(),
        flat_matrix.end());

    // 拷贝向量到显存
    thrust::device_vector<float> d_vec(
        vec.begin(),
        vec.end());

    // 在显存中开辟结果数组的空间（相当于 cudaMalloc 了 rows * sizeof(float)）
    thrust::device_vector<float> d_result(rows);

    // ---------- 4. 获取原始指针 ----------
    // 因为我们的 RowDotFunctor 内部使用的是传统的 C 风格指针 (float*)，
    // 所以需要用 raw_pointer_cast 把 Thrust 的高级对象解包成 GPU 上的裸指针。
    const float *matrix_ptr =
        thrust::raw_pointer_cast(d_matrix.data());

    const float *vec_ptr =
        thrust::raw_pointer_cast(d_vec.data());

    // ---------- 5. GPU 并行计算 (替代传统 <<<blocks, threads>>>) ----------
    // thrust::transform 类似于标准库的 std::transform，但它是在 GPU 上开挂并行版。
    //
    // 关键魔法点：thrust::counting_iterator<int>(0)
    // 它是一个虚拟迭代器，不占内存。它的作用是向 transform 算法提供一个 0, 1, 2, ..., rows-1 的数字序列。
    // transform 会把这些数字（即行号）逐个传给 RowDotFunctor 的 operator()(int row)。

    // 本质上：Thrust 在底层自动帮你计算了最优的 Block 和 Thread 数量并启动了 Kernel。
    thrust::transform(
        thrust::counting_iterator<int>(0),    // 输入序列起始：0
        thrust::counting_iterator<int>(rows), // 输入序列结束：rows (不含)
        d_result.begin(),                     // 结果输出到这里
        RowDotFunctor(                        // 传入我们的 GPU 算子
            matrix_ptr,
            vec_ptr,
            cols));

    // ---------- 6. Device -> Host 内存拷贝 ----------
    std::vector<float> result(rows);

    // 使用 thrust::copy 把显存中算好的结果倒回 CPU 的 result 中
    // 底层等同于 cudaMemcpy(..., D2H)，并且会自动隐式同步，不需要再手写 cudaDeviceSynchronize()
    thrust::copy(
        d_result.begin(),
        d_result.end(),
        result.begin());

    // 返回最终结果，C++11 移动语义生效，零拷贝开销
    return result;
}

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution
{
public:
    // 1
    void reorderList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return;

        ListNode *slow = head, *fast = head;
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode *head2 = new ListNode(0);
        ListNode *cur = slow->next;
        slow->next = nullptr;

        while (cur)
        {
            ListNode *next = cur->next;
            cur->next = head2->next;
            head2->next = cur;
            cur = next;
        }

        ListNode *ret = new ListNode(0);
        ListNode *prev = ret, *cur1 = head, *cur2 = head2->next;
        while (cur1 || cur2)
        {
            if (cur1)
            {
                prev->next = cur1;
                prev = prev->next;
                cur1 = cur1->next;
            }
            if (cur2)
            {
                prev->next = cur2;
                prev = prev->next;
                cur2 = cur2->next;
            }
        }

        prev = ret->next;
        delete ret, head2;
    }

    // 2
    int maxProfit(vector<int> &prices)
    {
        int n = prices.size();
        vector<int> a(n), b(n), c(n);

        a[0] = -prices[0];

        for (int i = 1; i < n; i++)
        {
            a[i] = max(a[i - 1], b[i - 1] - prices[i]);
            b[i] = max(b[i - 1], c[i - 1]);
            c[i] = a[i - 1] + prices[i];
        }

        return max(b[n - 1], c[n - 1]);
    }

    // 3
    int maxProfit(vector<int> &prices, int fee)
    {
        int n = prices.size();
        vector<int> f(n), g(n);

        f[0] = -prices[0];
        for (int i = 1; i < n; i++)
        {
            f[i] = max(f[i - 1], g[i - 1] - prices[i]);
            g[i] = max(g[i - 1], f[i - 1] + prices[i] - fee);
        }

        return g[n - 1];
    }

    // 4
    bool wordBreak(string s, vector<string> &wordDict)
    {
        unordered_set<string> hash(wordDict.begin(), wordDict.end());

        int n = s.size();
        s = " " + s;
        vector<bool> dp(n + 1);
        dp[0] = true;

        for (int i = 1; i <= n; i++)
            for (int j = i; j >= 1; j--)
            {
                if (dp[j - 1] && hash.count(s.substr(j, i - j + 1)))
                {
                    dp[i] = true;
                    break;
                }
            }

        return dp[n];
    }

    // 5
    int findSubstringInWraproundString(string s)
    {
        int n = s.size();
        vector<int> dp(n, 1);

        for (int i = 1; i < n; i++)
        {
            if (s[i - 1] + 1 == s[i] || (s[i - 1] == 'z' && s[i] == 'a'))
                dp[i] += dp[i - 1];
        }

        int hash[26] = {0};
        for (int i = 0; i < n; i++)
        {
            int index = s[i] - 'a';
            hash[index] = max(hash[index], dp[i]);
        }

        int ret = 0;
        for (int i = 0; i < 26; i++)
            ret += hash[i];

        return ret;
    }

    // 6
    int minCut(string s)
    {
        int n = s.size();
        vector<vector<bool>> isPal(n, vector<bool>(n));

        for (int i = n - 1; i >= 0; i--)
            for (int j = i; j < n; j++)
                if (s[i] == s[j])
                    isPal[i][j] = j - i + 1 > 3 ? isPal[i + 1][j - 1] : true;

        vector<int> dp(n, 0x3f3f3f);
        for (int i = 0; i < n; i++)
        {
            if (isPal[0][i])
                dp[i] = 0;
            else
            {
                for (int j = 1; j <= i; j++)
                {
                    if (isPal[j][i])
                        dp[i] = min(dp[i], dp[j - 1] + 1);
                }
            }
        }

        return dp[n - 1];
    }

    // 7
    int FindGreatestSumOfSubArray(vector<int> &array)
    {
        int n = array.size(), ret = INT_MIN;
        vector<int> dp(n + 1);

        for (int i = 1; i <= n; i++)
        {
            dp[i] = max(dp[i - 1] + array[i - 1], array[i - 1]);
            ret = max(ret, dp[i]);
        }

        return ret;
    }

    // 8
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder)
    {
        int posti = postorder.size() - 1;
        return _buildTree(inorder, postorder, posti, 0, inorder.size() - 1);
    }

    TreeNode *_buildTree(vector<int> &inorder, vector<int> &postorder, int &posti, int inBegin, int inEnd)
    {
        if (inBegin > inEnd)
            return nullptr;

        TreeNode *root = new TreeNode(postorder[posti]);

        int rooti = inBegin;
        while (rooti <= inEnd)
            if (inorder[rooti] == postorder[posti])
                break;
            else
                rooti++;

        --posti;
        root->right = _buildTree(inorder, postorder, posti, rooti + 1, inEnd);
        root->left = _buildTree(inorder, postorder, posti, inBegin, rooti - 1);

        return root;
    }
};