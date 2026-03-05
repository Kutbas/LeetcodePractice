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
    int removeDuplicates(vector<int> &nums)
    {
        int n = nums.size(), slow = 1, fast = 1;

        while (fast < n)
        {
            if (nums[fast - 1] != nums[fast])
                nums[slow++] = nums[fast];
            fast++;
        }
        return slow;
    }

    // 2
    vector<vector<int>> levelOrder(TreeNode *root)
    {
        vector<vector<int>> ret;
        if (root == nullptr)
            return ret;

        queue<TreeNode *> q;
        q.push(root);
        while (q.size())
        {
            int sz = q.size();
            vector<int> tmp;
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
            ret.push_back(tmp);
        }

        return ret;
    }

    // 3
    int maxProfit(vector<int> &prices)
    {
        int n = prices.size();
        vector<vector<int>> dp(n, vector<int>(3));
        dp[0][0] = -prices[0];
        // 0：持有 1：未持有 2：未持有冷静期

        for (int i = 1; i < n; i++)
        {
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] - prices[i]);
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][2]);
            dp[i][2] = dp[i - 1][0] + prices[i];
        }

        return max(dp[n - 1][1], dp[n - 1][2]);
    }

    // 4
    int minOperations(vector<int> &nums, int x)
    {
        int sum = 0;
        for (auto n : nums)
            sum += n;

        int aim = sum - x, ret = INT_MIN;
        if (aim < 0)
            return -1;

        for (int left = 0, right = 0, tmp = 0; right < nums.size(); right++)
        {
            tmp += nums[right];
            while (tmp > aim)
                tmp -= nums[left++];
            if (tmp == aim)
                ret = max(ret, right - left + 1);
        }

        return ret == INT_MIN ? -1 : nums.size() - ret;
    }

    // 5
    int combinationSum4(vector<int> &nums, int target)
    {
        int n = nums.size();
        vector<double> dp(target + 1);
        dp[0] = 1;

        for (int i = 1; i <= target; i++)
            for (auto x : nums)
                if (i >= x)
                    dp[i] += dp[i - x];
        return dp[target];
    }
};