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
    int tribonacci(int n)
    {
        if (n == 0)
            return 0;

        if (n == 1 || n == 2)
            return 1;

        int a = 0, b = 1, c = 1, d = 0;
        for (int i = 3; i <= n; i++)
        {
            d = a + b + c;
            a = b, b = c, c = d;
        }
        return d;
    }

    // 2
    int findLength(vector<int> &nums1, vector<int> &nums2)
    {
        int m = nums1.size(), n = nums2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));

        int ret = 0;
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                if (nums1[i - 1] == nums2[j - 1])
                {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    ret = max(ret, dp[i][j]);
                }

        return ret;
    }

    // 3
    int MoreThanHalfNum_Solution(vector<int> &numbers)
    {
        int ret = numbers[0], count = 1;

        for (auto n : numbers)
        {
            if (n == ret)
                count++;
            else if (--count == 0)
            {
                ret = n;
                count = 1;
            }
        }

        return ret;
    }

    // 4
    int minCut(string s)
    {
        int n = s.size();
        vector<vector<bool>> isPal(n, vector<bool>(n));

        for (int i = n - 1; i >= 0; i--)
            for (int j = i; j < n; j++)
                if (s[i] == s[j])
                    isPal[i][j] = j - i + 1 > 3 ? isPal[i + 1][j - 1] : true;

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

    // 5
    int profitableSchemes(int n, int m, vector<int> &group,
                          vector<int> &profit)
    {
        const int MOD = 1e9 + 7;
        int len = group.size();
        vector<vector<vector<int>>> dp(
            len + 1, vector<vector<int>>(n + 1, vector<int>(m + 1)));

        for (int i = 0; i <= n; i++)
            dp[0][i][0] = 1;
        for (int i = 1; i <= len; i++)
            for (int j = 0; j <= n; j++)
            {
                for (int k = 0; k <= m; k++)
                {
                    dp[i][j][k] = dp[i - 1][j][k];

                    if (j >= group[i - 1])
                    {
                        int remain = max(0, k - profit[i - 1]);
                        dp[i][j][k] += dp[i - 1][j - group[i - 1]][remain];
                    }

                    dp[i][j][k] %= MOD;
                }
            }
        return dp[len][n][m];
    }

    // 6
    int findNumberOfLIS(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> longestLength(n, 1);
        vector<int> ways(n, 1);
        int globalLongest = 1, globalWays = 1;

        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (nums[j] < nums[i])
                {
                    int newlen = longestLength[j] + 1;
                    if (newlen == longestLength[i])
                        ways[i] += ways[j];
                    else if (newlen > longestLength[i])
                    {
                        longestLength[i] = newlen;
                        ways[i] = ways[j];
                    }
                }
            }

            if (globalLongest == longestLength[i])
                globalWays += ways[i];
            else if (longestLength[i] > globalLongest)
            {
                globalLongest = longestLength[i];
                globalWays = ways[i];
            }
        }

        return globalWays;
    }

    // 7
    int singleNumber(vector<int> &nums)
    {
        int bitMap = 0;
        for (int i = 0; i < 32; i++)
        {
            int count = 0;
            for (auto n : nums)
                if (((n >> i) & 1) == 1)
                    count++;
            if (count % 3 == 1)
                bitMap |= 1 << i;
        }
        return bitMap;
    }
};