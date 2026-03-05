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
    bool validateStackSequences(vector<int> &pushed, vector<int> &popped)
    {
        stack<int> st;
        int n = pushed.size(), i = 0;

        for (auto n : pushed)
        {
            st.push(n);

            while (st.size() && st.top() == popped[i])
            {
                st.pop();
                i++;
            }
        }

        return i == n;
    }

    // 2
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    int memo[201][201];
    int longestIncreasingPath(vector<vector<int>> &matrix)
    {
        m = matrix.size(), n = matrix[0].size();

        int ret = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                ret = max(ret, 1 + dfs(matrix, i, j));

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
            if (x >= 0 && x < m && y >= 0 && y < n && matrix[x][y] > matrix[i][j])
                ret = max(ret, 1 + dfs(matrix, x, y));
        }

        memo[i][j] = ret;
        return ret;
    }

    // 3
    int ret = 0;
    int sumNumbers(TreeNode *root)
    {
        dfs(root, 0);
        return ret;
    }

    void dfs(TreeNode *root, int path)
    {
        path = path * 10 + root->val;

        if (root->left == nullptr && root->right == nullptr)
        {
            ret += path;
            return;
        }

        if (root->left)
            dfs(root->left, path);
        if (root->right)
            dfs(root->right, path);
    }

    // 4
    vector<int> missingTwo(vector<int> &nums)
    {
        int xorsum = 0;
        for (auto n : nums)
            xorsum ^= n;
        for (int i = 1; i <= nums.size() + 2; i++)
            xorsum ^= i;

        int lsb = xorsum == INT_MIN ? xorsum : xorsum & (-xorsum);
        int x = 0, y = 0;
        for (auto n : nums)
        {
            if (n & lsb)
                x ^= n;
            else
                y ^= n;
        }
        for (int i = 1; i <= nums.size() + 2; i++)
        {
            if (i & lsb)
                x ^= i;
            else
                y ^= i;
        }

        return {x, y};
    }

    int combinationSum4(vector<int> &nums, int target)
    {
        vector<double> dp(target + 1);
        dp[0] = 1;

        for (int i = 1; i <= target; i++)
            for (auto x : nums)
                if (i >= x)
                    dp[i] += dp[i - x];

        return dp[target];
    }

    int numTrees(int n)
    {
        vector<int> dp(n + 1);
        dp[0] = 1;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= i; j++)
                dp[i] += dp[i - j] * dp[j - 1];

        return dp[n];
    }
};