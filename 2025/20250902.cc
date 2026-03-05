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
    int minPathSum(vector<vector<int>> &grid)
    {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, INT_MAX));
        dp[0][1] = dp[1][0] = 0;

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i - 1][j - 1];

        return dp[m][n];
    }

    // 1
    int minMutation(string startGene, string endGene, vector<string> &bank)
    {
        unordered_set<string> hash(bank.begin(), bank.end());
        unordered_set<string> vis;
        string change = "ATGC";

        if (!hash.count(endGene))
            return -1;

        queue<string> q;
        q.push(startGene);
        int ret = 0;

        while (q.size())
        {
            ret++;
            int sz = q.size();
            while (sz--)
            {
                auto t = q.front();
                q.pop();
                for (int i = 0; i < t.size(); i++)
                {
                    string tmp = t;
                    for (int k = 0; k < 4; k++)
                    {
                        tmp[i] = change[k];
                        if (hash.count(tmp) && !vis.count(tmp))
                        {
                            if (tmp == endGene)
                                return ret;
                            q.push(tmp);
                            vis.insert(tmp);
                        }
                    }
                }
            }
        }

        return -1;
    }

    // 2
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    bool vis[16][16];
    bool exist(vector<vector<char>> &board, string word)
    {
        m = board.size(), n = board[0].size();
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (board[i][j] == word[0])
                {
                    vis[i][j] = true;
                    if (dfs(board, i, j, word, 1))
                        return true;
                    vis[i][j] = false;
                }

        return false;
    }

    bool dfs(vector<vector<char>> &board, int i, int j, string &word, int pos)
    {
        if (pos == word.size())
            return true;

        for (int k = 0; k < 4; k++)
        {
            int x = i + dx[k], y = j + dy[k];
            if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && board[x][y] == word[pos])
            {
                vis[x][y] = true;
                if (dfs(board, x, y, word, pos + 1))
                    return true;
                else
                    vis[x][y] = false;
            }
        }

        return false;
    }

    // 3
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    bool vis[501][501];
    int numEnclaves(vector<vector<int>> &grid)
    {
        m = grid.size(), n = grid[0].size();

        for (int i = 0; i < m; i++)
        {
            if (grid[i][0] == 1)
                dfs(grid, i, 0);
            if (grid[i][n - 1] == 1)
                dfs(grid, i, n - 1);
        }
        for (int i = 0; i < n; i++)
        {
            if (grid[0][i] == 1)
                dfs(grid, 0, i);
            if (grid[m - 1][i] == 1)
                dfs(grid, m - 1, i);
        }

        int ret = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j] == 1 & !vis[i][j])
                    ret++;

        return ret;
    }

    void dfs(vector<vector<int>> &grid, int i, int j)
    {
        queue<pair<int, int>> q;
        q.push({i, j});
        vis[i][j] = true;

        while (q.size())
        {
            auto [a, b] = q.front();
            q.pop();
            for (int k = 0; k < 4; k++)
            {
                int x = a + dx[k], y = b + dy[k];
                if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && grid[x][y] == 1)
                {
                    q.push({x, y});
                    vis[x][y] = true;
                }
            }
        }
    }

    // 4
    int singleNumber(vector<int> &nums)
    {
        int ret = 0;
        for (int i = 0; i < 32; i++)
        {
            int count = 0;
            for (auto n : nums)
                if ((n >> i) & 1 == 1)
                    count++;

            if (count % 3 == 1)
                ret |= (1 << i);
        }

        return ret;
    }

    // 5
    bool Row[9][10], Col[9][10], grid[3][3][10];
    int m, n;
    void solveSudoku(vector<vector<char>> &board)
    {
        m = board.size(), n = board[0].size();
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (board[i][j] != '.')
                {
                    int num = board[i][j] - '0';
                    Row[i][num] = Col[j][num] = grid[i / 3][j / 3][num] = true;
                }

        dfs(board);

        return;
    }

    bool dfs(vector<vector<char>> &board)
    {
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (board[i][j] == '.')
                {
                    for (int num = 1; num <= 9; num++)
                    {
                        if (!Row[i][num] && !Col[j][num] && !grid[i / 3][j / 3][num])
                        {
                            board[i][j] = num + '0';
                            Row[i][num] = Col[j][num] = grid[i / 3][j / 3][num] = true;
                            if (dfs(board))
                                return true;
                            else
                            {
                                board[i][j] = '.';
                                Row[i][num] = Col[j][num] = grid[i / 3][j / 3][num] = false;
                            }
                        }
                    }
                    return false;
                }
        return true;
    }

    // 6
    int findPoisonedDuration(vector<int> &timeSeries, int duration)
    {
        int ret = 0;
        for (int i = 0; i < timeSeries.size() - 1; i++)
        {
            int tmp = timeSeries[i + 1] - timeSeries[i];
            if (tmp > duration)
                ret += duration;
            else
                ret += tmp;
        }

        return ret + duration;
    }
};
