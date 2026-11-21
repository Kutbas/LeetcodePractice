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
#include <set>
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
    int m, n;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    typedef pair<int, int> PII;
    bool vis[51][51];
    int cutOffTree(vector<vector<int>> &f)
    {
        m = f.size(), n = f[0].size();

        vector<PII> trees;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (f[i][j] > 1)
                    trees.push_back({i, j});

        sort(trees.begin(), trees.end(), [&](const PII &a, const PII &b)
             { return f[a.first][a.second] < f[b.first][b.second]; });

        int ret = 0;
        int bx = 0, by = 0;

        for (auto [a, b] : trees)
        {
            int step = dfs(f, bx, by, a, b);

            if (step == -1)
                return -1;

            ret += step;
            bx = a, by = b;
        }

        return ret;
    }

    int dfs(vector<vector<int>> &f, int bx, int by, int ex, int ey)
    {
        if (bx == ex && by == ey)
            return 0;

        memset(vis, 0, sizeof vis);
        int ret = 0;
        queue<PII> q;
        vis[bx][by] = true;
        q.push({bx, by});

        while (q.size())
        {
            ret++;
            int sz = q.size();
            while (sz--)
            {
                auto [a, b] = q.front();
                q.pop();

                for (int k = 0; k < 4; k++)
                {
                    int x = a + dx[k], y = b + dy[k];
                    if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && f[x][y])
                    {
                        if (x == ex && y == ey)
                            return ret;

                        q.push({x, y});
                        vis[x][y] = true;
                    }
                }
            }
        }

        return -1;
    }

    // 2
    int m, n;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int ret = 0, step = 0;
    bool vis[21][21];
    int uniquePathsIII(vector<vector<int>> &grid)
    {
        m = grid.size(), n = grid[0].size();

        int bx = 0, by = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == 0)
                    step++;
                else if (grid[i][j] == 1)
                    bx = i, by = j;
            }
        step += 2;

        vis[bx][by] = true;
        DFS(grid, bx, by, 1);

        return ret;
    }

    void DFS(vector<vector<int>> &grid, int i, int j, int count)
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
                DFS(grid, x, y, count + 1);
                vis[x][y] = false;
            }
        }
    }

    // 3
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int K;
    bool vis[101][101] = {0};
    int wardrobeFinishing(int m, int n, int cnt)
    {
        K = cnt;

        int ret = 1;
        queue<pair<int, int>> q;
        q.push({0, 0});
        vis[0][0] = true;

        while (q.size())
        {
            auto [a, b] = q.front();
            q.pop();

            for (int k = 0; k < 4; k++)
            {
                int x = a + dx[k], y = b + dy[k];
                if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && check(x, y))
                {
                    ret++;
                    vis[x][y] = true;
                    q.push({x, y});
                }
            }
        }

        return ret;
    }

    bool check(int i, int j)
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

    // 4
    int maxProfit(int k, vector<int> &prices)
    {
        const int INF = 0x3f3f3f;
        int n = prices.size();
        k = min(k, n / 2);

        vector<vector<int>> f(n, vector<int>(k + 1, -INF));
        auto g = f;
        f[0][0] = -prices[0];
        g[0][0] = 0;

        int ret = 0;
        for (int i = 1; i < n; i++)
            for (int j = 0; j <= k; j++)
            {
                f[i][j] = max(f[i - 1][j], g[i - 1][j] - prices[i]);
                g[i][j] = g[i - 1][j];
                if (j >= 1)
                    g[i][j] = max(g[i][j], f[i - 1][j - 1] + prices[i]);
                ret = max(ret, g[i][j]);
            }

        return ret;
    }

    // 5
    bool checkPartitioning(string s)
    {
        int n = s.size();
        vector<vector<bool>> isPal(n, vector<bool>(n));
        for (int i = n - 1; i >= 0; i--)
            for (int j = i; j < n; j++)
                if (s[i] == s[j])
                    isPal[i][j] = j - i + 1 > 3 ? isPal[i + 1][j - 1] : true;

        for (int i = 1; i < n; i++)
            for (int j = i; j < n - 1; j++)
                if (isPal[0][i - 1] && isPal[i][j] && isPal[j + 1][n - 1])
                    return true;

        return false;
    }

    // 6
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

    // 7
    bool IsPopOrder(vector<int> &pushV, vector<int> &popV)
    {
        int n = pushV.size(), i = 0;
        stack<int> st;

        for (auto num : pushV)
        {
            st.push(num);
            while (st.size() && st.top() == popV[i])
            {
                st.pop();
                i++;
            }
        }

        return i == n;
    }
};