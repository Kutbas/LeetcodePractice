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

    // 2
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
                dp[i][j] = dp[i][j - 1];
                if (t[i] == s[j])
                    dp[i][j] += dp[i - 1][j - 1];
            }

        return dp[m][n];
    }

    // 3
    bool isMatch(string s, string p)
    {
        int m = s.size(), n = p.size();
        s = " " + s, p = " " + p;

        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1));
        dp[0][0] = true;
        for (int i = 2; i <= n; i += 2)
            if (p[i] == '*')
                dp[0][i] = true;
            else
                break;

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                if (p[j] == '*')
                {
                    bool case1 = dp[i][j - 2];
                    bool case2 = (p[j - 1] == '.' || p[j - 1] == s[i]) && dp[i - 1][j];
                    dp[i][j] = case1 || case2;
                }
                else
                    dp[i][j] = (p[j] == '.' || p[j] == s[i]) && dp[i - 1][j - 1];
            }

        return dp[m][n];
    }

    // 4
    int numSquares(int n)
    {
        int m = sqrt(n);
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));

        for (int i = 1; i <= n; i++)
            dp[0][i] = INT_MAX;

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                dp[i][j] = dp[i - 1][j];
                if (j >= i * i)
                    dp[i][j] = min(dp[i][j], dp[i][j - i * i] + 1);
            }

        return dp[m][n];
    }

    // 5
    int findLongestChain(vector<vector<int>> &pairs)
    {
        // 1. 按区间起点排序（默认先按第一个元素，再按第二个）
        sort(pairs.begin(), pairs.end());
        int n = pairs.size();

        // 2. dp[i] 表示以第 i 个区间结尾的最长链长度
        vector<int> dp(n, 1); // 初始化为 1，每个区间自身就是长度为 1 的链
        int ret = 1;          // 记录全局最大长度

        // 3. 遍历每个区间，尝试接在前面可行的区间后面
        for (int i = 1; i < n; i++)
        {
            // 检查所有在 i 前面的区间 j
            for (int j = 0; j < i; j++)
            {
                // 如果区间 j 的右端点 严格小于 区间 i 的左端点
                // 说明它们可以连接成链
                if (pairs[j][1] < pairs[i][0])
                    // 更新 dp[i]：要么保持原值，要么从 j 接过来
                    dp[i] = max(dp[j] + 1, dp[i]);
            }
            // 用当前 dp[i] 更新全局最优解
            ret = max(ret, dp[i]);
        }

        // 4. 返回最长链的长度
        return ret;
    }
};