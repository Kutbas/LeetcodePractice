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

    // 2
    int eraseOverlapIntervals(vector<vector<int>> &in)
    {
        sort(in.begin(), in.end());
        int n = in.size(), right = in[0][1], ret = 0;

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

    // 3
    string addStrings(string num1, string num2)
    {
        int m = num1.size(), n = num2.size();
        int cur1 = m - 1, cur2 = n - 1, t = 0;
        string ret;

        while (cur1 >= 0 || cur2 >= 0 || t)
        {
            if (cur1 >= 0)
                t += num1[cur1--] - '0';
            if (cur2 >= 0)
                t += num2[cur2--] - '0';
            ret += to_string(t % 10);
            t /= 10;
        }

        reverse(ret.begin(), ret.end());
        return ret;
    }

    // 4
    int myAtoi(string str)
    {
        // ret: 存储转换结果
        // bndry: INT_MAX / 10，用来预判乘以10后是否会溢出
        int ret = 0, bndry = INT_MAX / 10;

        int cur = 0, sign = 1, n = str.size();

        // 空字符串，直接返回0
        if (n == 0)
            return 0;

        // 1. 跳过前导空格
        while (str[cur] == ' ')
            if (++cur == n)
                return 0; // 全是空格也返回0

        // 2. 跳过符号位
        if (str[cur] == '-' || str[cur] == '+')
        {
            // 判断正负号
            if (str[cur++] == '-')
                sign = -1;
        }

        // 3. 逐位转换数字
        for (int i = cur; i < n; i++)
        {
            // 非数字字符，停止转换
            if (!isdigit(str[i]))
                break;

            // 溢出预判：
            // ret > bndry 时，res * 10 一定超过 INT_MAX
            // ret == bndry 且当前数字 > 7 时，会超过 INT_MAX（2147483647）
            if (ret > (INT_MAX - (str[i] - '0')) / 10)
                return sign == 1 ? INT_MAX : INT_MIN;

            // 安全累加：字符转数字并加到末位
            ret = ret * 10 + (str[i] - '0');
        }

        // 4. 返回带符号的结果
        return sign * ret;
    }
};