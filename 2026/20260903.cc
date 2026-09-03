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
    vector<vector<int>> ret;
    vector<int> path;
    bool vis[7] = {0};
    vector<vector<int>> permute(vector<int> &nums)
    {
        dfs(nums);
        return ret;
    }

    void dfs(vector<int> &nums)
    {
        if (path.size() == nums.size())
        {
            ret.push_back(path);
            return;
        }

        for (int i = 0; i < nums.size(); i++)
        {
            if (!vis[i])
            {
                vis[i] = true;
                path.push_back(nums[i]);
                dfs(nums);
                path.pop_back();
                vis[i] = false;
            }
        }
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
    int minCostClimbingStairs(vector<int> &cost)
    {
        int n = cost.size();
        vector<int> dp(n + 1);

        for (int i = 2; i <= n; i++)
        {
            dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
        }

        return dp[n];
    }

    // 4
    int coinChange(vector<int> &coins, int amount)
    {
        const int INF = 0x3f3f3f;
        int n = coins.size();
        vector<vector<int>> dp(n + 1, vector<int>(amount + 1));

        for (int i = 1; i <= amount; i++)
            dp[0][i] = INF;

        for (int i = 1; i <= n; i++)
            for (int j = 0; j <= amount; j++)
            {
                dp[i][j] = dp[i - 1][j];
                if (j >= coins[i - 1])
                    dp[i][j] = min(dp[i][j], dp[i][j - coins[i - 1]] + 1);
            }

        return dp[n][amount] == INF ? -1 : dp[n][amount];
    }

    // 5
    string reverseWords(string s)
    {
        int n = s.size(), start = 0;
        for (int i = 0; i <= n; i++)
            if (i == n || s[i] == ' ')
            {
                reverse(s.begin() + start, s.begin() + i);
                start = i + 1;
            }

        return s;
    }
};