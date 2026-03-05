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
    int calculateMinimumHP(vector<vector<int>> &dungeon)
    {
        int m = dungeon.size(), n = dungeon[0].size();

        vector<vector<int>> dp(m + 1, vector<int>(n + 1, INT_MAX));
        dp[m][n - 1] = dp[m - 1][n] = 1;

        for (int i = m - 1; i >= 0; i--)
            for (int j = n - 1; j >= 0; j--)
            {
                int min_required = min(dp[i + 1][j], dp[i][j + 1]);

                dp[i][j] = min_required - dungeon[i][j];

                dp[i][j] = max(1, dp[i][j]);
            }

        return dp[0][0];
    }

    // 2
    int findSubstringInWraproundString(string s)
    {
        int n = s.size();
        vector<int> dp(n, 1);
        for (int i = 1; i < n; i++)
            if (s[i - 1] + 1 == s[i] || (s[i - 1] == 'z' && s[i] == 'a'))
                dp[i] += dp[i - 1];

        int hash[26] = {0};
        for (int i = 0; i < n; i++)
        {
            int index = s[i] - 'a';
            hash[index] = max(hash[index], dp[i]);
        }

        int sum = 0;
        for (int i = 0; i < 26; i++)
            sum += hash[i];

        return sum;
    }

    // 3
    int removeDuplicates(vector<int> &nums)
    {
        int n = nums.size();
        int slow = 1, fast = 1;

        while (fast < n)
        {
            if (nums[fast] != nums[fast - 1])
                nums[slow++] = nums[fast];

            fast++;
        }

        return slow;
    }

    // 4
    int findLengthOfLCIS(vector<int> &nums)
    {
        int n = nums.size(), ret = 0;

        for (int left = 0, right = 0; right < n; right++)
        {
            while (right + 1 < n && nums[right + 1] > nums[right])
                right++;
            ret = max(ret, right - left + 1);
            left = right + 1;
        }

        return ret;
    }

    // 5
    int getSum(int a, int b)
    {
        while (b)
        {
            int tmp = a ^ b;
            int carry = (a & b) << 1;
            a = tmp, b = carry;
        }

        return a;
    }

    // 6
    int profitableSchemes(int n, int m, vector<int> &group, vector<int> &profit)
    {
        const int MOD = 1e9 + 7;
        int len = group.size();

        vector<vector<vector<int>>> dp(len + 1, vector<vector<int>>(n + 1, vector<int>(m + 1, 0)));

        for (int j = 0; j <= n; j++)
            dp[0][j][0] = 1;

        for (int i = 1; i <= len; i++)
            for (int j = 0; j <= n; j++)
                for (int k = 0; k <= m; k++)
                {
                    dp[i][j][k] = dp[i - 1][j][k];

                    if (j >= group[i - 1])
                    {
                        int remain = max(0, k - profit[i - 1]);

                        dp[i][j][k] += dp[i - 1][j - group[i - 1]][remain];
                    }

                    dp[i][j][k] %= MOD;
                }

        return dp[len][n][m];
    }
};