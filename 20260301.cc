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
    void hanota(vector<int> &A, vector<int> &B, vector<int> &C)
    {
        dfs(A, B, C, A.size());
    }

    void dfs(vector<int> &from, vector<int> &buffer, vector<int> &to, int n)
    {
        if (n == 1)
        {
            to.push_back(from.back());
            from.pop_back();
            return;
        }

        dfs(from, to, buffer, n - 1);
        to.push_back(from.back());
        from.pop_back();
        dfs(buffer, from, to, n - 1);
    }

    // 2
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

    // 3
    vector<vector<int>> generate(int numRows)
    {
        vector<vector<int>> ret;
        ret.resize(numRows);

        for (int i = 0; i < numRows; i++)
        {
            ret[i].resize(i + 1);
            ret[i][0] = ret[i][i] = 1;

            for (int j = 1; j < i; j++)
                ret[i][j] = ret[i - 1][j - 1] + ret[i - 1][j];
        }

        return ret;
    }

    // 4
    int m, n;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    void solve(vector<vector<char>> &board)
    {
        m = board.size(), n = board[0].size();

        for (int i = 0; i < m; i++)
        {
            if (board[i][0] == 'O')
                dfs(board, i, 0);
            if (board[i][n - 1] == 'O')
                dfs(board, i, n - 1);
        }

        for (int i = 0; i < n; i++)
        {
            if (board[0][i] == 'O')
                dfs(board, 0, i);
            if (board[m - 1][i] == 'O')
                dfs(board, m - 1, i);
        }

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (board[i][j] == 'O')
                    board[i][j] = 'X';
                else if (board[i][j] == '.')
                    board[i][j] = 'O';
            }
    }

    void dfs(vector<vector<char>> &board, int i, int j)
    {
        queue<pair<int, int>> q;
        q.push({i, j});
        board[i][j] = '.';

        while (q.size())
        {
            auto [a, b] = q.front();
            q.pop();
            for (int k = 0; k < 4; k++)
            {
                int x = a + dx[k], y = b + dy[k];
                if (x >= 0 && x < m && y >= 0 && y < n && board[x][y] == 'O')
                {
                    board[x][y] = '.';
                    q.push({x, y});
                }
            }
        }
    }

    // 5
    int N, ret = 0;
    bool vis[16] = {0};
    int countArrangement(int n)
    {
        N = n;
        dfs(1);
        return ret;
    }

    void dfs(int pos)
    {
        if (pos == N + 1)
        {
            ret++;
            return;
        }

        for (int i = 1; i <= N; i++)
        {
            if (!vis[i] && (i % pos == 0 || pos % i == 0))
            {
                vis[i] = true;
                dfs(pos + 1);
                vis[i] = false;
            }
        }
    }

    // 6
    string addBinary(string a, string b)
    {
        int m = a.size(), n = b.size();
        string ret;

        int t = 0, cur1 = m - 1, cur2 = n - 1;
        while (t || cur1 >= 0 || cur2 >= 0)
        {
            if (cur1 >= 0)
                t += a[cur1--] - '0';
            if (cur2 >= 0)
                t += b[cur2--] - '0';

            ret += to_string(t % 2);
            t /= 2;
        }

        reverse(ret.begin(), ret.end());
        return ret[0] == '0' ? "0" : ret;
    }
};