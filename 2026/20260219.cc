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
    bool increasingTriplet(vector<int> &nums)
    {
        int a = INT_MAX, b = nums[0];

        for (int i = 1; i < nums.size(); i++)
        {
            if (nums[i] > a)
                return true;
            else if (nums[i] > b)
                a = nums[i];
            else
                b = nums[i];
        }

        return false;
    }

    // 2
    TreeNode *pruneTree(TreeNode *root)
    {
        if (root == nullptr)
            return nullptr;

        root->left = pruneTree(root->left);
        root->right = pruneTree(root->right);

        if (root->left == nullptr && root->right == nullptr && root->val == 0)
            return nullptr;

        return root;
    }

    // 3
    int minCostClimbingStairs(vector<int> &cost)
    {
        int n = cost.size();
        vector<int> dp(n + 1);

        int ret = INT_MAX;
        for (int i = 2; i <= n; i++)
        {
            dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
        }

        return dp[n];
    }

    // 4
    typedef pair<TreeNode *, unsigned int> PTI;
    int widthOfBinaryTree(TreeNode *root)
    {
        vector<PTI> q;
        q.push_back({root, 1});

        unsigned int ret = 0;
        while (q.size())
        {
            vector<PTI> tmp;

            auto &[x1, y1] = q[0];
            auto &[x2, y2] = q.back();
            ret = max(ret, y2 - y1 + 1);

            for (auto &[x, y] : q)
            {
                if (x->left)
                    tmp.push_back({x->left, 2 * y});
                if (x->right)
                    tmp.push_back({x->right, 2 * y + 1});
            }

            q = tmp;
        }

        return ret;
    }

    // 5
    vector<vector<int>> ret;
    vector<int> path;
    bool vis[7];
    vector<vector<int>> permute(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        dfs(nums, 0);
        return ret;
    }

    void dfs(vector<int> &nums, int pos)
    {
        if (path.size() == nums.size())
        {
            ret.push_back(path);
            return;
        }

        for (int i = 0; i < nums.size(); i++)
        {
            if (!vis[i])
            {
                vis[i] = true;
                path.push_back(nums[i]);
                dfs(nums, i + 1);
                path.pop_back();
                vis[i] = false;
            }
        }
    }

    // 6
    int missingNumber(vector<int> &nums)
    {
        int ret = 0;
        for (auto n : nums)
            ret ^= n;
        for (int i = 1; i <= nums.size(); i++)
            ret ^= i;
        return ret;
    }

    // 7
    int maxProfit(vector<int> &prices)
    {
        int n = prices.size();
        vector<vector<int>> dp(n, vector<int>(3));
        dp[0][0] = -prices[0];

        for (int i = 1; i < n; i++)
        {
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] - prices[i]);
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][2]);
            dp[i][2] = dp[i - 1][0] + prices[i];
        }

        return max(dp[n - 1][1], dp[n - 1][2]);
    }
};