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
    vector<string> sortPeople(vector<string> &names, vector<int> &heights)
    {
        int n = names.size();
        vector<int> index(n);
        for (int i = 0; i < n; i++)
            index[i] = i;

        sort(index.begin(), index.end(), [&](const int i, const int j)
             { return heights[i] > heights[j]; });

        vector<string> ret;
        for (auto i : index)
            ret.push_back(names[i]);

        return ret;
    }

    // 2
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

    // 3
    ListNode *reverseList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *newhead = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;

        return newhead;
    }

    // 4
    int halveArray(vector<int> &nums)
    {
        double sum = 0, ret = 0;
        priority_queue<double> q;

        for (auto n : nums)
        {
            sum += n;
            q.push(n);
        }

        double aim = sum / 2.0;
        while (sum > aim)
        {
            auto t = q.top();
            q.pop();
            q.push(t / 2.0);
            sum -= t / 2.0;
            ret++;
        }

        return ret;
    }

    // 5
    bool increasingTriplet(vector<int> &nums)
    {
        int a = INT_MAX, b = nums[0], n = nums.size();
        for (int i = 1; i < n; i++)
        {
            if (nums[i] > a)
                return true;
            else if (nums[i] > b)
                a = nums[i];
            else
                b = min(b, nums[i]);
        }

        return false;
    }
};