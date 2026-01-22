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
    int minPathSum(vector<vector<int>> &grid)
    {
        int m = grid.size(), n = grid[0].size();

        vector<vector<int>> dp(m + 1, vector<int>(n + 1, INT_MAX));
        dp[0][1] = dp[1][0] = 0;

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                int prev = min(dp[i - 1][j], dp[i][j - 1]);

                dp[i][j] = prev + grid[i - 1][j - 1];
            }

        return dp[m][n];
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
    int findContentChildren(vector<int> &g, vector<int> &s)
    {
        // g:胃口 s:饼干尺寸
        int m = g.size(), n = s.size();
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());

        int ret = 0;
        for (int i = 0, j = 0; i < m && j < n; i++, j++)
        {
            while (j < n && s[j] < g[i])
                j++;
            if (j < n)
                ret++;
        }
        return ret;
    }

    // 4
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        int i = 0;
        return _buildTree(preorder, inorder, i, 0, inorder.size() - 1);
    }

    TreeNode *_buildTree(vector<int> &preorder, vector<int> &inorder,
                         int &previ, int inBegin, int inEnd)
    {
        if (inBegin > inEnd)
            return nullptr;

        TreeNode *root = new TreeNode(preorder[previ]);

        int rooti = inBegin;
        while (rooti <= inEnd)
            if (inorder[rooti] != preorder[previ])
                rooti++;
            else
                break;

        previ++;
        root->left = _buildTree(preorder, inorder, previ, inBegin, rooti - 1);
        root->right = _buildTree(preorder, inorder, previ, rooti + 1, inEnd);

        return root;
    }

    // 5
    bool isInterleave(string s1, string s2, string s3)
    {
        int m = s1.size(), n = s2.size();
        if (m + n != s3.size())
            return false;

        s1 = " " + s1;
        s2 = " " + s2;
        s3 = " " + s3;

        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1));
        dp[0][0] = true;
        for (int i = 1; i <= m; i++)
            if (s1[i] == s3[i])
                dp[i][0] = true;
            else
                break;

        for (int i = 1; i <= n; i++)
            if (s2[i] == s3[i])
                dp[0][i] = true;
            else
                break;

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                bool from_s1 = s1[i] == s3[i + j] && dp[i - 1][j];
                bool from_s2 = s2[j] == s3[i + j] && dp[i][j - 1];

                dp[i][j] = from_s1 || from_s2;
            }

        return dp[m][n];
    }

    // 6
    
};