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
    vector<vector<int>> ret;
    vector<int> path;
    bool vis[9];
    vector<vector<int>> permuteUnique(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
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
            if (vis[i] || (i != 0 && nums[i] == nums[i - 1] && !vis[i - 1]))
                continue;
            vis[i] = true;
            path.push_back(nums[i]);
            dfs(nums);
            path.pop_back();
            vis[i] = false;
        }
    }

    // 2
    int dx[8] = {0, 0, 1, -1, 1, 1, -1, -1};
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

    // 3
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    int memo[201][201];
    int longestIncreasingPath(vector<vector<int>> &matrix)
    {
        m = matrix.size(), n = matrix[0].size();

        int ret = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                ret = max(ret, 1 + dfs(matrix, i, j));

        return ret;
    }

    int dfs(vector<vector<int>> &matrix, int i, int j)
    {
        if (memo[i][j])
            return memo[i][j];

        int ret = 0;
        for (int k = 0; k < 4; k++)
        {
            int x = i + dx[k], y = j + dy[k];
            if (x >= 0 && x < m && y >= 0 && y < n && matrix[x][y] > matrix[i][j])
                ret = max(ret, 1 + dfs(matrix, x, y));
        }

        memo[i][j] = ret;
        return ret;
    }

    // 4
    vector<vector<string>> Ret;
    vector<string> Path;
    bool Col[10], Dig1[20], Dig2[20];
    int N;
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
                Path[row][col] = '.';
                Col[col] = Dig1[row + col] = Dig2[row - col + N] = false;
            }
        }
    }

    // 5
    vector<int> singleNumber(vector<int> &nums)
    {
        int xorsum = 0;
        for (auto n : nums)
            xorsum ^= n;

        int x = 0, y = 0;
        int lsb = xorsum == INT_MIN ? xorsum : xorsum & (-xorsum);
        for (auto n : nums)
        {
            if (n & lsb)
                x ^= n;
            else
                y ^= n;
        }

        return {x, y};
    }

    // 6
    string multiply(string num1, string num2)
    {
        int m = num1.size(), n = num2.size();
        vector<int> tmp(m + n - 1);

        for (int i = m - 1; i >= 0; i--)
            for (int j = n - 1; j >= 0; j--)
                tmp[i + j] += (num1[i] - '0') * (num2[j] - '0');

        string ret;
        int t = 0, i = m + n - 2;
        while (i >= 0 || t)
        {
            if (i >= 0)
                t += tmp[i--];

            ret += to_string(t % 10);
            t /= 10;
        }

        reverse(ret.begin(), ret.end());
        return ret[0] == '0' ? "0" : ret;
    }

    // 7
    int memo[201][201];
    int getMoneyAmount(int n)
    {
        return dfs(1, n);
    }

    int dfs(int m, int n)
    {
        if (m >= n)
            return 0;

        if (memo[m][n])
            return memo[m][n];

        int ret = INT_MAX;
        for (int head = m; head <= n; head++)
        {
            int x = dfs(m, head - 1);
            int y = dfs(head + 1, n);

            ret = min(ret, head + max(x, y));
        }

        memo[m][n] = ret;
        return ret;
    }
};