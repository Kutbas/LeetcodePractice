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
    vector<vector<int>> matrixBlockSum(vector<vector<int>> &mat, int k)
    {
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1] + mat[i - 1][j - 1];

        vector<vector<int>> ret(m, vector<int>(n));
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                int x1 = max(0, i - k) + 1, y1 = max(0, j - k) + 1;
                int x2 = min(m - 1, i + k) + 1, y2 = min(n - 1, j + k) + 1;
                ret[i][j] = dp[x2][y2] - dp[x1 - 1][y2] - dp[x2][y1 - 1] + dp[x1 - 1][y1 - 1];
            }

        return ret;
    }

    // 2
    typedef pair<int, int> PIR;
    int m, n;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    bool vis[51][51] = {0};
    int cutOffTree(vector<vector<int>> &forest)
    {
        m = forest.size(), n = forest[0].size();
        vector<PIR> trees;

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (forest[i][j] > 1)
                    trees.push_back({i, j});

        sort(trees.begin(), trees.end(), [&](const PIR &p1, const PIR &p2)
             { return forest[p1.first][p1.second] < forest[p2.first][p2.second]; });

        int ret = 0, bx = 0, by = 0;
        for (auto &[a, b] : trees)
        {
            int step = dfs(forest, bx, by, a, b);
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

        queue<PIR> q;
        q.push({bx, by});
        int ret = 0;
        vis[bx][by] = true;

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
                    if (x >= 0 && x < m && y >= 0 && y < n && f[x][y] && !vis[x][y])
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

    // 3
    int N;
    vector<vector<string>> ret;
    vector<string> path;
    bool Col[10], Dig1[20], Dig2[20];
    vector<vector<string>> solveNQueens(int n)
    {
        N = n;
        path.resize(n);

        for (int i = 0; i < n; i++)
            path[i].append(n, '.');

        dfs(0);

        return ret;
    }

    void dfs(int row)
    {
        if (row == N)
        {
            ret.push_back(path);
            return;
        }

        for (int col = 0; col < N; col++)
        {
            if (!Col[col] && !Dig1[row + col] && !Dig2[row - col + N])
            {
                path[row][col] = 'Q';
                Col[col] = Dig1[row + col] = Dig2[row - col + N] = true;
                dfs(row + 1);
                Col[col] = Dig1[row + col] = Dig2[row - col + N] = false;
                path[row][col] = '.';
            }
        }
    }

    // 4
    int eraseOverlapIntervals(vector<vector<int>> &in)
    {
        sort(in.begin(), in.end());

        int n = in.size(), right = in[0][1], ret = 0;

        for (int i = 1; i < n; i++)
        {
            int a = in[i][0], b = in[i][1];
            if (a < right)
            {
                ret++;
                right = min(right, b);
            }
            else
                right = b;
        }

        return ret;
    }

    // 5
    int deleteAndEarn(vector<int> &nums)
    {
        const int N = 10001;
        int arr[N] = {0};

        for (auto n : nums)
            arr[n] += n;

        vector<int> f(N), g(N);
        for (int i = 1; i < N; i++)
        {
            f[i] = g[i - 1] + arr[i];
            g[i] = max(f[i - 1], g[i - 1]);
        }

        return max(f[N - 1], g[N - 1]);
    }

    // 6
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

    // 7
    int maxProfit(vector<int> &prices, int fee)
    {
        int n = prices.size();
        vector<int> f(n), g(n);
        f[0] = -prices[0];

        for (int i = 1; i < n; i++)
        {
            f[i] = max(f[i - 1], g[i - 1] - prices[i]);
            g[i] = max(g[i - 1], f[i - 1] + prices[i] - fee);
        }

        return max(f[n - 1], g[n - 1]);
    }

    // 8
    int longestSubsequence(vector<int> &arr, int difference)
    {
        int n = arr.size(), ret = 1;
        unordered_map<int, int> hash;
        hash[arr[0]] = 1;

        for (int i = 1; i < n; i++)
        {
            hash[arr[i]] = hash[arr[i] - difference] + 1;
            ret = max(ret, hash[arr[i]]);
        }

        return ret;
    }
};