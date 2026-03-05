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
    int memo[101][101];
    int uniquePaths(int m, int n)
    {
        return dfs(m, n);
    }

    int dfs(int m, int n)
    {
        if (m == 0 && n == 0)
            return 0;

        if (m == 1 || n == 1)
        {
            memo[m][n] = 1;
            return 1;
        }

        if (memo[m][n])
            return memo[m][n];

        memo[m][n] = dfs(m - 1, n) + dfs(m, n - 1);
        return memo[m][n];
    }

    // 2
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost)
    {
        int n = gas.size();

        for (int i = 0; i < n; i++)
        {
            int rest = 0, step = 0;
            for (; step < n; step++)
            {
                int index = (i + step) % n;

                rest = rest + gas[index] - cost[index];
                if (rest < 0)
                    break;
            }

            if (rest >= 0)
                return i;

            i = i + step;
        }

        return -1;
    }

    // 3
    string longestCommonPrefix(vector<string> &strs)
    {
        for (int i = 0; i < strs[0].size(); i++)
            for (int j = 1; j < strs.size(); j++)
                if (i == strs[j].size() || strs[0][i] != strs[j][i])
                    return strs[0].substr(0, i);
        return strs[0];
    }

    // 4
    ListNode *swapPairs(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *newhead = new ListNode(0);
        ListNode *prev = newhead;
        ListNode *cur = head, *next = cur->next, *nnext = next->next;

        while (cur && next)
        {
            prev->next = next;
            next->next = cur;
            cur->next = nnext;

            prev = cur;
            cur = nnext;

            if (cur)
                next = cur->next;
            if (next)
                nnext = next->next;
        }

        prev = newhead->next;
        delete newhead;
        return prev;
    }

    // 5
    int ret = 0, N;
    bool vis[16];
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
    ListNode *reverseKGroup(ListNode *head, int k)
    {
        int sum = 0;
        ListNode *cur = head;

        while (cur)
        {
            cur = cur->next;
            sum++;
        }

        sum /= k;

        ListNode *newhead = new ListNode(0);
        ListNode *prev = newhead;
        cur = head;

        for (int i = 0; i < sum; i++)
        {
            ListNode *tmp = cur;

            for (int j = 0; j < k; j++)
            {
                ListNode *next = cur->next;

                prev->next = next;
                next->next = nullptr;
                prev = prev->next;

                cur = next;
            }

            prev = tmp;
        }

        prev->next = cur;

        prev = newhead->next;
        delete newhead;
        return prev;
    }

    // 7
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
                            Row[i][num] = Col[j][num] =
                                grid[i / 3][j / 3][num] = true;

                            if (dfs(board))
                                return true;
                            else
                            {
                                board[i][j] = '.';
                                Row[i][num] = Col[j][num] =
                                    grid[i / 3][j / 3][num] = false;
                            }
                        }
                    }

                    return false;
                }

        return true;
    }

    int change(int amount, vector<int> &coins)
    {
        vector<int> dp(amount + 1);
        dp[0] = 1;

        for (int i = 0; i < coins.size(); i++)
            for (int j = coins[i]; j <= amount; j++)
                dp[j] += dp[j - coins[j]];

        return dp[amount];
    }

    int numSquares(int n)
    {
        int m = sqrt(n);
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        for (int j = 1; j <= n; j++)
            dp[0][j] = 0x3f3f3f;
        for (int i = 1; i <= m; i++)
            for (int j = 0; j <= n; j++)
            {
                dp[i][j] = dp[i - 1][j];
                if (j >= i * i)
                    dp[i][j] = min(dp[i][j], dp[i - 1][j - i * i]);
            }

        return dp[m][n];
    }
};