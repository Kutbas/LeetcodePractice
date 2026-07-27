#include <mutex>
#include <vector>
#include <algorithm>
#include <climits>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <iostream>
#include <regex>
#include <map>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
public:
    // 1
    int maxSubArray(vector<int> &nums)
    {
        int n = nums.size(), ret = INT_MIN;
        vector<int> dp(n + 1);

        for (int i = 1; i <= n; i++)
        {
            dp[i] = max(dp[i - 1] + nums[i - 1], nums[i - 1]);
            ret = max(ret, dp[i]);
        }

        return ret;
    }

    // 2
    vector<vector<int>> levelOrder(TreeNode *root)
    {
        vector<vector<int>> ret;
        if (root == nullptr)
            return ret;

        queue<TreeNode *> q;
        q.push(root);

        while (q.size())
        {
            int sz = q.size();
            vector<int> tmp;
            while (sz--)
            {
                auto t = q.front();
                q.pop();
                tmp.push_back(t->val);

                if (t->left)
                    q.push(t->left);
                if (t->right)
                    q.push(t->right);
            }

            ret.push_back(tmp);
        }

        return ret;
    }

    // 3
    int removeDuplicates(vector<int> &nums)
    {
        int n = nums.size(), slow = 1, fast = 1;

        while (fast < n)
        {
            if (nums[fast - 1] != nums[fast])
                nums[slow++] = nums[fast];
            fast++;
        }

        return slow;
    }

    // 4
    string ret;
    string tree2str(TreeNode *root)
    {
        dfs(root);
        return ret;
    }

    void dfs(TreeNode *root)
    {
        if (root == nullptr)
            return;

        ret += to_string(root->val);

        if (root->left || root->right)
        {
            ret += "(";
            dfs(root->left);
            ret += ")";
        }

        if (root->right)
        {
            ret += "(";
            dfs(root->right);
            ret += ")";
        }
    }

    // 5
    string addStrings(string num1, string num2)
    {
        int m = num1.size(), n = num2.size();
        int t = 0, cur1 = m - 1, cur2 = n - 1;

        string ret;
        while (t || cur1 >= 0 || cur2 >= 0)
        {
            if (cur1 >= 0)
                t += num1[cur1--] - '0';
            if (cur2 >= 0)
                t += num2[cur2--] - '0';

            ret += to_string(t % 10);
            t /= 10;
        }

        reverse(ret.begin(), ret.end());
        return ret[0] == '0' ? "0" : ret;
    }

    // 7
    int minimumDeleteSum(string s1, string s2)
    {
        int m = s1.size(), n = s2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        // s1=" "+s1,s2=" "+s2;

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);

                if (s1[i - 1] == s2[j - 1])
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + s1[i - 1]);
            }

        int sum = 0;
        for (char ch : s1)
            sum += ch;
        for (char ch : s2)
            sum += ch;

        return sum - 2 * dp[m][n];
    }
};

// 6
struct RowDotFunction
{
    const float *_matrix;
    const float *_vec;
    int _cols;

    RowDotFunction(const float *matrix, const float *vec, int cols) : _matrix(matrix), _vec(vec), _cols(cols)
    {
    }

    __host__ __device__ float operator()(int row)
    {
        float sum = 0.0f;
        const float *row_ptr = _matrix + row * _cols;

        for (int i = 0; i < _cols; i++)
            sum += row_ptr[i] * _vec[i];

        return sum;
    }
};

std::vector<float> matrix_dot_vector(const std::vector<std::vector<float>> &matrix, const std::vector<float> &vec)
{
    int rows = matrix.size();
    if (rows == 0)
        return {-1};
    int cols = matrix[0].size();
    if (cols != vec.size())
        return {-1};

    vector<float> flat_matrix(rows * cols);
    for (int i = 0; i < rows; i++)
    {
        if (matrix[i].size() != cols)
            return {-1};

        copy(matrix[i].begin(), matrix[i].end(), flat_matrix.begin() + i * cols);
    }

    thrust::device_vector<float> d_matrix(flat_matrix.begin(), flat_matrix.end());
    thrust::device_vector<float> d_vec(vec.begin(), vec.end());
    thrust::device_vector<float> d_result(rows);

    const float *d_matrix_ptr = thrust::raw_pointer_cast(d_matrix.data());
    const float *d_vec_ptr = thrust::raw_pointer_cast(d_vec.data());

    thrust::transform(thrust::counting_iterator<int>(0), thrust::counting_iterator<int>(rows), d_result.begin(), RowDotFunction(d_matrix_ptr, d_vec_ptr, cols));

    vector<float> result(rows);

    thrust::copy(d_result.begin(), d_result.end(), result.begin());

    return result;
}