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
    bool checkPartitioning(string s)
    {
        int n = s.size();
        vector<vector<bool>> dp(n, vector<bool>(n));

        for (int i = n - 1; i >= 0; i--)
            for (int j = i; j < n; j++)
                if (s[i] == s[j])
                    dp[i][j] = i + 1 < j ? dp[i + 1][j - 1] : true;

        for (int i = 1; i < n - 1; i++)
            for (int j = i; j < n - 1; j++)
                if (dp[0][i - 1] && dp[i][j] && dp[j + 1][n - 1])
                    return true;
        return false;
    }

    int minCut(string s)
    {
        int n = s.size();
        vector<vector<bool>> isPal(n, vector<bool>(n));

        for (int i = n - 1; i >= 0; i--)
            for (int j = i; j < n; j++)
                if (s[i] == s[j])
                    isPal[i][j] = i + 1 < j ? isPal[i + 1][j - 1] : true;

        vector<int> dp(n, INT_MAX);
        for (int i = 0; i < n; i++)
        {
            if (isPal[0][i])
                dp[i] = 0;
            else
            {
                for (int j = 1; j <= i; j++)
                    if (isPal[j][i])
                        dp[i] = min(dp[i], dp[j - 1] + 1);
            }
        }

        return dp[n - 1];
    }

    // 1
    int wiggleMaxLength(vector<int> &nums)
    {
        int n = nums.size();
        if (n < 2)
            return n;

        int ret = 0, left = 0;
        for (int i = 0; i < n - 1; i++)
        {
            int right = nums[i + 1] - nums[i];
            if (right == 0)
                continue;
            if (left * right <= 0)
                ret++;
            left = right;
        }

        return ret + 1;
    }

    // 2
    string optimalDivision(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 1)
            return to_string(nums[0]);
        if (n == 2)
            return to_string(nums[0]) + '/' + to_string(nums[1]);

        string ret = to_string(nums[0]) + "/(" + to_string(nums[1]);
        for (int i = 2; i < n; i++)
            ret += '/' + to_string(nums[i]);
        ret += ")";
        return ret;
    }
};