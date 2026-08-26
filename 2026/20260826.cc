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
    bool isValidSudoku(vector<vector<char>> &board)
    {
        m = board.size(), n = board[0].size();

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (board[i][j] != '.')
                {
                    int num = board[i][j] - '0';
                    if (Row[i][num] || Col[j][num] || Grid[i / 3][j / 3][num])
                        return false;
                    Row[i][num] = Col[j][num] = Grid[i / 3][j / 3][num] = true;
                }
            }

        return true;
    }

    // 2
    bool lemonadeChange(vector<int> &bills)
    {
        int hash[128] = {0};

        for (auto n : bills)
        {
            if (n == 5)
                hash[5]++;
            else if (n == 10)
            {
                if (!hash[5])
                    return false;
                hash[5]--, hash[10]++;
            }
            else
            {
                if (hash[10] && hash[5])
                    hash[10]--, hash[5]--;
                else if (hash[5] >= 3)
                    hash[5] -= 3;
                else
                    return false;
            }
        }

        return true;
    }

    // 3
    int deleteAndEarn(vector<int> &nums)
    {
        const int N = 10001;
        int arr[N] = {0};
        for (auto n : nums)
            arr[n] += n;

        vector<int> f(N);
        auto g = f;
        for (int i = 1; i < N; i++)
        {
            f[i] = g[i - 1] + arr[i];
            g[i] = max(g[i - 1], f[i - 1]);
        }

        return max(f[N - 1], g[N - 1]);
    }

    // 4
    int numberOfArithmeticSlices(vector<int> &nums)
    {
        int n = nums.size();
        if (n < 3)
            return 0;

        int sum = 0, prev = 0;
        for (int i = 2; i < n; i++)
        {
            if (nums[i] - nums[i - 1] == nums[i - 1] - nums[i - 2])
            {
                prev += 1;
                sum += prev;
            }
            else
                prev = 0;
        }

        return sum;
    }

    // 5
    int longestPalindromeSubseq(string s)
    {
        int n = s.size(), ret = 1;
        vector<vector<int>> dp(n, vector<int>(n));

        for (int i = n - 1; i >= 0; i--)
            for (int j = i; j < n; j++)
            {
                if (s[i] == s[j])
                    dp[i][j] = j == i ? 1 : dp[i + 1][j - 1] + 2;
                else
                    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
                ret = max(ret, dp[i][j]);
            }

        return ret;
    }

    // 6
    int numDistinct(string s, string t)
    {
        int m = t.size(), n = s.size();
        s = " " + s, t = " " + t;

        vector<vector<double>> dp(m + 1, vector<double>(n + 1));
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