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
    bool isMatch(string s, string p)
    {
        int m = s.size(), n = p.size();
        s = " " + s;
        p = " " + p;
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1));
        for (int i = 2; i <= n; i += 2)
            if (p[i] == '*')
                dp[0][i] = true;
            else
                break;

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                if (p[j] == '*')
                {
                    bool from_s1 = dp[i][j - 2];
                    bool from_s2 = (p[j - 1] == '.' || p[j - 1] == s[i]) && dp[i - 1][j];
                    dp[i][j] = from_s1 || from_s2;
                }
                else
                    dp[i][j] = (p[j] == '.' || s[i] == p[j]) && dp[i - 1][j - 1];
            }

        return dp[m][n];
    }

    // 2
    int eraseOverlapIntervals(vector<vector<int>> &in)
    {
        sort(in.begin(), in.end());

        int n = in.size(), ret = 0, right = in[0][1];

        for (int i = 1; i < n; i++)
        {
            int a = in[i][0], b = in[i][1];
            if (a < right)
            { // 重叠
                ret++;
                right = min(right, b); // 保留结束早的
            }
            else           // 不重叠
                right = b; // 接受当前区间
        }
        return ret;
    }

    // 3
    ListNode *swapPairs(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *ret = new ListNode(0);
        ListNode *prev = ret;
        ListNode *cur = head, *next = cur->next, *nnext = next->next;
        while (cur && next)
        {
            prev->next = next;
            next->next = cur;
            cur->next = nnext;
            prev = cur;
            cur = nnext;

            if (cur)
                next = cur->next;
            if (next)
                nnext = next->next;
        }

        prev = ret->next;
        delete ret;
        return prev;
    }

    // 4
    int countSubstrings(string s)
    {
        int n = s.size(), ret = 0;
        vector<vector<bool>> dp(n, vector<bool>(n));
        for (int i = n - 1; i >= 0; i--)
            for (int j = i; j < n; j++)
            {
                if (s[i] == s[j])
                    dp[i][j] = j - i + 1 > 3 ? dp[i + 1][j - 1] : true;
                if (dp[i][j])
                    ret++;
            }

        return ret;
    }
};