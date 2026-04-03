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
    int countSubstrings(string s)
    {
        int n = s.size(), ret = 0;
        vector<vector<bool>> isPal(n, vector<bool>(n));
        for (int i = n - 1; i >= 0; i--)
            for (int j = i; j < n; j++)
            {
                if (s[i] == s[j])
                    isPal[i][j] = j - i + 1 > 3 ? isPal[i + 1][j - 1] : true;

                if (isPal[i][j])
                    ret++;
            }
        return ret;
    }

    // 2
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder)
    {
        int i = postorder.size() - 1;
        return _buildTree(inorder, postorder, i, 0, inorder.size() - 1);
    }

    TreeNode *_buildTree(vector<int> &inorder, vector<int> &postorder, int &posti, int inBegin, int inEnd)
    {
        if (inBegin > inEnd)
            return nullptr;

        TreeNode *root = new TreeNode(postorder[posti]);

        int rooti = inBegin;
        while (rooti <= inEnd)
            if (postorder[posti] == inorder[rooti])
                break;
            else
                rooti++;

        --posti;
        root->right = _buildTree(inorder, postorder, posti, rooti + 1, inEnd);
        root->left = _buildTree(inorder, postorder, posti, inBegin, rooti - 1);
        return root;
    }

    // 3
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    int calculateMinimumHP(vector<vector<int>> &dungeon)
    {
        m = dungeon.size(), n = dungeon[0].size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, INT_MAX));
        dp[m][n - 1] = dp[m - 1][n] = 1;

        for (int i = m - 1; i >= 0; i--)
            for (int j = n - 1; j >= 0; j--)
            {
                int prev = min(dp[i + 1][j], dp[i][j + 1]);
                dp[i][j] = prev - dungeon[i][j];
                dp[i][j] = max(1, dp[i][j]);
            }

        return dp[0][0];
    }

    // 4
    double myPow(double x, int n)
    {
        long N = n;
        if (N < 0)
        {
            N = -N;
            x = 1 / x;
        }
        return dfs(x, N);
    }

    double dfs(double x, int n)
    {
        if (n == 0)
            return 1;
        if (n == 1)
            return x;

        double tmp = dfs(x, n / 2);

        return n % 2 == 0 ? tmp * tmp : tmp * tmp * x;
    }

    // 5
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        int i = 0;
        return _buildTree(preorder, inorder, i, 0, inorder.size() - 1);
    }

    TreeNode *_buildTree(vector<int> &preorder, vector<int> &inorder, int &prei, int inBegin, int inEnd)
    {
        if (inBegin > inEnd)
            return nullptr;

        TreeNode *root = new TreeNode(preorder[prei]);

        int rooti = inBegin;
        while (rooti <= inEnd)
            if (preorder[prei] == inorder[rooti])
                break;
            else
                rooti++;

        ++prei;
        root->left = _buildTree(preorder, inorder, prei, inBegin, rooti - 1);
        root->right = _buildTree(preorder, inorder, prei, rooti + 1, inEnd);
        return root;
    }

    // 6
    int jump(vector<int> &nums)
    {
        int n = nums.size(), cur = 0, far = 0, ret = 0;

        for (int i = 0; i < n - 1; i++)
        {
            far = max(far, i + nums[i]);

            if (i == cur)
            {
                cur = far;
                ret++;
                if (i == n - 1)
                    break;
            }
        }

        return ret;
    }

    // 7
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
};