#include <bits/stdc++.h>
#include <mutex>
using namespace std;

class Solution
{
public:
    // 1
    vector<int> missingTwo(vector<int> &nums)
    {
        int xorsum = 0;

        for (auto n : nums)
            xorsum ^= n;
        for (int i = 1; i <= nums.size() + 2; i++)
            xorsum ^= i;

        int lsb = xorsum == INT_MIN ? xorsum : xorsum & (-xorsum);
        int x = 0, y = 0;
        for (auto n : nums)
        {
            if (n & lsb)
                x ^= n;
            else
                y ^= n;
        }

        for (int i = 1; i <= nums.size() + 2; i++)
        {
            if (i & lsb)
                x ^= i;
            else
                y ^= i;
        }

        return {x, y};
    }

    // 2
    int halveArray(vector<int> &nums)
    {
        priority_queue<double> q;
        double sum = 0;

        for (auto n : nums)
        {
            q.push(n);
            sum += n;
        }

        int ret = 0;
        double aim = sum / 2.0;
        while (sum > aim)
        {
            auto t = q.top();
            q.pop();
            sum -= t / 2.0;
            q.push(t / 2.0);
            ret++;
        }

        return ret;
    }

    // 3
    int longestPalindromeSubseq(string s)
    {
        int n = s.size();
        s = " " + s;
        vector<vector<int>> dp(n + 1, vector<int>(n + 1));

        for (int i = n; i >= 1; i--)
            for (int j = i; j <= n; j++)
            {
                if (s[i] == s[j])
                    dp[i][j] = i == j ? 1 : dp[i + 1][j - 1] + 2;
                else
                    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
            }

        return dp[1][n];
    }

    // 4
    bool isMatch(string s, string p)
    {
        int m = s.size(), n = p.size();
        s = " " + s, p = " " + p;
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1));
        dp[0][0] = true;

        for (int i = 1; i <= n; i++)
            if (p[i] == '*')
                dp[0][i] = true;
            else
                break;

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                if (p[j] == '*')
                {
                    dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
                }
                else
                    dp[i][j] =
                        (p[j] == '?' || p[j] == s[i]) && dp[i - 1][j - 1];
            }

        return dp[m][n];
    }

    // 5
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
};