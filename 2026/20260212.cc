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

    // 2
    vector<vector<int>> threeSum(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        vector<vector<int>> ret;

        int i = 0;
        while (i < n - 1)
        {
            int left = i + 1, right = n - 1;
            while (left < right)
            {
                if (nums[i] + nums[left] + nums[right] > 0)
                    right--;
                else if (nums[i] + nums[left] + nums[right] < 0)
                    left++;
                else
                {
                    ret.push_back({nums[i], nums[left], nums[right]});
                    do
                    {
                        left++;
                    } while (left < right && nums[left] == nums[left - 1]);
                    do
                    {
                        right--;
                    } while (left < right && nums[right] == nums[right + 1]);
                }
            }

            do
            {
                i++;
            } while (i < n - 1 && nums[i] == nums[i - 1]);
        }

        return ret;
    }

    // 3
    int calculateMinimumHP(vector<vector<int>> &dungeon)
    {
        int m = dungeon.size(), n = dungeon[0].size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, INT_MAX));

        dp[m][n - 1] = dp[m - 1][n] = 1;
        for (int i = m - 1; i >= 0; i--)
            for (int j = n - 1; j >= 0; j--)
            {
                int prev = min(dp[i + 1][j], dp[i][j + 1]);
                dp[i][j] = prev - dungeon[i][j];
                dp[i][j] = max(dp[i][j], 1);
            }

        return dp[0][0];
    }

    // 4
    vector<vector<string>> ret;
    vector<string> path;
    bool Col[10], Grid1[20], Grid2[20];
    int N;
    vector<vector<string>> solveNQueens(int n)
    {
        N = n;
        path.resize(n);
        for (int i = 0; i < n; i++)
            path[i].append(n, '.');

        dfs(0);

        return ret;
    }

    void dfs(int row)
    {
        if (row == N)
        {
            ret.push_back(path);
            return;
        }

        for (int col = 0; col < N; col++)
        {
            if (!Col[col] && !Grid1[row + col] && !Grid2[row - col + N])
            {
                path[row][col] = 'Q';
                Col[col] = Grid1[row + col] = Grid2[row - col + N] = true;
                dfs(row + 1);
                path[row][col] = '.';
                Col[col] = Grid1[row + col] = Grid2[row - col + N] = false;
            }
        }
    }

    // 5
    
};