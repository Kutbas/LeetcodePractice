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
    int minOperations(vector<int> &nums, int x)
    {
        int n = nums.size(), sum = 0;
        for (auto num : nums)
            sum += num;

        int aim = sum - x;
        if (aim < 0)
            return -1;

        int ret = INT_MIN;
        for (int left = 0, right = 0, tmp = 0; right < n; right++)
        {
            tmp += nums[right];
            while (tmp > aim)
                tmp -= nums[left++];
            if (tmp == aim)
                ret = max(ret, right - left + 1);
        }

        return ret == INT_MIN ? -1 : n - ret;
    }

    // 2
    vector<int> diStringMatch(string s)
    {
        int n = s.size(), left = 0, right = n;
        vector<int> ret;

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
    int maxTurbulenceSize(vector<int> &arr)
    {
        int n = arr.size();
        vector<int> f(n, 1);
        auto g = f;

        int ret = 1;
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

    // 4
    int findSubstringInWraproundString(string s)
    {
        int n = s.size();
        vector<int> dp(n, 1);

        for (int i = 1; i < n; i++)
        {
            if ((s[i - 1] == 'z' && s[i] == 'a') || s[i - 1] + 1 == s[i])
                dp[i] += dp[i - 1];
        }

        int hash[26] = {0};
        for (int i = 0; i < n; i++)
        {
            int index = s[i] - 'a';
            hash[index] = max(hash[index], dp[i]);
        }

        int ret = 0;
        for (auto i : hash)
            ret += i;

        return ret;
    }

    // 6
    typedef pair<int, int> PII;

    struct cmp
    {
        bool operator()(const PII &a, const PII &b)
        {
            return a.second > b.second;
        }
    };

    int networkDelayTime(vector<vector<int>> &times, int n, int k)
    {
        const int INF = 0x3f3f3f;
        vector<vector<PII>> graph(n + 1);
        for (auto &t : times)
            graph[t[0]].push_back({t[1], t[2]});

        vector<int> dist(n + 1, INF);
        dist[k] = 0;

        priority_queue<PII, vector<PII>, cmp> q;
        q.push({k, 0});

        while (q.size())
        {
            auto [u, d] = q.top();
            q.pop();

            if (dist[u] < d)
                continue;

            for (auto [v, w] : graph[u])
            {
                if (dist[u] + w < dist[v])
                {
                    dist[v] = dist[u] + w;
                    q.push({v, dist[v]});
                }
            }
        }

        int ret = INT_MIN;
        for (int i = 1; i <= n; i++)
            ret = max(ret, dist[i]);

        return ret == INF ? -1 : ret;
    }
};

// 5
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
        if (cols != matrix[i].size())
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