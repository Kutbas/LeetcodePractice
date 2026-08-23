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
    bool validateStackSequences(vector<int> &pushed, vector<int> &popped)
    {
        stack<int> nums;
        int n = pushed.size(), i = 0;

        for (auto num : pushed)
        {
            nums.push(num);
            while (nums.size() && nums.top() == popped[i])
            {
                nums.pop();
                i++;
            }
        }

        return i == n;
    }

    // 2
    bool lemonadeChange(vector<int> &bills)
    {
        int hash[128] = {0};

        for (auto n : bills)
        {
            if (n == 5)
                hash[5]++;
            else if (n == 10)
            {
                if (!hash[5])
                    return false;
                hash[5]--, hash[10]++;
            }
            else
            {
                if (hash[5] && hash[10])
                    hash[5]--, hash[10]--;
                else if (hash[5] >= 3)
                    hash[5] -= 3;
                else
                    return false;
            }
        }

        return true;
    }

    // 3
    int massage(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 0)
            return 0;

        vector<int> f(n), g(n);
        f[0] = nums[0];

        for (int i = 1; i < n; i++)
        {
            f[i] = g[i - 1] + nums[i];
            g[i] = max(f[i - 1], g[i - 1]);
        }

        return max(f[n - 1], g[n - 1]);
    }

    // 4
    int maxTurbulenceSize(vector<int> &arr)
    {
        int n = arr.size();
        vector<int> f(n + 1, 1), g(n + 1, 1);
        int ret = 1;

        for (int i = 1; i < n; i++)
        {
            if (arr[i - 1] > arr[i])
                f[i] = g[i - 1] + 1;
            else if (arr[i - 1] < arr[i])
                g[i] = f[i - 1] + 1;
            ret = max(ret, max(f[i], g[i]));
        }

        return ret;
    }

    // 5
    class MyQueue
    {
    private:
        stack<int> in, out;

        void in2out()
        {
            while (in.size())
            {
                out.push(in.top());
                in.pop();
            }
        }

    public:
        MyQueue()
        {
        }

        void push(int x)
        {
            in.push(x);
        }

        int pop()
        {
            if (out.empty())
                in2out();

            int r = out.top();
            out.pop();
            return r;
        }

        int peek()
        {
            if (out.empty())
                in2out();

            int r = out.top();
            return r;
        }

        bool empty()
        {
            return in.empty() && out.empty();
        }
    };
};

// 6
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

        for (int col = 0; col < _cols; col++)
            sum += ptr[col] * _vec[col];

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