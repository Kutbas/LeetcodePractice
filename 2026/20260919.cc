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
    int getSum(int a, int b)
    {
        while (b)
        {
            int x = a ^ b;
            int carry = (a & b) << 1;
            a = x;
            b = carry;
        }

        return b;
    }

    // 2
    int maxProfit(vector<int> &prices)
    {
        int n = prices.size();
        vector<int> f(n, INT_MIN);
        auto g = f;

        f[0] = -prices[0];
        g[0] = 0;

        for (int i = 1; i < n; i++)
        {
            f[i] = max(f[i - 1], g[i - 1] - prices[i]);
            g[i] = max(g[i - 1], f[i - 1] + prices[i]);
        }

        return g[n - 1];
    }

    // 3
    int numDistinct(string s, string t)
    {
        int m = t.size(), n = s.size();
        vector<vector<double>> dp(m + 1, vector<double>(n + 1));
        s = " " + s, t = " " + t;

        for (int i = 0; i <= n; i++)
            dp[0][i] = 1;

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                dp[i][j] += dp[i][j - 1];
                if (t[i] == s[j])
                    dp[i][j] += dp[i - 1][j - 1];
            }

        return dp[m][n];
    }
};

// 4
const int N = 1010;
int n, v;
int V[N], W[N];
int dp[N][N];

int main()
{
    cin >> n >> v;
    for (int i = 1; i <= n; i++)
        cin >> V[i] >> W[i];

    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= v; j++)
        {
            dp[i][j] = dp[i - 1][j];
            if (j >= V[i])
                dp[i][j] = max(dp[i][j], dp[i - 1][j - V[i]] + W[i]);
        }

    cout << dp[n][v] << endl;

    memset(dp, 0, sizeof dp);
    for (int i = 1; i <= v; i++)
        dp[0][i] = INT_MIN;

    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= v; j++)
        {
            dp[i][j] = dp[i - 1][j];
            if (j >= V[i] && dp[i - 1][j - V[i]] != INT_MIN)
                dp[i][j] = max(dp[i][j], dp[i - 1][j - V[i]] + W[i]);
        }

    cout << (dp[n][v] == INT_MIN ? 0 : dp[n][v]) << endl;

    return 0;
}