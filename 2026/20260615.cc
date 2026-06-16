#include <bits/stdc++.h>
#include <mutex>
using namespace std;

class Solution
{
public:
    // 1
    int ret = 0, xorsum = 0;
    int subsetXORSum(vector<int> &nums)
    {
        dfs(nums, 0);
        return ret;
    }

    void dfs(vector<int> &nums, int pos)
    {
        ret += xorsum;

        if (pos == nums.size())
            return;

        for (int i = pos; i < nums.size(); i++)
        {
            xorsum ^= nums[i];
            dfs(nums, i + 1);
            xorsum ^= nums[i];
        }
    }

    // 2
    int integerReplacement(int n)
    {
        int ret = 0;
        while (n != 1)
        {
            if (n % 2 == 0)
            {
                n /= 2;
                ret++;
            }
            else if (n == 3)
            {
                n = 1;
                ret += 2;
            }
            else if (n % 4 == 1)
            {
                n /= 2;
                ret += 2;
            }
            else
            {
                n = n / 2 + 1;
                ret += 2;
            }
        }
        return ret;
    }

    // 3
    int findLength(vector<int> &nums1, vector<int> &nums2)
    {
        int m = nums1.size(), n = nums2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));

        int ret = 0;
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                if (nums1[i - 1] == nums2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                ret = max(ret, dp[i][j]);
            }

        return ret;
    }

    // 4
    int numSquares(int n)
    {
        int m = sqrt(n);
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));

        for (int i = 1; i <= n; i++)
            dp[0][i] = INT_MAX;

        for (int i = 1; i <= m; i++)
            for (int j = 0; j <= n; j++)
            {
                dp[i][j] = dp[i - 1][j];
                if (j >= i * i)
                    dp[i][j] = min(dp[i][j], dp[i][j - i * i] + 1);
            }

        return dp[m][n];
    }

    // 5
    bool wordBreak(string s, vector<string> &wordDict)
    {
        unordered_set<string> hash(wordDict.begin(), wordDict.end());

        int n = s.size();
        s = " " + s;
        vector<bool> dp(n + 1);
        dp[0] = true;

        for (int i = 1; i <= n; i++)
            for (int j = i; j >= 1; j--)
            {
                if (dp[j - 1] && hash.count(s.substr(j, i - j + 1)))
                {
                    dp[i] = true;
                    break;
                }
            }

        return dp[n];
    }

    // 6
    int maxTurbulenceSize(vector<int> &arr)
    {
        int n = arr.size(), ret = 1;
        vector<int> f(n, 1);
        auto g = f;

        for (int i = 1; i < n; i++)
        {
            if (arr[i - 1] > arr[i])
                f[i] = g[i - 1] + 1;
            else if (arr[i - 1] < arr[i])
                g[i] = f[i - 1] + 1;

            ret = max(ret, max(f[i], g[i]));
        }

        return ret;
    }

    // 7
    int findLongestChain(vector<vector<int>> &pairs)
    {
        sort(pairs.begin(), pairs.end());

        int n = pairs.size(), ret = 1;
        vector<int> dp(n, 1);

        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < i; j++)
            {
                int a = pairs[j][1], b = pairs[i][0];
                if (a < b)
                {
                    dp[i] = max(dp[i], dp[j] + 1);
                    // break;
                }
            }
            ret = max(ret, dp[i]);
        }

        return ret;
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