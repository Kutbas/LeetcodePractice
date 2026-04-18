#include <bits/stdc++.h>
#include <mutex>
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
    int memo[101][101] = {0};
    int uniquePaths(int m, int n)
    {
        return dfs(m, n);
    }

    int dfs(int m, int n)
    {
        if (m == 0 || n == 0)
            return 0;

        if (m == 1 && n == 1)
            return 1;

        if (memo[m][n])
            return memo[m][n];

        int ret = dfs(m - 1, n) + dfs(m, n - 1);

        memo[m][n] = ret;
        return ret;
    }

    // 2
    void moveZeroes(vector<int> &nums)
    {
        int n = nums.size(), cur = 0, dest = -1;
        while (cur < n)
        {
            if (nums[cur])
                swap(nums[cur], nums[++dest]);
            cur++;
        }
    }

    // 3
    string decodeString(string s)
    {
        int n = s.size();
        stack<int> nums;
        int num = 0;
        stack<string> st;
        string ret;

        for (char ch : s)
        {
            if (isdigit(ch))
                num = num * 10 + (ch - '0');
            else if (ch == '[')
            {
                nums.push(num);
                num = 0;
                st.push(ret);
                ret = "";
            }
            else if (ch == ']')
            {
                int k = nums.top();
                nums.pop();
                string tmp = st.top();
                st.pop();
                while (k--)
                    tmp += ret;
                ret = tmp;
            }
            else
                ret += ch;
        }
        return ret;
    }

    // 4
    int combinationSum4(vector<int> &nums, int target)
    {
        vector<double> dp(target + 1);
        dp[0] = 1;

        for (int i = 1; i <= target; i++)
            for (auto n : nums)
                if (i >= n)
                    dp[i] += dp[i - n];
        return dp[target];
    }
};