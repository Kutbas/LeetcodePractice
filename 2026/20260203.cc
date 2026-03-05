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
    struct cmp
    {
        bool operator()(ListNode *&l1, ListNode *&l2)
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

    // 2
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

    // 3
    vector<int> twoSum(vector<int> &nums, int target)
    {
        unordered_map<int, int> hash;
        for (int i = 0; i < nums.size(); i++)
        {
            int x = target - nums[i];
            if (hash.count(x))
                return {i, hash[x]};
            hash[nums[i]] = i;
        }
        return {-1, -1};
    }

    // 4
    int maxSumDivThree(vector<int> &nums)
    {
        const int INF = 0x3f3f3f;
        int x1 = INF, x2 = INF, y1 = INF, y2 = INF;
        int sum = 0;

        for (auto n : nums)
        {
            sum += n;
            if (n % 3 == 1)
            {
                if (n < x1)
                    x2 = x1, x1 = n;
                else if (n < x2)
                    x2 = n;
            }
            else if (n % 3 == 2)
            {
                if (n < y1)
                    y2 = y1, y1 = n;
                else if (n < y2)
                    y2 = n;
            }
        }

        if (sum % 3 == 0)
            return sum;
        else if (sum % 3 == 1)
            return max(sum - x1, sum - y1 - y2);
        return max(sum - y1, sum - x1 - x2);
    }

    // 5
    int maxEnvelopes(vector<vector<int>> &e)
    {
        int n = e.size();
        sort(e.begin(), e.end(),
             [&](const vector<int> &v1, const vector<int> &v2)
             {
                 return v1[0] != v2[0] ? v1[0] < v2[0] : v1[1] > v2[1];
             });

        vector<int> ret;
        ret.push_back(e[0][1]);
        for (int i = 1; i < n; i++)
        {
            if (e[i][1] > ret.back())
                ret.push_back(e[i][1]);
            else
            {
                int left = 0, right = ret.size() - 1;
                while (left < right)
                {
                    int mid = left + (right - left) / 2;
                    if (e[i][1] > ret[mid])
                        left = mid + 1;
                    else
                        right = mid;
                }
                ret[left] = e[i][1];
            }
        }
        return ret.size();
    }

    // 6
    int maxProfit(vector<int> &prices)
    {
        int n = prices.size();
        vector<vector<int>> dp(n, vector<int>(3));
        dp[0][0] = -prices[0];
        // 0:持股 1：未持股 2：未持股冷冻期

        for (int i = 1; i < n; i++)
        {
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] - prices[i]);
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][2]);
            dp[i][2] = dp[i - 1][0] + prices[i];
        }

        return max(dp[n - 1][1], dp[n - 1][2]);
    }

    // 7
    int wiggleMaxLength(vector<int> &nums)
    {
        int n = nums.size(), left = 0, right = 0, ret = 0;

        for (int i = 0; i < n - 1; i++)
        {
            right = nums[i + 1] - nums[i];
            if (right == 0)
                continue;
            if (left * right <= 0)
                ret++;
            left = right;
        }
        return ret + 1;
    }
};