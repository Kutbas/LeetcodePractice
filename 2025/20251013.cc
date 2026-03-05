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
    int minimumDeleteSum(string s1, string s2)
    {
        int m = s1.size(), n = s2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
                if (s1[i - 1] == s2[j - 1])
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + s1[i - 1]);
            }

        int sum = 0;
        for (auto s : s1)
            sum += s;
        for (auto s : s2)
            sum += s;

        return sum - dp[m][n] * 2;
    }

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

    // 1
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost)
    {
        int n = gas.size();
        for (int i = 0; i < n; i++)
        {
            int step = 0, rest = 0;
            for (; step < n; step++)
            {
                int index = (i + step) % n;
                rest = rest + gas[index] - cost[index];
                if (rest < 0)
                    break;
            }

            if (rest >= 0)
                return i;
            i = i + step;
        }

        return -1;
    }

    // 2
    string largestNumber(vector<int> &nums)
    {
        vector<string> strs;
        for (auto n : nums)
            strs.push_back(to_string(n));

        sort(strs.begin(), strs.end(), [&](const string &s1, const string &s2)
             { return s1 + s2 > s2 + s1; });

        string ret;
        for (auto s : strs)
            ret += s;

        return ret[0] == '0' ? "0" : ret;
    }

    // 3
    int findContentChildren(vector<int> &g, vector<int> &s)
    {
        int m = g.size(), n = s.size();
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());

        int ret = 0;
        for (int i = 0, j = 0; i < m && j < n; i++, j++)
        {
            while (j < n && s[j] < g[i])
                j++;
            if (j < n)
                ret++;
        }

        return ret;
    }

    // 4
    int wiggleMaxLength(vector<int> &nums)
    {
        int n = nums.size(), ret = 0, left = 0;
        if (n < 2)
            return n;

        for (int i = 0; i + 1 < n; i++)
        {
            int right = nums[i + 1] * nums[i];
            if (right == 0)
                continue;
            if (left * right <= 0)
                ret++;
            left = right;
        }

        return ret + 1;
    }

    // 5
    vector<int> advantageCount(vector<int> &nums1, vector<int> &nums2)
    {
        int n = nums1.size();
        sort(nums1.begin(), nums1.end());

        vector<int> index2(n);
        for (int i = 0; i < n; i++)
            index2[i] = i;

        sort(index2.begin(), index2.end(), [&](int i, int j)
             { return nums2[i] < nums2[j]; });

        vector<int> ret(n);
        int left = 0, right = n - 1;
        for (auto x : nums1)
        {
            if (x > nums2[index2[left]])
                ret[index2[left++]] = x;
            else
                ret[index2[right--]] = x;
        }

        return ret;
    }

    // 6
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

    // 7
    ListNode *swapPairs(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *newhead = new ListNode(0);
        ListNode *prev = newhead;
        ListNode *cur = head, *next = cur->next, *nnext = next->next;

        while (cur && next)
        {
            prev->next = next;
            prev = prev->next;

            next->next = cur;
            cur->next == nnext;

            if (cur)
                next = cur->next;
            if (next)
                nnext = next->next;
        }

        prev = newhead->next;
        delete newhead;
        return prev;
    }
};