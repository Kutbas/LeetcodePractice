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
    int mySqrt(int x)
    {
        if (x < 1)
            return 0;

        int left = 1, right = x;
        while (left < right)
        {
            double mid = left + (right - left + 1) / 2;
            if (mid * mid <= x)
                left = mid;
            else
                right = mid - 1;
        }

        return left;
    }

    // 2
    string decodeString(string s)
    {
        stack<int> nums;
        int n = 0;
        stack<string> str;
        string ret;

        for (char ch : s)
        {
            if (isdigit(ch))
                n = n * 10 + (ch - '0');
            else if (ch == '[')
            {
                str.push(ret);
                ret = "";
                nums.push(n);
                n = 0;
            }
            else if (ch == ']')
            {
                int k = nums.top();
                nums.pop();
                string tmp = str.top();
                str.pop();
                while (k--)
                    tmp += ret;
                ret = tmp;
            }
            else
                ret += ch;
        }

        return ret;
    }

    // 3
    int m, n;
    bool vis[101][101] = {0};
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int getMaximumGold(vector<vector<int>> &grid)
    {
        m = grid.size(), n = grid[0].size();
        int ret = 0;

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j])
                {
                    vis[i][j] = true;
                    ret = max(ret, grid[i][j] + dfs(grid, i, j));
                    vis[i][j] = false;
                }
            }

        return ret;
    }

    int dfs(vector<vector<int>> &grid, int i, int j)
    {
        int ret = 0;

        for (int k = 0; k < 4; k++)
        {
            int x = i + dx[k], y = j + dy[k];
            if (x >= 0 && x < m && y >= 0 && y < n && grid[x][y] && !vis[x][y])
            {
                vis[x][y] = true;
                ret = max(ret, grid[x][y] + dfs(grid, x, y));
                vis[x][y] = false;
            }
        }

        return ret;
    }

    // 4
    int maxProfit(vector<int> &prices)
    {
        int n = prices.size();
        vector<int> f(n), g(n), c(n);
        f[0] = -prices[0];

        for (int i = 1; i < n; i++)
        {
            f[i] = max(f[i - 1], g[i - 1] - prices[i]);
            g[i] = max(g[i - 1], c[i - 1]);
            c[i] = f[i - 1] + prices[i];
        }

        return max(g[n - 1], c[n - 1]);
    }

    // 5
    int longestSubsequence(vector<int> &arr, int difference)
    {
        int n = arr.size(), ret = 0;
        unordered_map<int, int> hash;
        hash[arr[0]] = 1;

        for (int i = 1; i < n; i++)
        {
            hash[arr[i]] = hash[arr[i] - difference] + 1;
            ret = max(ret, hash[arr[i]]);
        }

        return ret;
    }

    // 6
    int minCut(string s)
    {
        int n = s.size();
        vector<vector<bool>> isPal(n, vector<bool>(n));
        for (int i = n - 1; i >= 0; i--)
            for (int j = i; j < n; j++)
                if (s[i] == s[j])
                    isPal[i][j] = j - i + 1 > 3 ? isPal[i + 1][j - 1] : true;

        vector<int> dp(n, INT_MAX);
        for (int i = 0; i < n; i++)
        {
            if (isPal[0][i])
                dp[i] = 0;
            else
            {
                for (int j = 1; j <= i; j++)
                {
                    if (isPal[j][i])
                        dp[i] = min(dp[i], dp[j - 1] + 1);
                }
            }
        }

        return dp[n - 1];
    }

    // 7
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

    // 8
    int maxUncrossedLines(vector<int> &nums1, vector<int> &nums2)
    {
        int m = nums1.size(), n = nums2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                if (nums1[i - 1] == nums2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }

        return dp[m][n];
    }
};