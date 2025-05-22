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
    string removeDuplicates(string s)
    {
        string ret;
        for (auto ch : s)
        {
            if (ret.size() && ret.back() == ch)
                ret.pop_back();
            else
                ret += ch;
        }

        return ret;
    }

    int tmp[50010];
    int reversePairs(vector<int> &record)
    {
        return mergeSort(record, 0, record.size() - 1);
    }

    int mergeSort(vector<int> &nums, int left, int right)
    {
        if (left >= right)
            return 0;

        int mid = left + (right - left) / 2;
        int ret = 0;
        ret += mergeSort(nums, left, mid);
        ret += mergeSort(nums, mid + 1, right);

        int i = 0, cur1 = left, cur2 = mid + 1;
        while (cur1 <= mid && cur2 <= right)
        {
            if (nums[cur1] <= nums[cur2])
                tmp[i++] = nums[cur2++];
            else
            {
                ret += right - cur2 + 1;
                tmp[i++] = nums[cur1++];
            }
        }

        while (cur1 <= mid)
            tmp[i++] = nums[cur1++];
        while (cur2 <= right)
            tmp[i++] = nums[cur2++];

        for (int j = left; j <= right; j++)
            nums[j] = tmp[j - left];

        return ret;
    }

    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        ListNode *head = new ListNode(0);
        ListNode *prev = head;

        int t = 0;
        ListNode *cur1 = l1, *cur2 = l2;

        while (t || cur1 || cur2)
        {
            if (cur1)
            {
                t += cur1->val;
                cur1 = cur1->next;
            }
            if (cur2)
            {
                t += cur2->val;
                cur2 = cur2->next;
            }

            prev->next = new ListNode(t % 10);
            prev = prev->next;
            t /= 10;
        }

        prev = head->next;
        delete head;
        return prev;
    }

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
        for (auto &list : lists)
            if (list)
                q.push(list);

        ListNode *head = new ListNode(0);
        ListNode *prev = head;

        while (q.size())
        {
            auto t = q.top();
            q.pop();
            prev->next = t;
            prev = prev->next;
            if (t->next)
                q.push(t->next);
        }

        prev = head->next;
        delete head;
        return prev;
    }
};