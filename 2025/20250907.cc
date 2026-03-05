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
    int minCost(vector<vector<int>> &costs)
    {

        int n = costs.size();
        vector<vector<int>> dp(n + 1, vector<int>(3));

        for (int i = 1; i <= n; i++)
        {
            dp[i][0] = min(dp[i - 1][1], dp[i - 1][2]) + costs[i - 1][0];
            dp[i][1] = min(dp[i - 1][0], dp[i - 1][2]) + costs[i - 1][1];
            dp[i][2] = min(dp[i - 1][0], dp[i - 1][1]) + costs[i - 1][2];
        }

        return min(dp[n][0], min(dp[n][1], dp[n][2]));
    }

    // 1
    int memo[201][201];
    int getMoneyAmount(int n)
    {
        return dfs(1, n);
    }

    int dfs(int left, int right)
    {
        if (left > right)
            return 0;

        if (memo[left][right])
            return memo[left][right];

        int ret = INT_MAX;
        for (int head = left; head <= right; left++)
        {
            int tmp1 = dfs(left, head - 1);
            int tmp2 = dfs(head + 1, right);

            ret = min(ret, head + max(tmp1, tmp2));
        }

        memo[left][right] = ret;
        return ret;
    }

    // 2
    long prev = LONG_MIN;
    bool isValidBST(TreeNode *root)
    {
        if (root == nullptr)
            return true;

        bool left = isValidBST(root->left);
        if (!left)
            return false;

        bool cur = false;
        if (root->val > prev)
            cur = true;
        if (!cur)
            return false;

        prev = root->val;
        bool right = isValidBST(root->right);
        return right;
    }

    // 3
    int N, res = 0;
    bool vis[16];
    int countArrangement(int n)
    {
        N = n;
        dfs(1);
        return res;
    }

    void dfs(int pos)
    {
        if (pos == N + 1)
        {
            res++;
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

    // 4
    int Row[9][10], Col[9][10], grid[3][3][10];
    int m, n;
    bool isValidSudoku(vector<vector<char>> &board)
    {
        m = board.size(), n = board[0].size();
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (board[i][j] != '.')
                {
                    int num = board[i][j] - '0';
                    if (!Row[i][num] && !Col[j][num] && !grid[i / 3][j / 3][num])
                    {
                        Row[i][num] = Col[j][num] = grid[i / 3][j / 3][num] = true;
                    }
                    else
                        return false;
                }

        return true;
    }

    // 5
    vector<vector<int>> Ret;
    vector<int> Path;
    vector<vector<int>> subsets(vector<int> &nums)
    {
        dfs(nums, 0);
        return Ret;
    }

    void dfs(vector<int> &nums, int pos)
    {
        Ret.push_back(Path);

        if (pos == nums.size())
            return;

        for (int i = pos; i < nums.size(); i++)
        {
            Path.push_back(nums[i]);
            dfs(nums, i + 1);
            Path.pop_back();
        }
    }

    // 6
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