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
    int findMaxForm(vector<string> &strs, int m, int n)
    {
        int len = strs.size();
        vector<vector<vector<int>>> dp(len + 1, vector<vector<int>>(m + 1, vector<int>(n + 1)));

        for (int i = 1; i <= len; i++)
        {
            int a = 0, b = 0;
            for (auto ch : strs[i - 1])
                if (ch == '0')
                    a++;
                else
                    b++;
            for (int j = 0; j <= m; j++)
                for (int k = 0; k <= n; k++)
                {
                    dp[i][j][k] = dp[i - 1][j][k];
                    if (j >= a && k >= b)
                        dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j - a][k - b] + 1);
                }
        }

        return dp[len][m][n];
    }

    const int MOD = 1e9 + 7;
    int profitableSchemes(int n, int m, vector<int> &g, vector<int> &p)
    {
        int len = g.size();
        vector<vector<vector<int>>> dp(len + 1, vector<vector<int>>(n + 1, vector<int>(m + 1)));

        for (int j = 0; j <= n; j++)
            dp[0][j][0] = 1;
        for (int i = 1; i <= len; i++)
            for (int j = 0; j <= n; j++)
                for (int k = 0; k <= m; k++)
                {
                    dp[i][j][k] = dp[i - 1][j][k];
                    if (j >= g[i - 1])
                        dp[i][j][k] += dp[i - 1][j - g[i - 1]][max(0, k - p[i - 1])];
                    dp[i][j][k] %= MOD;
                }
        return dp[len][n][m];
    }
};