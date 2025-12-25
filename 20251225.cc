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
    int K;
    bool vis[101][101];
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int wardrobeFinishing(int m, int n, int cnt)
    {
        K = cnt;

        int ret = 1;
        queue<pair<int, int>> q;
        q.push({0, 0});
        vis[0][0] = true;

        while (q.size())
        {
            int sz = q.size();
            while (sz--)
            {
                auto [a, b] = q.front();
                q.pop();

                for (int k = 0; k < 4; k++)
                {
                    int x = a + dx[k], y = b + dy[k];
                    if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && Check(x, y))
                    {
                        q.push({x, y});
                        vis[x][y] = true;
                        ret++;
                    }
                }
            }
        }

        return ret;
    }

    bool Check(int i, int j)
    {
        int tmp = 0;
        while (i)
        {
            tmp += i % 10;
            i /= 10;
        }
        while (j)
        {
            tmp += j % 10;
            j /= 10;
        }

        return tmp <= K;
    }

    // 2
    string convert(string s, int numRows)
    {
        if (numRows == 1)
            return s;

        int n = s.size(), d = 2 * numRows - 2;

        string ret;
        for (int i = 0; i < n; i += d)
            ret += s[i];

        for (int k = 1; k < numRows - 1; k++)
            for (int i = k, j = d - k; i < n || j < n; i += d, j += d)
            {
                if (i < n)
                    ret += s[i];
                if (j < n)
                    ret += s[j];
            }

        for (int i = numRows - 1; i < n; i += d)
            ret += s[i];

        return ret;
    }

    // 3
    int profitableSchemes(int n, int m, vector<int> &group, vector<int> &profit)
    {
        const int MOD = 1e9 + 7;
        int len = group.size();

        vector<vector<vector<int>>> dp(len + 1, vector<vector<int>>(n + 1, vector<int>(m + 1)));
        for (int i = 1; i <= n; i++)
            dp[0][i][0] = 1;

        for (int i = 1; i <= len; i++)
            for (int j = 0; j <= n; j++)
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

        return dp[len][n][m];
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

    // 5
    int m, n;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int ret = 0, step = 0;
    bool vis[21][21];
    int uniquePathsIII(vector<vector<int>> &grid)
    {
        m = grid.size(), n = grid[0].size();

        int bx = 0, by = 0;
        step += 2;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == 0)
                    step++;
                else if (grid[i][j] == 1)
                    bx = i, by = j;
            }

        vis[bx][by] = true;
        dfs(grid, bx, by, 1);

        return ret;
    }

    void dfs(vector<vector<int>> &grid, int i, int j, int count)
    {
        if (grid[i][j] == 2)
        {
            if (count == step)
                ret++;
            return;
        }

        for (int k = 0; k < 4; k++)
        {
            int x = i + dx[k], y = j + dy[k];
            if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && grid[x][y] != -1)
            {
                vis[x][y] = true;
                dfs(grid, x, y, count + 1);
                vis[x][y] = false;
            }
        }
    }

    // 7
    int sum = 0;
    int sumNumbers(TreeNode *root)
    {
        dfs(root, 0);
        return sum;
    }

    void dfs(TreeNode *root, int tmp)
    {
        tmp = tmp * 10 + root->val;

        if (root->left == nullptr && root->right == nullptr)
            sum += tmp;

        if (root->left)
            dfs(root->left, tmp);
        if (root->right)
            dfs(root->right, tmp);
    }
};

// 6
const int N = 1010;
int n, v;
int V[N], W[N];
int dp[N][N];

int main()
{
    cin >> n >> v;
    for (int i = 1; i <= n; i++)
        cin >> V[i] >> W[i];

    memset(dp, 0, sizeof dp);
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= v; j++)
        {
            dp[i][j] = dp[i - 1][j];

            if (j >= V[i])
                dp[i][j] = max(dp[i][j], dp[i][j - V[i]] + W[i]);
        }

    cout << dp[n][v] << endl;

    memset(dp, 0, sizeof dp);
    for (int i = 1; i <= v; i++)
        dp[0][i] = -1;

    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= v; j++)
        {
            dp[i][j] = dp[i - 1][j];

            if (j >= V[i] && dp[i][j - V[i]] != -1)
                dp[i][j] = max(dp[i][j], dp[i][j - V[i]] + W[i]);
        }

    cout << (dp[n][v] == -1 ? 0 : dp[n][v]) << endl;
}