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
    ListNode *reverseKGroup(ListNode *head, int k)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *cur = head;
        int count = 0;
        while (cur)
        {
            cur = cur->next;
            count++;
        }

        count /= k;

        ListNode *ret = new ListNode(0);
        ListNode *prev = ret;
        cur = head;

        for (int i = 0; i < count; i++)
        {
            ListNode *tmp = cur;
            for (int j = 0; j < k; j++)
            {
                ListNode *next = cur->next;
                cur->next = prev->next;
                prev->next = cur;
                cur = next;
            }
            prev = tmp;
        }
        prev->next = cur;

        prev = ret->next;
        delete ret;
        return prev;
    }

    // 2
    int lastStoneWeight(vector<int> &stones)
    {
        priority_queue<int> q;
        for (auto s : stones)
            q.push(s);

        while (q.size() > 1)
        {
            auto x = q.top();
            q.pop();
            auto y = q.top();
            q.pop();
            q.push(x - y);
        }

        return q.top();
    }

    // 3
    string decodeString(string s)
    {
        stack<int> nums;
        int n = 0;
        stack<string> strs;
        string ret;

        for (char ch : s)
        {
            if (isdigit(ch))
                n = n * 10 + (ch - '0');
            else if (ch == '[')
            {
                nums.push(n);
                n = 0;
                strs.push(ret);
                ret = "";
            }
            else if (ch == ']')
            {
                int k = nums.top();
                nums.pop();
                string tmp = strs.top();
                strs.pop();
                while (k--)
                    tmp += ret;
                ret = tmp;
            }
            else
                ret += ch;
        }

        return ret;
    }

    // 4
    int maxUncrossedLines(vector<int> &nums1, vector<int> &nums2)
    {
        int m = nums1.size(), n = nums2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                if (nums1[i - 1] == nums2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }

        return dp[m][n];
    }

    // 5
    int numDistinct(string s, string t)
    {
        int m = t.size(), n = s.size();
        s = " " + s, t = " " + t;
        vector<vector<double>> dp(m + 1, vector<double>(n + 1));

        for (int i = 0; i <= n; i++)
            dp[0][i] = 1;

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                dp[i][j] = dp[i][j - 1];

                if (t[i] == s[j])
                    dp[i][j] += dp[i - 1][j - 1];
            }

        return dp[m][n];
    }

    // 6
    int myAtoi(string str)
    {
        int n = str.size(), ret = 0, cur = 0, sign = 1;

        while (str[cur] == ' ')
            if (++cur == n)
                return ret;

        if (str[cur] == '+' || str[cur] == '-')
        {
            if (str[cur] == '-')
                sign = -1;
            cur++;
        }

        for (int i = cur; i < n; i++)
        {
            if (!isdigit(str[i]))
                break;

            if (ret > (INT_MAX - (str[i] - '0')) / 10)
                return sign == 1 ? INT_MAX : INT_MIN;

            ret = ret * 10 + (str[i] - '0');
        }

        return ret * sign;
    }

    // 7
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
};