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
    int sum = 0, xorsum = 0;
    int subsetXORSum(vector<int> &nums)
    {
        dfs(nums, 0);
        return sum;
    }

    void dfs(vector<int> &nums, int pos)
    {
        sum += xorsum;

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
    vector<int> largestValues(TreeNode *root)
    {
        vector<int> ret;
        if (root == nullptr)
            return ret;
        queue<TreeNode *> q;
        q.push(root);

        while (q.size())
        {
            int sz = q.size();
            int tmp = INT_MIN;
            while (sz--)
            {
                auto t = q.front();
                q.pop();
                tmp = max(tmp, t->val);

                if (t->left)
                    q.push(t->left);
                if (t->right)
                    q.push(t->right);
            }
            ret.push_back(tmp);
        }
        return ret;
    }

    // 3
    int numDecodings(string s)
    {
        int n = s.size();

        vector<int> dp(n);
        dp[0] = s[0] == '0' ? 0 : 1;
        if (n == 1)
            return dp[0];

        if (s[0] != '0' && s[1] != '0')
            dp[1] += 1;

        int twoDigits = (s[0] - '0') * 10 + (s[1] - '0');
        if (twoDigits >= 10 && twoDigits <= 26)
            dp[1] += 1;

        for (int i = 2; i < n; i++)
        {
            if (s[i] != '0')
                dp[i] += dp[i - 1];

            int twoDigits = (s[i - 1] - '0') * 10 + (s[i] - '0');
            if (twoDigits >= 10 && twoDigits <= 26)
                dp[i] += dp[i - 2];
        }

        return dp[n - 1];
    }

    // 4
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    bool vis[201][201];
    int memo[201][201];
    int longestIncreasingPath(vector<vector<int>> &matrix)
    {
        m = matrix.size(), n = matrix[0].size();

        int ret = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                vis[i][j] = true;
                ret = max(ret, 1 + dfs(matrix, i, j));
                vis[i][j] = false;
            }

        return ret;
    }

    int dfs(vector<vector<int>> &matrix, int i, int j)
    {
        if (memo[i][j])
            return memo[i][j];

        int ret = 0;
        for (int k = 0; k < 4; k++)
        {
            int x = i + dx[k], y = j + dy[k];
            if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && matrix[x][y] > matrix[i][j])
            {
                vis[x][y] = true;
                ret = max(ret, 1 + dfs(matrix, x, y));
                vis[x][y] = false;
            }
        }

        memo[i][j] = ret;
        return ret;
    }

    // 5
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
};