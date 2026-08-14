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
                if (board[i][j] != '.')
                {
                    int num = board[i][j] - '0';
                    Row[i][num] = Col[j][num] = Grid[i / 3][j / 3][num] = true;
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
                        if (!Row[i][num] && !Col[j][num] && !Grid[i / 3][j / 3][num])
                        {
                            board[i][j] = num + '0';
                            Row[i][num] = Col[j][num] = Grid[i / 3][j / 3][num] = true;
                            if (dfs(board))
                                return true;
                            Row[i][num] = Col[j][num] = Grid[i / 3][j / 3][num] = false;
                            board[i][j] = '.';
                        }
                    }
                    return false;
                }
            }
        return true;
    }

    // 2
    int minFallingPathSum(vector<vector<int>> &matrix)
    {
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 2, INT_MAX));

        for (int i = 0; i < n + 2; i++)
            dp[0][i] = 0;

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                dp[i][j] = min(dp[i - 1][j], min(dp[i - 1][j - 1], dp[i - 1][j + 1])) + matrix[i - 1][j - 1];

        int ret = INT_MAX;
        for (int i = 1; i <= n; i++)
            ret = min(ret, dp[m][i]);

        return ret;
    }

    // 3
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
            g[i] = max(g[i - 1], f[i - 1]);
        }

        return max(f[N - 1], g[N - 1]);
    }

    // 4
    int minCost(vector<vector<int>> &costs)
    {
        int n = costs.size();
        vector<vector<int>> dp(n + 1, vector<int>(3));

        for (int i = 1; i <= n; i++)
        {
            dp[i][0] = min(dp[i - 1][1], dp[i - 1][2]) + costs[i - 1][0];
            dp[i][1] = min(dp[i - 1][0], dp[i - 1][2]) + costs[i - 1][1];
            dp[i][2] = min(dp[i - 1][1], dp[i - 1][0]) + costs[i - 1][2];
        }

        return min(dp[n][0], min(dp[n][1], dp[n][2]));
    }

    // 5
    int findLongestChain(vector<vector<int>> &pairs)
    {
        int n = pairs.size();
        sort(pairs.begin(), pairs.end());

        vector<int> dp(n, 1);
        int ret = 1;
        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (pairs[j][1] < pairs[i][0])
                    dp[i] = max(dp[i], dp[j] + 1);
            }
            ret = max(ret, dp[i]);
        }

        return ret;
    }

    // 6
    int longestPalindromeSubseq(string s)
    {
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n));

        for (int i = n - 1; i >= 0; i--)
            for (int j = i; j < n; j++)
            {
                if (s[i] == s[j])
                    dp[i][j] = i == j ? 1 : dp[i + 1][j - 1] + 2;
                else
                    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
            }

        return dp[0][n - 1];
    }

    // 7
    int numDistinct(string s, string t)
    {
        int m = t.size(), n = s.size();
        vector<vector<double>> dp(m + 1, vector<double>(n + 1));
        s = " " + s, t = " " + t;

        for (int i = 0; i <= n; i++)
            dp[0][i] = 1;

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                dp[i][j] += dp[i][j - 1];
                if (t[i] == s[j])
                    dp[i][j] += dp[i - 1][j - 1];
            }

        return dp[m][n];
    }
};

// 8
int main()
{
    string s;
    cin >> s;

    int hash[128] = {0};
    for (char ch : s)
        hash[ch]++;

    for (char ch : s)
        if (hash[ch] == 1)
        {
            cout << ch << endl;
            return 0;
        }

    cout << -1 << endl;

    return 0;
}