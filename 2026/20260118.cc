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
    int waysToStep(int n)
    {
        const int MOD = 1e9 + 7;
        if (n < 3)
            return n;

        int dp1 = 1, dp2 = 2, dp3 = 4, tmp1;
        for (int i = 3; i < n; i++)
        {
            tmp1 = ((dp1 + dp2) % MOD + dp3) % MOD;
            dp1 = dp2;
            dp2 = dp3;
            dp3 = tmp1;
        }

        return dp3;
    }

    // 2
    int minPathSum(vector<vector<int>> &grid)
    {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, INT_MAX));
        dp[0][1] = dp[1][0] = 0;
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                int prev = min(dp[i - 1][j], dp[i][j - 1]);
                dp[i][j] = prev + grid[i - 1][j - 1];
            }

        return dp[m][n];
    }

    // 3
    int removeDuplicates(vector<int> &nums)
    {
        int n = nums.size(), slow = 1, fast = 1;
        while (fast < n)
        {
            if (nums[fast] != nums[fast - 1])
                nums[slow++] = nums[fast];
            fast++;
        }
        return slow;
    }

    // 4
    int minCostClimbingStairs(vector<int> &cost)
    {
        int n = cost.size();
        vector<int> dp(n + 1);
        for (int i = 2; i <= n; i++)
            dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
        return dp[n];
    }


};