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

class Node
{
public:
    int val;
    vector<Node *> children;

    Node() {}

    Node(int _val)
    {
        val = _val;
    }

    Node(int _val, vector<Node *> _children)
    {
        val = _val;
        children = _children;
    }
};

class Solution
{
public:
    string decodeString(string s)
    {
        stack<int> nums;
        stack<string> st;
        st.push("");
        int i = 0, n = s.size();

        while (i < n)
        {
            if (s[i] >= '0' && s[i] <= '9')
            {
                int tmp = 0;
                while (s[i] >= '0' && s[i] <= '9')
                {
                    tmp = tmp * 10 + (s[i++] - '0');
                }
                nums.push(tmp);
            }
            else if (s[i] == '[')
            {
                i++;
                string tmp = "";
                while (s[i] >= 'a' && s[i] <= 'z')
                {
                    tmp += s[i++];
                }
                st.push(tmp);
            }
            else if (s[i] == ']')
            {
                string tmp = st.top();
                st.pop();
                int k = nums.top();
                nums.pop();

                while (k--)
                {
                    st.top() += tmp;
                }
                i++;
            }
            else
            {
                string tmp;
                while (i < n && s[i] >= 'a' && s[i] <= 'z')
                {
                    tmp += s[i++];
                }
                st.top() += tmp;
            }
        }
        return st.top();
    }

    bool validateStackSequences(vector<int> &pushed, vector<int> &popped)
    {
        stack<int> st;

        int i = 0, n = popped.size();
        for (auto x : pushed)
        {
            st.push(x);
            while (st.size() && st.top() == popped[i])
            {
                st.pop();
                i++;
            }
        }

        return i == n;
    }

    vector<vector<int>> levelOrder(Node *root)
    {
        vector<vector<int>> ret;
        queue<Node *> q;

        if (root == nullptr)
            return ret;

        q.push(root);
        while (q.size())
        {
            int sz = q.size(); // 本层元素的个数
            vector<int> tmp;   // 统计本层的节点
            for (int i = 0; i < sz; i++)
            {
                Node *t = q.front();
                q.pop();
                tmp.push_back(t->val);
                for (Node *child : t->children) // 让下一层节点入队
                {
                    if (child != nullptr)
                        q.push(child);
                }
            }
            ret.push_back(tmp);
        }

        return ret;
    }

    bool CheckPermutation(string s1, string s2)
    {
        if (s1.size() != s2.size())
            return false;

        int hash[128] = {0};
        for (auto ch : s1)
            hash[ch]++;

        for (auto ch : s2)
            if (--hash[ch] < 0)
                return false;

        return true;
    }

    string countAndSay(int n)
    {
        string ret = "1";
        for (int i = 1; i < n; i++)
        {
            string tmp;
            int len = ret.size();
            for (int left = 0, right = 0; right < len;)
            {
                while (right < len && ret[left] == ret[right])
                    right++;
                tmp += to_string(right - left) + ret[left];
                left = right;
            }
            ret = tmp;
        }

        return ret;
    }

    void reorderList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr || head->next->next)
            return;

        ListNode *slow = head, *fast = head;
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode *newhead = new ListNode(0);
        ListNode *cur = slow->next;
        slow->next = nullptr;

        while (cur)
        {
            ListNode *next = cur->next;
            cur->next = newhead->next;
            newhead->next = cur;
            cur = next;
        }

        ListNode *ret = new ListNode(0);
        ListNode *prev = ret;
        ListNode *cur1 = head, *cur2 = newhead;

        while (cur1)
        {

            prev->next = cur1;
            cur1 = cur1->next;
            prev = prev->next;

            if (cur2)
            {
                prev->next = cur2;
                cur2 = cur2->next;
                prev = prev->next;
            }
        }

        head = ret->next;
        delete newhead, ret;
        return;
    }

    string addBinary(string a, string b)
    {
        string ret;

        int cur1 = a.size() - 1, cur2 = b.size() - 1, t = 0;

        while (cur1 >= 0 || cur2 >= 0 || t)
        {
            if (cur1 >= 0)
                t += (a[cur1--] - '0');
            if (cur2 >= 0)
                t += (b[cur2--] - '0');

            ret += t % 2 + '0';
            t /= 2;
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }

    string longestPalindrome(string s)
    {
        // 边界情况
        int n = s.size();
        if (n < 2)
            return s;

        // 初始化
        vector<vector<int>> dp(n, vector<int>(n));
        int begin = 0, maxlen = 1;
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
                    begin = i;
                    maxlen = j - i + 1;
                }
            }

        return s.substr(begin, maxlen);
    }

    string addBinary(string a, string b)
    {
        int cur1 = a.size() - 1, cur2 = b.size() - 1, t = 0;
        string ret;

        while (cur1 >= 0 || cur2 >= 0 || t)
        {
            if (cur1 >= 0)
                t += (a[cur1--] - '0');
            if (cur2 >= 0)
                t += (b[cur2--] - '0');

            ret += t % 2 + '0';
            t /= 2;
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }

    string longestPalindrome(string s)
    {
        int n = s.size();
        if (n < 2)
            return s;

        vector<vector<int>> dp(n, vector<int>(n));
        int begin = 0, maxlen = 1;
        for (int i = 0; i < n; i++)
            dp[i][i] = true;

        for (int L = 2; L <= n; L++)
            for (int i = 0; i < n; i++)
            {
                int j = i + L - 1;
                if (j >= n)
                    break;

                if (s[i] != s[i])
                    dp[i][j] = false;
                else
                {
                    if (L == 2)
                        dp[i][j] = true;
                    else
                        dp[i][j] = dp[i + 1][j - 1];
                }

                if (j - i + 1 > maxlen)
                {
                    begin = i;
                    maxlen = j - i + 1;
                }
            }

        return s.substr(begin, maxlen);
    }

    vector<int> findSubstring(string s, vector<string> &words)
    {
        vector<int> ret;
        int m = words.size(), len = words[0].size();
        unordered_map<string, int> hash1;

        for (auto word : words)
            hash1[word]++;

        for (int i = 0; i < len; i++)
        {
            unordered_map<string, int> hash2;
            for (int left = i, right = i, count = 0; right + len <= s.size(); right += len)
            {
                string in = s.substr(right, len);
                ++hash2[in];
                if (hash1.count(in) && hash2[in] <= hash1[in])
                    count++;

                while (right - left + 1 > len * m)
                {
                    string out = s.substr(left, len);
                    if (hash1.count(out) && hash2[out] <= hash1[out])
                        count--;
                    --hash2[out];
                    left += len;
                }

                if (count == m)
                    ret.push_back(left);
            }
        }

        return ret;
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
        ListNode *prev = ret;
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

        delete ret, head2;
        return;
    }

    int findMin(vector<int> &nums)
    {
        int n = nums.size();
        int left = 0, right = n - 1;
        while (left < right)
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] > nums[n - 1])
                left = mid + 1;
            else
                right = mid;
        }
        return nums[left];
    }

    int waysToStep(int n)
    {
        if (n < 3)
            return n;
        int base = 1000000007, dp1 = 1, dp2 = 2, dp3 = 4, tmp2, tmp3;

        while (n-- != 3)
        {
            tmp2 = dp3, tmp3 = dp3;
            dp3 = ((dp3 + dp2) % base + dp1) % base;
            dp2 = tmp3;
            dp1 = tmp2;
        }
        return dp3;
    }

    string addBinary(string a, string b)
    {
        string ret;
        int cur1 = a.size() - 1, cur2 = b.size() - 1;
        int t = 0;

        while (cur1 >= 0 || cur2 >= 0 || t)
        {
            if (cur1 >= 0)
                t += (a[cur1--] - '0');
            if (cur2 >= 0)
                t += (b[cur2--] - '0');

            ret += t % 2 + '0';
            t /= 2;
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }

    ListNode *swapPairs(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *newhead = new ListNode(0);
        newhead->next = head;
        ListNode *prev = newhead;

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

        prev = newhead->next;
        delete newhead;
        return prev;
    }
};