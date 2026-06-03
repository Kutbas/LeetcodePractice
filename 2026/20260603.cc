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
    vector<int> rearrangeBarcodes(vector<int> &barcodes)
    {
        unordered_map<int, int> hash;
        int maxVal = 0, maxCount = 0;

        for (auto n : barcodes)
            if (maxCount < ++hash[n])
            {
                maxCount = hash[n];
                maxVal = n;
            }

        int n = barcodes.size(), index = 0;
        vector<int> ret(n);
        for (int i = 0; i < maxCount; i++)
        {
            ret[index] = maxVal;
            index += 2;
        }

        hash.erase(maxVal);
        for (auto &[x, y] : hash)
            for (int i = 0; i < y; i++)
            {
                if (index >= n)
                    index = 1;
                ret[index] = x;
                index += 2;
            }

        return ret;
    }

    // 2
    int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid)
    {
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        dp[0][1] = 1;

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                if (obstacleGrid[i - 1][j - 1] == 0)
                    dp[i][j] += dp[i - 1][j] + dp[i][j - 1];
            }

        return dp[m][n];
    }

    // 3
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

    // 4
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
                    dp[i] = max(dp[i], dp[j] + 1);
            }
            ret = max(ret, dp[i]);
        }

        return ret;
    }

    // 5
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

    // 6
    int myAtoi(string str)
    {
        int n = str.size(), sign = 1, cur = 0;

        while (cur < n)
            if (str[cur] == ' ')
                cur++;
            else
                break;

        if (str[cur] == '+' || str[cur] == '-')
        {
            if (str[cur] == '-')
                sign = -1;
            cur++;
        }

        int ret = 0;
        for (int i = cur; i < n; i++)
        {
            if (!isdigit(str[i]))
                break;

            if (ret > (INT_MAX - (str[i] - '0')) / 10)
                return sign == 1 ? INT_MAX : INT_MIN;

            ret = ret * 10 + (str[i] - '0');
        }

        return ret * sign;
    }

    // 7
    int MoreThanHalfNum_Solution(vector<int> &numbers)
    {
        int ret = numbers[0], count = 1, n = numbers.size();

        for (int i = 1; i < n; i++)
        {
            if (numbers[i] == ret)
                count++;
            else if (--count == 0)
            {
                ret = numbers[i];
                count = 1;
            }
        }

        return ret;
    }

    // 8
    vector<int> ret;
    vector<int> preorderTraversal(TreeNode *root)
    {
        if (root == nullptr)
            return ret;

        dfs(root);

        return ret;
    }

    void dfs(TreeNode *root)
    {
        if (root == nullptr)
            return;

        ret.push_back(root->val);
        dfs(root->left);
        dfs(root->right);
    }

    // 9
    string reverseWords(string s)
    {
        int n = s.size();
        int start = 0;

        for (int i = 0; i <= n; i++)
        {
            if (i == n || s[i] == ' ')
            {
                reverse(s.begin() + start, s.begin() + i);
                start = i + 1;
            }
        }

        return s;
    }
};