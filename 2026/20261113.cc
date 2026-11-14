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
    bool Row[9][10], Col[9][10], Grid[3][3][10];
    void solveSudoku(vector<vector<char>> &board)
    {
        m = board.size(), n = board[0].size();
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (board[i][j] != '.')
                {
                    int num = board[i][j] - '0';
                    Row[i][num] = Col[j][num] = Grid[i / 3][j / 3][num] = true;
                }
            }

        dfs(board);
    }

    bool dfs(vector<vector<char>> &board)
    {

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (board[i][j] == '.')
                {

                    for (int num = 1; num <= 9; num++)
                    {
                        if (!Row[i][num] && !Col[j][num] &&
                            !Grid[i / 3][j / 3][num])
                        {
                            board[i][j] = num + '0';
                            Row[i][num] = Col[j][num] =
                                Grid[i / 3][j / 3][num] = true;

                            if (dfs(board))
                                return true;

                            board[i][j] = '.';
                            Row[i][num] = Col[j][num] =
                                Grid[i / 3][j / 3][num] = false;
                        }
                    }
                    return false;
                }
            }

        return true;
    }

    // 2
    int monotoneIncreasingDigits(int n)
    {
        string s = to_string(n);
        int m = s.size();

        int i = 0;
        while (i + 1 < m && s[i] <= s[i + 1])
            i++;

        if (i + 1 == m)
            return n;

        while (i - 1 >= 0 && s[i] == s[i - 1])
            i--;

        s[i]--;
        for (int j = i + 1; j < m; j++)
            s[j] = '9';

        return stoi(s);
    }

    // 3
    int massage(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> f(n + 1);
        auto g = f;

        for (int i = 1; i <= n; i++)
        {
            f[i] = g[i - 1] + nums[i - 1];
            g[i] = max(f[i - 1], g[i - 1]);
        }

        return max(f[n], g[n]);
    }

    // 4
    int numDistinct(string s, string t)
    {
        int m = t.size(), n = s.size();
        vector<vector<double>> dp(m + 1, vector<double>(n + 1));

        for (int i = 0; i <= n; i++)
            dp[0][i] = 1;

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                dp[i][j] += dp[i][j - 1];
                if (t[i - 1] == s[j - 1])
                    dp[i][j] += dp[i - 1][j - 1];
            }

        return dp[m][n];
    }

};