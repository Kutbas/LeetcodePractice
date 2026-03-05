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

class Solution
{
public:
    struct cmp
    {
        bool operator()(const ListNode *l1, const ListNode *l2)
        {
            return l1->val > l2->val;
        }
    };

    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        priority_queue<ListNode *, vector<ListNode *>, cmp> heap;

        for (auto l : lists)
            if (l)
                heap.push(l);

        // 合并K个有序链表
        ListNode *ret = new ListNode(0);
        ListNode *prev = ret;

        while (!heap.empty())
        {
            ListNode *t = heap.top();
            heap.pop();

            prev->next = t;
            prev = t;
            if (t->next)
                heap.push(t->next);
        }

        prev = ret->next;
        delete ret;
        return prev;
    }

    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        return merge(lists, 0, lists.size() - 1);
    }

    ListNode *merge(vector<ListNode *> &lists, int left, int right)
    {
        if (left > right)
            return nullptr;
        if (left == right)
            return lists[left];

        int mid = left + (right - left) / 2;

        ListNode *l1 = merge(lists, left, mid);
        ListNode *l2 = merge(lists, mid + 1, right);

        // 合并两个有序链表
        return mergeTowLists(l1, l2);
    }

    ListNode *mergeTowLists(ListNode *l1, ListNode *l2)
    {
        if (l1 == nullptr)
            return l2;
        if (l2 == nullptr)
            return l1;

        ListNode head;
        ListNode *cur1 = l1, *cur2 = l2, *prev = &head;

        head.next = nullptr;

        while (cur1 && cur2)
        {
            if (cur1->val <= cur2->val)
            {
                prev = prev->next = cur1;
                cur1 = cur1->next;
            }
            else
            {
                prev = prev->next = cur2;
                cur2 = cur2->next;
            }
        }

        if (cur1)
            prev->next = cur1;
        if (cur2)
            prev->next = cur2;

        return head.next;
    }

    ListNode *reverseKGroup(ListNode *head, int k)
    {
        // 先求出需要逆序多少组
        int n = 0;
        ListNode *cur = head;

        while (cur)
        {
            cur = cur->next;
            n++;
        }

        n /= k;

        ListNode *newhead = new ListNode(0);
        ListNode *prev = newhead;
        cur = head;

        for (int i = 0; i < n; i++)
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
        // 把不需要翻转的接上
        prev->next = cur;
        cur = newhead->next;
        delete newhead;
        return cur;
    }

    int peakIndexInMountainArray(vector<int> &nums)
    {
        int left = 0, right = nums.size() - 1;

        while (left < right)
        {
            int mid = left + (right - left + 1) / 2;
            if (nums[mid] > nums[mid - 1])
                left = mid;
            else
                right = mid - 1;
        }

        return left;
    }

    int singleNumber(vector<int> &nums)
    {
        int ret = 0;
        for (auto n : nums)
            ret ^= n;
        return ret;
    }

    void moveZeroes(vector<int> &nums)
    {
        for (int i = 0, cur = -1; i < nums.size(); i++)
            if (nums[i])
                swap(nums[i], nums[++cur]);
    }

    int searchInsert(vector<int> &nums, int target)
    {
        int left = 0, right = nums.size() - 1;

        while (left < right)
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] < target)
                left = mid + 1;
            else
                right = mid;
        }

        return nums[left] == target ? left : left + 1;
    }

    string convert(string s, int numRows)
    {
        if (s.size() == 1)
            return s;
    }

    int missingNumber(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());

        int left = 0, right = nums.size() - 1;

        while (left < right)
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] == mid)
                left = mid + 1;
            else
                right = mid;
        }

        return nums[left] == left ? left + 1 : left;
    }

    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        return merge(lists, 0, lists.size() - 1);
    }

    ListNode *merge(vector<ListNode *> &lists, int left, int right)
    {
        if (left > right)
            return nullptr;
        if (left == right)
            return lists[left];

        int mid = left + (right - left) / 2;
        ListNode *l1 = merge(lists, left, mid);
        ListNode *l2 = merge(lists, mid + 1, right);

        return mergeTowLists(l1, l2);
    }

    ListNode *mergeTowLists(ListNode *l1, ListNode *l2)
    {
        if (l1 == nullptr)
            return l2;
        if (l2 == nullptr)
            return l1;

        ListNode head;
        ListNode *cur1 = l1, *cur2 = l2, *prev = &head;

        while (cur1 && cur2)
        {
            if (cur1->val < cur2->val)
            {
                prev = prev->next = cur1;
                cur1 = cur1->next;
            }
            else
            {
                prev = prev->next = cur2;
                cur2 = cur2->next;
            }
        }

        if (cur1)
            prev = prev->next = cur1;
        if (cur2)
            prev = prev->next = cur2;

        return head.next;
    }
};