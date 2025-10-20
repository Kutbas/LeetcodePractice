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
    int maxProfit(vector<int> &prices)
    {
        int ret = 0, n = prices.size();

        for (int i = 0; i < n;)
        {
            int j = i;
            while (j + 1 < n && prices[j + 1] > prices[j])
                j++;
            ret += prices[j] - prices[i];
            i = j + 1;
        }

        return ret;
    }

    // 2
    int searchInsert(vector<int> &nums, int target)
    {
        int left = 0, right = nums.size() - 1;

        while (left < right)
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] < target)
                left = mid + 1;
            else
                right = mid;
        }

        return nums[left] < target ? left + 1 : left;
    }

    // 3
    int findLengthOfLCIS(vector<int> &nums)
    {
        int n = nums.size(), ret = 0;

        for (int i = 0; i < n;)
        {
            int j = i + 1;
            while (j < n && nums[j] > nums[j - 1])
                j++;
            ret = max(ret, j - i);
            i = j;
        }
        return ret;
    }

    // 4
    int subarraySum(vector<int> &nums, int k)
    {
        int sum = 0, ret = 0;
        unordered_map<int, int> hash;
        hash[0] = 1;

        for (auto n : nums)
        {
            sum += n;
            if (hash.count(sum - k))
                ret += hash[sum - k];
            hash[sum]++;
        }

        return ret;
    }

    // 5
    struct cmp
    {
        bool operator()(const ListNode *l1, const ListNode *l2)
        {
            return l1->val > l2->val;
        }
    };

    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        priority_queue<ListNode *, vector<ListNode *>, cmp> q;
        for (auto &list : lists)
            if (list)
                q.push(list);

        ListNode *ret = new ListNode(0);
        ListNode *prev = ret;

        while (q.size())
        {
            auto t = q.top();
            q.pop();

            prev->next = t;
            prev = prev->next;

            if (t->next)
                q.push(t->next);
        }

        prev = ret->next;
        delete ret;
        return prev;
    }

    // 6
    int jump(vector<int> &nums)
    {
        int n = nums.size(), ret = 0, left = 0, right = 0, maxPos = 0;

        while (left <= right)
        {
            if (maxPos >= n - 1)
                return ret;

            for (int i = left; i <= right; i++)
                maxPos = max(maxPos, i + nums[i]);

            left = right + 1;
            right = maxPos;
            ret++;
        }

        return -1;
    }

    const int INF = 0x3f3f3f;
    int coinChange(vector<int> &coins, int amount)
    {
        int n = coins.size();
        vector<vector<int>> dp(n + 1, vector<int>(amount + 1));

        for (int j = 1; j <= amount; j++)
            dp[0][j] = INF;
        for (int i = 1; i <= n; i++)
            for (int j = 0; j <= amount; j++)
            {
                dp[i][j] = dp[i - 1][j];
                if (j >= coins[i - 1])
                    dp[i][j] = min(dp[i][j], dp[i][j - coins[i - 1]] + 1);
            }

        return dp[n][amount] >= INF ? -1 : dp[n][amount];
    }
};
