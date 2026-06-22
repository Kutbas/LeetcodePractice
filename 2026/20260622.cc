#include <mutex>
#include <vector>
#include <algorithm>
#include <climits>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
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
    string decodeString(string s)
    {
        stack<string> st;
        string ret;
        stack<int> nums;
        int n = 0;

        for (char ch : s)
        {
            if (isdigit(ch))
                n = n * 10 + (ch - '0');
            else if (ch == '[')
            {
                st.push(ret);
                ret = "";
                nums.push(n);
                n = 0;
            }
            else if (ch == ']')
            {
                string tmp = st.top();
                st.pop();
                int k = nums.top();
                nums.pop();
                while (k--)
                    tmp += ret;
                ret = tmp;
            }
            else
                ret += ch;
        }

        return ret;
    }

    // 2
    int findLongestChain(vector<vector<int>> &pairs)
    {
        sort(pairs.begin(), pairs.end());

        int n = pairs.size(), ret = 1;

        vector<int> dp(n, 1);
        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < i; j++)
            {
                int a = pairs[j][1], b = pairs[i][0];
                if (a < b)
                    dp[i] = max(dp[i], dp[j] + 1);
            }
            ret = max(ret, dp[i]);
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
    vector<int> intersection(vector<int> &nums1, vector<int> &nums2)
    {
        vector<int> ret;
        int hash[1001] = {0};

        for (auto n : nums1)
            if (hash[n] == 0)
                hash[n]++;

        for (auto n : nums2)
            if (--hash[n] == 0)
                ret.push_back(n);

        return ret;
    }

    // 5
    string addStrings(string num1, string num2)
    {
        int m = num1.size(), n = num2.size();

        string ret;
        int t = 0, cur1 = m - 1, cur2 = n - 1;
        while (cur1 >= 0 || cur2 >= 0 || t)
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

    // 6
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

};

// 7
// #include <thrust/device_vector.h>
// #include <thrust/transform.h>
// #include <thrust/copy.h>
// #include <thrust/iterator/counting_iterator.h>
// #include <iostream>
// #include <algorithm>
// #include <vector>

// using namespace std;

// struct RowDotFunctor{
//     const float* _matrix;
//     const float* _vec;
//     int _cols;

//     RowDotFunctor(const float* matrix,const float* vec,int cols)
//     :_matrix(matrix),_vec(vec),_cols(cols)
//     {}

//     __host__ __device__
//     float operator()(int row) const
//     {
//         float sum=0.0f;

//         const float* ptr=_matrix+row*_cols;
//         for(int col=0;col<_cols;col++)
//             sum+=ptr[col]*_vec[col];

//         return sum;
//     }

// };

// std::vector<float> matrix_dot_vector(const std::vector<std::vector<float>>& matrix, const std::vector<float>& vec) {
//     int rows=matrix.size();
//     if(rows==0)
//         return {-1};

//     int cols=matrix[0].size();
//     if(cols!=vec.size())
//         return {-1};

//     vector<float> flat_matrix(rows*cols);
//     for(int i=0;i<rows;i++)
//     {
//         if(matrix[i].size()!=cols)
//             return {-1};

//         copy(matrix[i].begin(),matrix[i].end(),flat_matrix.begin()+i*cols);
//     }

//     thrust::device_vector<float> d_matrix(flat_matrix.begin(),flat_matrix.end());
//     thrust::device_vector<float> d_vec(vec.begin(),vec.end());
//     thrust::device_vector<float> d_result(rows);

//     const float* matrix_ptr=thrust::raw_pointer_cast(d_matrix.data());
//     const float* vec_ptr=thrust::raw_pointer_cast(d_vec.data());

//     thrust::transform(thrust::counting_iterator<int>(0),thrust::counting_iterator<int>(rows),d_result.begin(),RowDotFunctor(matrix_ptr,vec_ptr,cols));

//     vector<float> result(cols);

//     thrust::copy(d_result.begin(),d_result.end(),result.begin());

//     return result;
// }