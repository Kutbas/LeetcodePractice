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
#include <set>
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
    vector<int> missingTwo(vector<int> &nums)
    {
        int xorsum = 0;
        for (auto n : nums)
            xorsum ^= n;
        for (int i = 1; i <= nums.size() + 2; i++)
            xorsum ^= i;

        int x = 0, y = 0;
        int lsb = xorsum == INT_MIN ? xorsum : xorsum & (-xorsum);
        for (auto n : nums)
        {
            if (n & lsb)
                x ^= n;
            else
                y ^= n;
        }
        for (int i = 1; i <= nums.size() + 2; i++)
        {
            if (i & lsb)
                x ^= i;
            else
                y ^= i;
        }

        return {x, y};
    }

    // 2
    bool increasingTriplet(vector<int> &nums)
    {
        int n = nums.size();
        int a = INT_MAX, b = nums[0];

        for (int i = 1; i < n; i++)
        {
            if (nums[i] > a)
                return true;
            else if (nums[i] > b)
                a = nums[i];
            else
                b = nums[i];
        }

        return false;
    }

    // 3
    int longestPalindrome(string s)
    {
        int n = s.size();
        int hash[128] = {0};

        for (char ch : s)
            hash[ch]++;

        int ret = 0;
        for (auto i : hash)
            ret += i / 2 * 2;

        return ret < n ? ret + 1 : ret;
    }

    // 4
    int monotoneIncreasingDigits(int n)
    {
        string s = to_string(n);
        int m = s.size(), i = 0;

        while (i + 1 < m && s[i] <= s[i + 1])
            i++;

        if (i + 1 == m)
            return n;

        while (i - 1 >= 0 && s[i] == s[i - 1])
            i--;

        s[i]--;
        for (int j = i + 1; j < m; j++)
            s[j] = '9';

        return stoi(s);
    }

    // 5
    int maxProfit(int k, vector<int> &prices)
    {
        const int INF = 0x3f3f3f;
        int n = prices.size();
        k = min(k, n / 2);
        vector<vector<int>> f(n, vector<int>(k + 1, -INF));
        auto g = f;

        f[0][0] = -prices[0];
        g[0][0] = 0;

        int ret = 0;
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

    // 6
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

    // 7
    int minInsertions(string s)
    {
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n));

        for (int i = n - 1; i >= 0; i--)
            for (int j = i + 1; j < n; j++)
            {
                if (s[i] == s[j])
                    dp[i][j] = dp[i + 1][j - 1];
                else
                    dp[i][j] = min(dp[i + 1][j], dp[i][j - 1]) + 1;
            }

        return dp[0][n - 1];
    }
};

// 8
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