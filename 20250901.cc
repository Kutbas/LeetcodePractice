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
    int minFallingPathSum(vector<vector<int>> &matrix)
    {
        int m = matrix.size(), n = matrix[0].size();

        vector<vector<int>> dp(m + 1, vector<int>(n + 2, INT_MAX));
        for (int i = 0; i < n + 2; i++)
            dp[0][i] = 0;

        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i - 1][j + 1])) + matrix[i - 1][j - 1];

        int ret = INT_MAX;
        for (int i = 1; i <= n; i++)
            ret = min(ret, dp[m][i]);
        return ret;
    }

    // 1
    vector<vector<int>> ret;
    vector<int> path;
    vector<vector<int>> subsets(vector<int> &nums)
    {
        dfs(nums, 0);
        return ret;
    }

    void dfs(vector<int> &nums, int pos)
    {
        ret.push_back(path);

        if (pos == nums.size())
            return;

        for (int i = pos; i < nums.size(); i++)
        {
            path.push_back(nums[i]);
            dfs(nums, i + 1);
            path.pop_back();
        }
    }

    // 2
    string optimalDivision(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 1)
            return to_string(nums[0]);
        if (n == 2)
            return to_string(nums[0]) + "/" + to_string(nums[1]);

        string ret = to_string(nums[0]) + "/(" + to_string(nums[1]);
        for (int i = 2; i < n; i++)
            ret += "/" + to_string(nums[i]);

        ret += ")";

        return ret;
    }

    // 3
    int memo[101][101];
    int uniquePaths(int m, int n)
    {
        return dfs(m, n);
    }

    int dfs(int m, int n)
    {
        if (memo[m][n])
            return memo[m][n];
        if (m == 0 || n == 0)
            return 0;
        if (m == 1 && n == 1)
        {
            memo[m][n] = 1;
            return 1;
        }

        memo[m][n] = dfs(m - 1, n) + dfs(m, n - 1);
        return memo[m][n];
    }

    // 4
    int aim, Ret = 0;
    int findTargetSumWays(vector<int> &nums, int target)
    {
        aim = target;
        dfs(nums, 0, 0);
        return Ret;
    }

    void dfs(vector<int> &nums, int pos, int sum)
    {
        if (pos == nums.size())
        {
            if (sum == aim)
                Ret++;
            return;
        }

        dfs(nums, pos + 1, sum + nums[pos]);
        dfs(nums, pos + 1, sum - nums[pos]);
    }

    // 5
    vector<vector<int>> res;
    vector<int> path;
    int aim;
    vector<vector<int>> combinationSum(vector<int> &candidates, int target)
    {
        aim = target;
        DFS(candidates, 0, 0);
        return res;
    }

    void DFS(vector<int> &nums, int pos, int sum)
    {
        if (sum > aim || pos == nums.size())
            return;

        if (sum == aim)
        {
            res.push_back(path);
            return;
        }

        for (int i = pos; i < nums.size(); i++)
        {
            path.push_back(nums[i]);
            DFS(nums, i, sum + nums[i]);
            path.pop_back();
        }
    }

    // 6
    vector<vector<int>> zigzagLevelOrder(TreeNode *root)
    {
        vector<vector<int>> ret;
        if (root == nullptr)
            return ret;
            
        queue<TreeNode *> q;
        q.push(root);

        int n = 1;
        while (q.size())
        {
            vector<int> tmp;
            int sz = q.size();
            while (sz--)
            {
                auto t = q.front();
                q.pop();
                tmp.push_back(t->val);

                if (t->left)
                    q.push(t->left);
                if (t->right)
                    q.push(t->right);
            }

            if (n++ % 2 == 0)
                reverse(tmp.begin(), tmp.end());
            ret.push_back(tmp);
        }
        return ret;
    }
};