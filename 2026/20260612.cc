#include <bits/stdc++.h>
#include <mutex>
using namespace std;

class Solution
{
public:
    // 1
    int brokenCalc(int startValue, int target)
    {
        int ret = 0;

        while (target > startValue)
        {
            if (target % 2 == 0)
                target /= 2;
            else
                target++;
            ret++;
        }

        return ret + startValue - target;
    }

    // 2
    vector<int> rearrangeBarcodes(vector<int> &barcodes)
    {
        unordered_map<int, int> hash;
        int maxVal = 0, maxCount = 0;

        for (auto n : barcodes)
        {
            if (maxCount < ++hash[n])
            {
                maxCount = hash[n];
                maxVal = n;
            }
        }

        int n = barcodes.size(), index = 0;
        vector<int> ret(n);
        for (int i = 0; i < maxCount; i++)
        {
            ret[index] = maxVal;
            index += 2;
        }

        hash.erase(maxVal);
        for (auto [x, y] : hash)
            for (int i = 0; i < y; i++)
            {
                if (index > n - 1)
                    index = 1;

                ret[index] = x;
                index += 2;
            }

        return ret;
    }

    // 3
    int tribonacci(int n)
    {
        if (n <= 1)
            return n;

        if (n == 2)
            return 1;

        int dp4 = 0, dp1 = 1, dp2 = 1, dp3 = 2;
        while (n-- != 3)
        {
            dp4 = dp1 + dp2 + dp3;
            dp1 = dp2, dp2 = dp3, dp3 = dp4;
        }

        return dp3;
    }

    // 4
    int maxProfit(vector<int> &prices)
    {
        const int INF = 0x3f3f3f;
        int n = prices.size();
        vector<vector<int>> f(n, vector<int>(3, -INF));
        auto g = f;

        f[0][0] = -prices[0];
        g[0][0] = 0;
        for (int i = 1; i < n; i++)
            for (int j = 0; j < 3; j++)
            {
                f[i][j] = max(f[i - 1][j], g[i - 1][j] - prices[i]);
                g[i][j] = g[i - 1][j];

                if (j >= 1)
                    g[i][j] = max(g[i][j], f[i - 1][j - 1] + prices[i]);
            }

        int ret = 0;
        for (int i = 0; i < 3; i++)
            ret = max(ret, g[n - 1][i]);

        return ret;
    }

    // 5
    int maxSubArray(vector<int> &nums)
    {
        int n = nums.size(), ret = INT_MIN;
        vector<int> dp(n + 1);

        for (int i = 1; i <= n; i++)
        {
            dp[i] = max(dp[i - 1] + nums[i - 1], nums[i - 1]);
            ret = max(ret, dp[i]);
        }

        return ret;
    }

    // 6
    bool IsPopOrder(vector<int> &pushV, vector<int> &popV)
    {
        int n = pushV.size(), i = 0;
        stack<int> st;

        for (auto num : pushV)
        {
            st.push(num);
            while (st.size() && st.top() == popV[i])
            {
                st.pop();
                i++;
            }
        }

        return i == n;
    }
};