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
    bool isMatch(string s, string p)
    {
        int m = s.size(), n = p.size();
        s = " " + s;
        p = " " + p;
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

    // 2
    vector<int> sortArray(vector<int> &nums)
    {
        srand(time(nullptr));
        quickSort(nums, 0, nums.size() - 1);
        return nums;
    }

    int getRandom(vector<int> &nums, int left, int right)
    {
        int r = rand();
        return nums[r % (right - left + 1) + left];
    }

    void quickSort(vector<int> &nums, int l, int r)
    {
        if (l >= r)
            return;

        int key = getRandom(nums, l, r);
        int left = l - 1, right = r + 1, i = l;
        while (i < right)
        {
            if (nums[i] < key)
                swap(nums[i++], nums[++left]);
            else if (nums[i] == key)
                i++;
            else
                swap(nums[i], nums[--right]);
        }

        quickSort(nums, l, left);
        quickSort(nums, right, r);
    }

    // 3
    int numDistinct(string s, string t)
    {
        int m = t.size(), n = s.size();
        vector<vector<double>> dp(m + 1, vector<double>(n + 1));
        for (int i = 0; i <= n; i++)
            dp[0][i] = 1;

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                dp[i][j] = dp[i][j - 1];

                if (t[i - 1] == s[j - 1])
                    dp[i][j] += dp[i - 1][j - 1];
            }

        return dp[m][n];
    }

    // 4
    int profitableSchemes(int n, int m, vector<int> &group, vector<int> &profit)
    {
        const int MOD = 1e9 + 7;
        int len = group.size();
        vector<vector<vector<int>>> dp(len + 1, vector<vector<int>>(n + 1, vector<int>(m + 1)));
        for (int i = 0; i <= n; i++)
            dp[0][i][0] = 1;

        for (int i = 1; i <= len; i++)
            for (int j = 0; j <= n; j++)
                for (int k = 0; k <= m; k++)
                {
                    dp[i][j][k] += dp[i - 1][j][k];

                    if (j >= group[i - 1])
                    {
                        int remain = max(0, k - profit[i - 1]);
                        dp[i][j][k] += dp[i - 1][j - group[i - 1]][remain];
                    }

                    dp[i][j][k] %= MOD;
                }

        return dp[len][n][m];
    }

    // 5
    int countSubstrings(string s)
    {
        int n = s.size(), ret = 0;
        vector<vector<bool>> dp(n, vector<bool>(n));
        for (int i = n - 1; i >= 0; i--)
            for (int j = i; j < n; j++)
            {
                if (s[i] == s[j])
                    dp[i][j] = j - i + 1 > 3 ? dp[i + 1][j - 1] : true;

                if (dp[i][j])
                    ret++;
            }

        return ret;
    }
};