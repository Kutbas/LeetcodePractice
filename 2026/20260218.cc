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

    // 2
    int xorsum = 0, sum = 0;
    int subsetXORSum(vector<int> &nums)
    {
        dfs(nums, 0);
        return sum;
    }

    void dfs(vector<int> &nums, int pos)
    {
        sum += xorsum;

        if (pos == nums.size())
        {
            return;
        }

        for (int i = pos; i < nums.size(); i++)
        {
            xorsum ^= nums[i];
            dfs(nums, i + 1);
            xorsum ^= nums[i];
        }
    }

    // 3
    int m, n;
    bool Row[9][10], Col[9][10], Grid[3][3][10];
    bool isValidSudoku(vector<vector<char>> &board)
    {
        m = board.size(), n = board[0].size();

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (board[i][j] != '.')
                {
                    int num = board[i][j] - '0';
                    if (Row[i][num] || Col[j][num] || Grid[i / 3][j / 3][num])
                        return false;
                    Row[i][num] = Col[j][num] = Grid[i / 3][j / 3][num] = true;
                }

        return true;
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
                {
                    dp[i][j] += dp[i - 1][j - 1];
                }
            }

        return dp[m][n];
    }

    // 5
    bool isInterleave(string s1, string s2, string s3)
    {
        int m = s1.size(), n = s2.size();
        if (m + n != s3.size())
            return false;

        s1 = " " + s1;
        s2 = " " + s2;
        s3 = " " + s3;

        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1));
        dp[0][0] = true;
        for (int i = 1; i <= m; i++)
            if (s1[i] == s3[i])
                dp[i][0] = true;
            else
                break;

        for (int i = 1; i <= n; i++)
            if (s2[i] == s3[i])
                dp[0][i] = true;
            else
                break;

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                bool from_s1 = s1[i] == s3[i + j] && dp[i - 1][j];
                bool from_s2 = s2[j] == s3[i + j] && dp[i][j - 1];

                dp[i][j] = from_s1 || from_s2;
            }

        return dp[m][n];
    }
};