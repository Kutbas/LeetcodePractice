#include <bits/stdc++.h>
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
    string longestPalindrome(string s)
    {
        if (s.size() < 2)
            return s;

        int n = s.size(), begin = 0, maxlen = 1;
        vector<vector<int>> dp(n, vector<int>(n));
        for (int i = 0; i < n; i++)
            dp[i][i] = true;

        for (int L = 2; L <= n; L++)
            for (int i = 0; i < n; i++)
            {
                int j = i + L - 1;
                if (j >= n)
                    break;

                if (s[i] != s[j])
                    dp[i][j] = false;
                else
                {
                    if (L == 2)
                        dp[i][j] = true;
                    else
                        dp[i][j] = dp[i + 1][j - 1];
                }

                if (dp[i][j] && j - i + 1 > maxlen)
                {
                    maxlen = j - i + 1;
                    begin = i;
                }
            }

        return s.substr(begin, maxlen);
    }

    void reorderList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr || head->next->next == nullptr)
            return;

        ListNode *slow = head, *fast = head;
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode *head2 = new ListNode(0);
        ListNode *prev = head2;
        // head2->next = slow->next;
        ListNode *cur = slow->next;
        slow->next = nullptr;

        // ListNode *cur = head2->next;
        while (cur)
        {
            ListNode *next = cur->next;
            cur->next = prev->next;
            prev->next = cur;
            // head2->next = next;
            // next->next = cur;
            cur = next;
        }

        ListNode *ret = new ListNode(0);
        prev = ret;
        ListNode *cur1 = head, *cur2 = head2->next;

        while (cur1)
        {
            prev->next = cur1;

            prev = prev->next;
            cur1 = cur1->next;
            if (cur2)
            {
                prev->next = cur2;
                prev = prev->next;
                cur2 = cur2->next;
            }
        }

        delete head2, ret;
        return;
    }
};