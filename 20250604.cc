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
    void reorderList(ListNode *head)
    {
        ListNode *slow = head, *fast = head;

        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode *newhead = new ListNode(0);
        ListNode *prev = newhead;
        ListNode *cur = slow->next;
        slow->next = nullptr;

        while (cur)
        {
            ListNode *next = cur->next;

            cur->next = prev->next;
            prev->next = cur;

            cur = next;
        }

        ListNode *ret = new ListNode(0);
        prev = ret;
        ListNode *cur1 = head, *cur2 = newhead->next;

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

        head = newhead->next;
        delete newhead, cur1, cur2, prev;
    }

    string decodeString(string s)
    {
        stack<int> nums;
        stack<string> st;
        string ret;
        int k = 0;

        for (char ch : s)
        {
            if (isdigit(ch))
                k = k * 10 + ch - 'a';
            else if (ch == '[')
            {
                nums.push(k);
                k = 0;
                st.push(ret);
                ret = "";
            }
            else if (ch == ']')
            {
                int n = nums.top();
                nums.pop();
                string tmp = st.top();
                st.pop();
                while (n--)
                    tmp += ret;
                ret = tmp;
            }
            else
                ret += ch;
        }

        return ret;
    }

    int lastStoneWeight(vector<int> &stones)
    {
        priority_queue<int> q;
        for (auto n : stones)
            q.push(n);

        while (q.size() > 1)
        {
            int x = q.top();
            q.pop();
            int y = q.top();
            q.pop();
            q.push(x - y);
        }
        return q.top();
    }

    string decodeString(string s)
    {
        stack<int> nums;
        stack<string> st;
        string ret;
        int k = 0;

        for (char ch : s)
        {
            if (isdigit(ch))
                k = k * 10 + ch - '0';
            else if (ch == '[')
            {
                nums.push(k);
                k = 0;
                st.push(ret);
                ret = "";
            }
            else if (ch == ']')
            {
                int n = nums.top();
                nums.pop();
                string tmp = st.top();
                st.pop();
                while (n--)
                    tmp += ret;
                ret = tmp;
            }
            else
                ret += ch;
        }

        return ret;
    }
};

class MedianFinder
{
public:
    priority_queue<int> left;
    priority_queue<int, vector<int>, greater<int>> right;

    MedianFinder() {}

    void addNum(int num)
    {
        if (left.size() == right.size())
        {
            if (left.empty() || num < left.top())
                left.push(num);
            else
            {
                right.push(num);
                left.push(right.top());
                right.pop();
            }
        }
        else
        {
            if (num >= left.top())
                right.push(num);
            else
            {
                left.push(num);
                right.push(left.top());
                left.pop();
            }
        }
    }

    double findMedian()
    {
        return left.size() == right.size() ? (left.top() + right.top()) / 2.0
                                           : left.top();
    }
};