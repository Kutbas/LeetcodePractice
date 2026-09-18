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
    int ret = 0, N;
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

    // 2
    int getMaxLen(vector<int> &nums)
    {
        int n = nums.size();

        vector<int> f(n + 1);
        auto g = f;

        int ret = 0;
        for (int i = 1; i <= n; i++)
        {
            if (nums[i - 1] > 0)
            {
                f[i] = f[i - 1] + 1;
                g[i] = g[i - 1] == 0 ? 0 : g[i - 1] + 1;
            }
            else if (nums[i - 1] < 0)
            {
                f[i] = g[i - 1] == 0 ? 0 : g[i - 1] + 1;
                g[i] = f[i - 1] + 1;
            }
            ret = max(ret, f[i]);
        }

        return ret;
    }

    // 3
    int findLongestChain(vector<vector<int>> &pairs)
    {
        sort(pairs.begin(), pairs.end());

        int n = pairs.size(), ret = 1;
        vector<int> dp(n, 1);
        for (int i = 1; i < n; i++)
            for (int j = 0; j < i; j++)
            {
                if (pairs[j][1] < pairs[i][0])
                    dp[i] = dp[j] + 1;
                ret = max(ret, dp[i]);
            }

        return ret;
    }

    // 4
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
                    if (isPal[j][i])
                        dp[i] = min(dp[i], dp[j - 1] + 1);
            }
        }

        return dp[n - 1];
    }

    // 5
    bool isInterleave(string s1, string s2, string s3)
    {
        int m = s1.size(), n = s2.size();
        if (m + n != s3.size())
            return false;

        s1 = " " + s1, s2 = " " + s2, s3 = " " + s3;
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1));
        dp[0][0] = true;

        for (int i = 1; i <= m; i++)
            if (s1[i] == s3[i])
                dp[i][0] = dp[i - 1][0];
            else
                break;

        for (int i = 1; i <= n; i++)
            if (s2[i] == s3[i])
                dp[0][i] = dp[0][i - 1];
            else
                break;

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                bool case1 = s1[i] == s3[i + j] && dp[i - 1][j];
                bool case2 = s2[j] == s3[i + j] && dp[i][j - 1];
                dp[i][j] = case1 || case2;
            }

        return dp[m][n];
    }
};