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
        int n = nums.size(), xorsum = 0;
        for (auto n : nums)
            xorsum ^= n;

        for (int i = 1; i <= n + 2; i++)
            xorsum ^= i;

        int lsb = xorsum == INT_MIN ? xorsum : xorsum & (-xorsum);
        int x = 0, y = 0;
        for (auto n : nums)
        {
            if (n & lsb)
                x ^= n;
            else
                y ^= n;
        }

        for (int i = 1; i <= n + 2; i++)
        {
            if (i & lsb)
                x ^= i;
            else
                y ^= i;
        }

        return {x, y};
    }

    // 2
    int maxTurbulenceSize(vector<int> &arr)
    {
        int n = arr.size(), ret = 1;
        vector<int> f(n, 1), g(n, 1);

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

    // 3
    int longestSubsequence(vector<int> &arr, int difference)
    {
        int n = arr.size(), ret = 0;
        unordered_map<int, int> hash;
        hash[arr[0]] = 1;

        for (int i = 1; i < n; i++)
        {
            hash[arr[i]] = hash[arr[i] - difference] + 1;
            ret = max(ret, hash[arr[i]]);
        }

        return ret;
    }

    // 5
    vector<string> uncommonFromSentences(string s1, string s2)
    {
        unordered_map<string, int> hash;

        auto countWords = [&](const string &s)
        {
            istringstream iss(s);
            string word;

            while (iss >> word)
                hash[word]++;
        };

        countWords(s1);
        countWords(s2);

        vector<string> ret;

        for (auto &[a, b] : hash)
            if (b == 1)
                ret.push_back(a);

        return ret;
    }
};

// 4
struct RowDotFunctor
{
    const float *_matrix;
    const float *_vec;
    int _cols;

    RowDotFunctor(const float *matrix, const float *vec, int cols) : _matrix(matrix), _vec(vec), _cols(cols)
    {
    }

    __host__ __device__ float operator()(int row)
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

    const float *d_matrix_pointer = thrust::raw_pointer_cast(d_matrix.data());
    const float *d_vec_pointer = thrust::raw_pointer_cast(d_vec.data());

    thrust::transform(thrust::counting_iterator<int>(0), thrust::counting_iterator<int>(rows), d_result.begin(), RowDotFunctor(d_matrix_pointer, d_vec_pointer, cols));

    vector<float> result(rows);

    thrust::copy(d_result.begin(), d_result.end(), result.begin());

    return result;
}