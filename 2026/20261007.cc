#include <mutex>
#include <vector>
#include <algorithm>
#include <climits>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <iostream>
#include <sstream>
#include <regex>
#include <map>
#include <set>
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
        bool operator()(const ListNode *l1, const ListNode *l2)
        {
            return l1->val > l2->val;
        }
    };

    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        priority_queue<ListNode *, vector<ListNode *>, cmp> q;

        for (auto list : lists)
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
    vector<int> diStringMatch(string s)
    {
        int n = s.size(), left = 0, rihgt = n;
        vector<int> ret;

        for (int i = 0; i <= n; i++)
        {
            if (s[i] == 'I')
                ret.push_back(left++);
            else
                ret.push_back(rihgt--);
        }

        return ret;
    }

    // 3
    int minCut(string s)
    {
        int n = s.size();
        vector<vector<bool>> isPal(n, vector<bool>(n));
        for (int i = n - 1; i >= 0; i--)
            for (int j = i; j < n; j++)
                if (s[i] == s[j])
                    isPal[i][j] = j - i + 1 > 3 ? isPal[i + 1][j - 1] : true;

        vector<int> dp(n, INT_MAX);
        for (int i = 0; i < n; i++)
        {
            if (isPal[0][i])
                dp[i] = 0;
            else
            {
                for (int j = 1; j <= i; j++)
                {
                    if (isPal[j][i])
                        dp[i] = min(dp[i], dp[j - 1] + 1);
                }
            }
        }

        return dp[n - 1];
    }

    // 4
    bool canPartition(vector<int> &nums)
    {
        int n = nums.size(), sum = 0;
        for (auto num : nums)
            sum += num;

        if (sum % 2)
            return false;

        int aim = sum / 2;
        vector<vector<bool>> dp(n + 1, vector<bool>(aim + 1));
        for (int i = 0; i <= n; i++)
            dp[i][0] = true;

        for (int i = 1; i <= n; i++)
            for (int j = 0; j <= aim; j++)
            {
                dp[i][j] = dp[i - 1][j];
                if (j >= nums[i - 1])
                    dp[i][j] = dp[i][j] || dp[i - 1][j - nums[i - 1]];
            }

        return dp[n][aim];
    }

    // 5
    int combinationSum4(vector<int> &nums, int target)
    {
        vector<double> dp(target + 1);
        dp[0] = 1;

        for (int i = 1; i <= target; i++)
            for (auto n : nums)
                if (i >= n)
                    dp[i] += dp[i - n];

        return dp[target];
    }

    // 6
    class MyQueue
    {
    private:
        stack<int> in, out;

        void in2out()
        {
            while (in.size())
            {
                out.push(in.top());
                in.pop();
            }
        }

    public:
        MyQueue() {}

        void push(int x) { in.push(x); }

        int pop()
        {
            if (out.empty())
                in2out();

            int r = out.top();
            out.pop();
            return r;
        }

        int peek()
        {
            if (out.empty())
                in2out();
            int r = out.top();
            return r;
        }

        bool empty() { return in.empty() && out.empty(); }
    };
};
