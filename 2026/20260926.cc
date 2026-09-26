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
#include <sstream>
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
    string largestNumber(vector<int> &nums)
    {
        vector<string> strs;
        for (auto num : nums)
            strs.push_back(to_string(num));

        sort(strs.begin(), strs.end(), [&](const string &s1, const string &s2)
             { return s1 + s2 > s2 + s1; });

        string ret;
        for (auto s : strs)
            ret += s;

        return ret[0] == '0' ? "0" : ret;
    }

    // 2
    vector<int> diStringMatch(string s)
    {
        vector<int> ret;
        int n = s.size(), left = 0, right = n;

        for (int i = 0; i <= n; i++)
        {
            if (s[i] == 'I')
                ret.push_back(left++);
            else
                ret.push_back(right--);
        }

        return ret;
    }

    // 3
    int maxProfit(int k, vector<int> &prices)
    {
        const int INF = 0x3f3f3f;
        int n = prices.size(), ret = 0;
        k = min(k, n / 2);
        vector<vector<int>> f(n, vector<int>(k + 1, -INF));
        auto g = f;
        f[0][0] = -prices[0];
        g[0][0] = 0;

        for (int i = 1; i < n; i++)
            for (int j = 0; j <= k; j++)
            {
                f[i][j] = max(f[i - 1][j], g[i - 1][j] - prices[i]);
                g[i][j] = g[i - 1][j];
                if (j >= 1)
                    g[i][j] = max(g[i][j], f[i - 1][j - 1] + prices[i]);
                ret = max(ret, g[i][j]);
            }

        return ret;
    }

    // 4
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

    // 5
    int maxTurbulenceSize(vector<int> &arr)
    {
        int n = arr.size(), ret = 1;
        vector<int> f(n, 1);
        auto g = f;

        for (int i = 1; i < n; i++)
        {
            if (arr[i] > arr[i - 1])
                f[i] = g[i - 1] + 1;
            else if (arr[i] < arr[i - 1])
                g[i] = f[i - 1] + 1;
            ret = max(ret, max(f[i], g[i]));
        }

        return ret;
    }

    // 6
    bool GetPath(TreeNode *root, TreeNode *x, stack<TreeNode *> &st)
    {
        if (root == nullptr)
            return false;

        st.push(root);

        if (root == x)
            return true;

        if (GetPath(root->left, x, st))
            return true;
        if (GetPath(root->right, x, st))
            return true;

        st.pop();

        return false;
    }

    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        stack<TreeNode *> qPath, pPath;

        GetPath(root, p, pPath);
        GetPath(root, q, qPath);

        while (qPath.size() != pPath.size())
        {
            if (qPath.size() > pPath.size())
                qPath.pop();
            else
                pPath.pop();
        }

        while (qPath.top() != pPath.top())
            qPath.pop(), pPath.pop();

        return qPath.top();
    }
};

// 7
struct RowDotFunctor
{
    const float *_matrix;
    const float *_vec;
    int _cols;

    RowDotFunctor(const float *matrix, const float *vec, int cols) : _matrix(matrix), _vec(vec), _cols(cols)
    {
    }

    __host__ __device__ float operator()(int row) const
    {
        float sum = 0.0f;
        const float *ptr = _matrix + row * _cols;

        for (int i = 0; i < _cols; i++)
            sum += ptr[i] * _vec[i];

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

    const float *matrix_ptr = thrust::raw_pointer_cast(d_matrix.data());
    const float *vec_ptr = thrust::raw_pointer_cast(d_vec.data());

    thrust::transform(thrust::counting_iterator<int>(0), thrust::counting_iterator<int>(rows), d_result.begin(), RowDotFunctor(matrix_ptr, vec_ptr, cols));

    vector<float> result(rows);

    thrust::copy(d_result.begin(), d_result.end(), result.begin());

    return result;
}