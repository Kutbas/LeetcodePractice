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
    int maxProfit(vector<int> &prices, int fee)
    {
        int n = prices.size();
        vector<int> f(n);
        auto g = f;
        f[0] = -prices[0];

        for (int i = 1; i < n; i++)
        {
            f[i] = max(f[i - 1], g[i - 1] - prices[i]);
            g[i] = max(g[i - 1], f[i - 1] + prices[i] - fee);
        }

        return g[n - 1];
    }

    // 2
    int longestSubsequence(vector<int> &arr, int difference)
    {
        int n = arr.size();
        unordered_map<int, int> hash;
        hash[arr[0]] = 1;

        int ret = 1;
        for (int i = 1; i < n; i++)
        {
            hash[arr[i]] = hash[arr[i] - difference] + 1;
            ret = max(ret, hash[arr[i]]);
        }

        return ret;
    }

    // 3
    int maxUncrossedLines(vector<int> &nums1, vector<int> &nums2)
    {
        int m = nums1.size(), n = nums2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                if (nums1[i - 1] == nums2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }

        return dp[m][n];
    }

    // 4
    int FindGreatestSumOfSubArray(vector<int> &array)
    {
        int n = array.size();
        vector<int> dp(n + 1);

        int ret = INT_MIN;
        for (int i = 1; i <= n; i++)
        {
            dp[i] = max(dp[i - 1] + array[i - 1], array[i - 1]);
            ret = max(ret, dp[i]);
        }

        return ret;
    }

    // 5
    int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid)
    {
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        dp[0][1] = 1;

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                if (obstacleGrid[i - 1][j - 1] == 0)
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }

        return dp[m][n];
    }
};