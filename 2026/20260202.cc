
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
    int deleteAndEarn(vector<int> &nums)
    {
        const int N = 10001;
        int arr[N] = {0};
        for (auto n : nums)
            arr[n] += n;

        vector<int> f(N), g(N);
        for (int i = 1; i < N; i++)
        {
            g[i] = max(f[i - 1], g[i - 1]);
            f[i] = g[i - 1] + arr[i];
        }

        return max(f[N - 1], g[N - 1]);
    }

    // 2
    int ret = 0;
    int sumNumbers(TreeNode *root)
    {
        dfs(root, 0);
        return ret;
    }

    void dfs(TreeNode *root, int tmp)
    {
        tmp = tmp * 10 + root->val;

        if (root->left == nullptr && root->right == nullptr)
        {
            ret += tmp;
            return;
        }

        if (root->left)
            dfs(root->left, tmp);
        if (root->right)
            dfs(root->right, tmp);
    }

    // 3
    int longestOnes(vector<int> &nums, int k)
    {
        int ret = 0;
        for (int left = 0, right = 0, count = 0; right < nums.size(); right++)
        {
            if (nums[right] == 0)
                count++;
            while (count > k)
                if (nums[left++] == 0)
                    count--;
            ret = max(ret, right - left + 1);
        }
        return ret;
    }

    // 4
    int maxProfit(vector<int> &prices)
    {
        int n = prices.size();
        vector<vector<int>> dp(n, vector<int>(3));
        dp[0][0] = -prices[0];
        // dp[i][0]:持股中 dp[i][1]:不持股，可购买 dp[i][2]:不持股，冷冻期

        for (int i = 1; i < n; i++)
        {
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] - prices[i]);
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][2]);
            dp[i][2] = dp[i - 1][0] + prices[i];
        }

        return max(dp[n - 1][1], dp[n - 1][2]);
    }

    // 5
    int findLength(vector<int> &nums1, vector<int> &nums2)
    {
        int m = nums1.size(), n = nums2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));

        int ret = 0;
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                if (nums1[i - 1] == nums2[j - 1])
                {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    ret = max(ret, dp[i][j]);
                }

        return ret;
    }
};