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
    int eraseOverlapIntervals(vector<vector<int>> &in)
    {
        sort(in.begin(), in.end());
        int n = in.size(), ret = 0, right = in[0][1];

        for (int i = 1; i < n; i++)
        {
            int a = in[i][0], b = in[i][1];

            if (a < right)
            {
                ret++;
                right = min(right, b);
            }
            else
                right = b;
        }

        return ret;
    }

    // 2
    int deleteAndEarn(vector<int> &nums)
    {
        const int N = 10001;
        int arr[N] = {0};

        for (auto n : nums)
            arr[n] += n;

        vector<int> f(N), g(N);
        for (int i = 1; i < N; i++)
        {
            g[i] = max(g[i - 1], f[i - 1]);
            f[i] = g[i - 1] + arr[i];
        }

        return max(f[N - 1], g[N - 1]);
    }

    // 3
    vector<vector<int>> ret;
    vector<int> path;
    vector<vector<int>> subsets(vector<int> &nums)
    {
        dfs(nums, 0);
        return ret;
    }

    void dfs(vector<int> &nums, int pos)
    {
        ret.push_back(path);

        if (pos == nums.size())
            return;

        for (int i = pos; i < nums.size(); i++)
        {
            path.push_back(nums[i]);
            dfs(nums, i + 1);
            path.pop_back();
        }
    }

    // 4
    int findLength(vector<int> &nums1, vector<int> &nums2)
    {
        int m = nums1.size(), n = nums2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        int ret = 0;
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                if (nums1[i - 1] == nums2[j - 1])
                {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    ret = max(ret, dp[i][j]);
                }

        return ret;
    }

    // 5
    string hash[10] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    vector<string> ret;
    string path;
    vector<string> letterCombinations(string digits)
    {
        dfs(digits, 0);
        return ret;
    }

    void dfs(string &digits, int pos)
    {
        if (pos == digits.size())
        {
            ret.push_back(path);
            return;
        }

        for (char ch : hash[digits[pos] - '0'])
        {
            path.push_back(ch);
            dfs(digits, pos + 1);
            path.pop_back();
        }
    }

    // 6
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

    // 7
    int m, n;
    int calculateMinimumHP(vector<vector<int>> &dungeon)
    {
        m = dungeon.size(), n = dungeon[0].size();

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
};