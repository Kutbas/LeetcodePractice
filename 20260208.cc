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
    vector<vector<int>> matrixBlockSum(vector<vector<int>> &mat, int k)
    {
        int m = mat.size(), n = mat[0].size();

        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1] + mat[i - 1][j - 1];

        vector<vector<int>> ret(m, vector<int>(n));
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                int x1 = max(0, i - k) + 1, y1 = max(0, j - k) + 1;
                int x2 = min(m - 1, i + k) + 1, y2 = min(n - 1, j + k) + 1;
                ret[i][j] = dp[x2][y2] - dp[x1 - 1][y2] - dp[x2][y1 - 1] + dp[x1 - 1][y1 - 1];
            }

        return ret;
    }

    // 2
    string tree2str(TreeNode *root)
    {
        if (root == nullptr)
            return "";

        string ret = to_string(root->val);
        if (root->left || root->right)
        {
            ret += "(";
            ret += tree2str(root->left);
            ret += ")";
        }

        if (root->right)
        {
            ret += "(";
            ret += tree2str(root->right);
            ret += ")";
        }

        return ret;
    }
};