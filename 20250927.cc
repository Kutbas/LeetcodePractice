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
    int maxSubArray(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> dp(n + 1);

        int ret = INT_MIN;
        for (int i = 1; i <= n; i++)
        {
            dp[i] = max(nums[i - 1], dp[i - 1] + nums[i - 1]);
            ret = max(ret, dp[i]);
        }

        return ret;
    }

    int maxSubarraySumCircular(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> f(n + 1), g(n + 1);

        int fmax = INT_MIN, gmin = INT_MAX, sum = 0;
        for (int i = 1; i <= n; i++)
        {
            int x = nums[i - 1];
            f[i] = max(x, x + f[i - 1]);
            fmax = max(fmax, f[i]);
            g[i] = min(x, x + g[i - 1]);
            gmin = min(gmin, g[i]);
            sum += x;
        }

        return sum == gmin ? fmax : max(fmax, sum - gmin);
    }

    // 1
    vector<vector<int>> ret;
    vector<int> path;
    int aim;
    vector<vector<int>> combinationSum(vector<int> &candidates, int target)
    {
        aim = target;
        dfs(candidates, 0, 0);
        return ret;
    }

    void dfs(vector<int> &nums, int sum, int pos)
    {
        if (sum > aim)
            return;

        if (sum == aim)
        {
            ret.push_back(path);
            return;
        }

        for (int i = pos; i < nums.size(); i++)
        {
            path.push_back(nums[i]);
            dfs(nums, sum + nums[i], i);
            path.pop_back();
        }
    }

    // 3
    vector<vector<string>> Ret;
    vector<string> Path;
    int N;
    bool Col[10], Dig1[20], Dig2[20];
    vector<vector<string>> solveNQueens(int n)
    {
        N = n;
        Path.resize(n);
        for (int i = 0; i < n; i++)
            Path[i].append(n, '.');

        dfs(0);

        return Ret;
    }

    void dfs(int row)
    {
        if (row == N)
        {
            Ret.push_back(Path);
            return;
        }

        for (int col = 0; col < N; col++)
        {
            if (!Col[col] && !Dig1[row + col] && !Dig2[row - col + N])
            {
                Path[row][col] = 'Q';
                Col[col] = Dig1[row + col] = Dig2[row - col + N] = true;
                dfs(row + 1);
                Col[col] = Dig1[row + col] = Dig2[row - col + N] = false;
                Path[row][col] = '.';
            }
        }
    }

    // 4
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    bool vis[51][51];
    int maxAreaOfIsland(vector<vector<int>> &grid)
    {
        m = grid.size(), n = grid[0].size();
        int ret = 0;

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j])
                    ret = max(ret, BFS(grid, i, j));

        return ret;
    }

    int BFS(vector<vector<int>> &grid, int i, int j)
    {
        int ret = 1;
        queue<pair<int, int>> q;
        q.push({i, j});
        vis[i][j] = true;

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
                    if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && grid[x][y])
                    {
                        ret++;
                        q.push({x, y});
                        vis[x][y] = true;
                    }
                }
            }
        }

        return ret;
    }

    // 5
    long N;
    double myPow(double x, int n)
    {
        N = n;
        if (N < 0)
        {
            x = 1 / x;
            N = -N;
        }

        return dfs(x, N);
    }

    double dfs(double x, int n)
    {
        if (n == 0)
            return 1;

        double tmp = dfs(x, n / 2);

        return n % 2 == 0 ? tmp * tmp : tmp * tmp * x;
    }

    // 6
    int dx[8] = {0, 0, 1, -1, 1, 1, -1 - 1};
    int dy[8] = {1, -1, 0, 0, 1, -1, 1, -1};
    int m, n;
    vector<vector<char>> updateBoard(vector<vector<char>> &board, vector<int> &click)
    {
        m = board.size(), n = board[0].size();
        int bx = click[0], by = click[1];

        if (board[bx][by] == 'M')
        {
            board[bx][by] = 'X';
            return board;
        }

        dfs(board, bx, by);

        return board;
    }

    void dfs(vector<vector<char>> &board, int i, int j)
    {
        int count = 0;
        for (int k = 0; k < 8; k++)
        {
            int x = i + dx[k], y = j + dy[k];
            if (x >= 0 && x < m && y >= 0 && y < n && board[x][y] == 'M')
                count++;
        }

        if (count)
        {
            board[i][j] = count + '0';
            return;
        }
        else
        {
            board[i][j] = 'B';
            for (int k = 0; k < 8; k++)
            {
                int x = i + dx[k], y = j + dy[k];
                if (x >= 0 && x < m && y >= 0 && y < n && board[x][y] == 'E')
                    dfs(board, x, y);
            }
        }
    }
};