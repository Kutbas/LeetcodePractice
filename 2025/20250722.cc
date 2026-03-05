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
    vector<int> ret;
    vector<int> tmp;
    vector<int> index;
    vector<int> tmpIndex;
    vector<int> countSmaller(vector<int> &nums)
    {
        int n = nums.size();
        ret.resize(n);
        tmp.resize(n);
        index.resize(n);
        tmpIndex.resize(n);

        for (int i = 0; i < n; i++)
            index[i] = i;

        mergeSort(nums, 0, nums.size() - 1);
        return ret;
    }

    void mergeSort(vector<int> &nums, int left, int right)
    {
        if (left >= right)
            return;

        int mid = left + (right - left) / 2;
        mergeSort(nums, left, mid);
        mergeSort(nums, mid + 1, right);

        int i = 0, cur1 = left, cur2 = mid + 1;
        while (cur1 <= mid && cur2 <= right)
        {
            if (nums[cur1] <= nums[cur2])
            {
                tmp[i] = nums[cur2];
                tmpIndex[i++] = index[cur2++];
            }
            else
            {
                ret[index[cur1]] += right - cur2 + 1;
                tmp[i] = nums[cur1];
                tmpIndex[i++] = index[cur1++];
            }
        }
        while (cur1 <= mid)
        {
            tmp[i] = nums[cur1];
            tmpIndex[i++] = index[cur1++];
        }
        while (cur2 <= right)
        {
            tmp[i] = nums[cur2];
            tmpIndex[i++] = index[cur2++];
        }

        for (int j = left; j <= right; j++)
        {
            nums[j] = tmp[j - left];
            index[j] = tmpIndex[j - left];
        }
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

        ListNode *ret = new ListNode(0);
        ListNode *prev = ret;

        while (q.size())
        {
            auto t = q.top();
            q.pop();

            prev->next = t;
            prev = prev->next;

            if (t->next)
                q.push(t->next);
        }

        prev = ret->next;
        delete ret;
        return prev;
    }

    int tmp[50010];
    int reversePairs(vector<int> &nums)
    {
        return mergesort(nums, 0, nums.size() - 1);
    }

    int mergesort(vector<int> &nums, int left, int right)
    {
        if (left >= right)
            return 0;

        int ret = 0, mid = left + (right - left) / 2;
        ret += mergesort(nums, left, mid);
        ret += mergesort(nums, mid + 1, right);

        int cur1 = left, cur2 = mid + 1;
        while (cur1 <= mid)
        {
            if (nums[cur1] <= 2 * nums[cur2])
                cur1++;
            else
            {
                ret += right - cur2 + 1;
                cur2++;
            }
        }

        int i = 0;
        cur1 = left, cur2 = mid + 1;
        while (cur1 <= mid && cur2 <= right)
            tmp[i++] = nums[cur1] <= nums[cur2] ? nums[cur2++] : nums[cur1++];
        while (cur1 <= mid)
            tmp[i++] = nums[cur1++];
        while (cur2 <= right)
            tmp[i++] = nums[cur2++];

        for (int j = left; j <= right; j++)
            nums[j] = tmp[j - left];

        return ret;
    }

    void moveZeroes(vector<int> &nums)
    {
        int dest = -1, cur = 0, n = nums.size();
        while (cur < n)
        {
            if (nums[cur])
                swap(nums[++dest], nums[cur]);
            cur++;
        }
    }

    string multiply(string num1, string num2)
    {
        int m = num1.size(), n = num2.size();
        vector<int> tmp(m + n - 1);
        string ret;

        for (int i = m - 1; i >= 0; i--)
            for (int j = n - 1; j >= 0; j--)
                tmp[i + j] += (num1[i] - '0') * (num2[j] - '0');

        int cur = m + n - 2, t = 0;
        while (t || cur >= 0)
        {
            t += tmp[cur];
            ret += (t % 10) + '0';
            t /= 10;
        }

        reverse(ret.begin(), ret.end());
        return ret;
    }
};