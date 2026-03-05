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

    // 2
    int calculateMinimumHP(vector<vector<int>> &dungeon)
    {
        int m = dungeon.size(), n = dungeon[0].size();

        vector<vector<int>> dp(m + 1, vector<int>(n + 1, INT_MAX));
        dp[m][n - 1] = dp[m - 1][n] = 1;

        for (int i = m - 1; i >= 0; i--)
            for (int j = n - 1; j >= 0; j--)
            {
                int min_required = min(dp[i + 1][j], dp[i][j + 1]);

                dp[i][j] = min_required - dungeon[i][j];

                dp[i][j] = max(1, dp[i][j]);
            }

        return dp[0][0];
    }

    // 3
    void reorderList(ListNode *head)
    {
        ListNode *slow = head, *fast = head;
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode *head2 = new ListNode(0);
        ListNode *cur = slow->next;
        slow->next = nullptr;

        while (cur)
        {
            ListNode *next = cur->next;
            cur->next = head2->next;
            head2->next = cur;
            cur = next;
        }

        ListNode *ret = new ListNode(0);
        ListNode *cur1 = head, *cur2 = head2->next, *prev = ret;

        while (cur1 || cur2)
        {
            if (cur1)
            {
                prev->next = cur1;
                prev = prev->next;
                cur1 = cur1->next;
            }
            if (cur2)
            {
                prev->next = cur2;
                prev = prev->next;
                cur2 = cur2->next;
            }
        }

        prev = ret->next;
        delete cur1, cur2, cur, ret, head2;
    }

    // 4
    string minWindow(string s, string t)
    {
        int m = t.size();
        int hash1[128] = {0};
        int hash2[128] = {0};
        for (char ch : t)
            hash1[ch]++;

        int begin = -1, minlen = INT_MAX;
        for (int left = 0, right = 0, count = 0; right < s.size(); right++)
        {
            char in = s[right];
            if (++hash2[in] <= hash1[in])
                count++;
            while (count == m)
            {
                if (right - left + 1 < minlen)
                {
                    begin = left;
                    minlen = right - left + 1;
                }
                char out = s[left++];
                if (hash2[out]-- <= hash1[out])
                    count--;
            }
        }

        return begin == -1 ? "" : s.substr(begin, minlen);
    }

    // 5
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
};