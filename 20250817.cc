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
    int monotoneIncreasingDigits(int n)
    {
        string s = to_string(n);

        int i = 0, m = s.size();
        while (i + 1 < m && s[i] <= s[i + 1])
            i++;

        // n 本身就是递增的
        if (i + 1 == m)
            return n;

        // 回退
        while (i - 1 >= 0 && s[i] == s[i - 1])
            i--;

        s[i]--;
        for (int j = i + 1; j < m; j++)
            s[j] = '9';

        return stoi(s);
    }

    // 1
    bool vis[7];
    vector<vector<int>> ret;
    vector<int> path;
    vector<vector<int>> permute(vector<int> &nums)
    {
        dfs(nums);
        return ret;
    }

    void dfs(vector<int> &nums)
    {
        if (path.size() == nums.size())
        {
            ret.push_back(path);
            return;
        }

        for (int i = 0; i < nums.size(); i++)
        {
            if (!vis[i])
            {
                vis[i] = true;
                path.push_back(nums[i]);
                dfs(nums);
                path.pop_back();
                vis[i] = false;
            }
        }
    }

    // 2
    bool validateStackSequences(vector<int> &pushed, vector<int> &popped)
    {
        vector<int> st;
        int i = 0, n = popped.size();

        for (auto x : pushed)
        {
            if (st.size() && st.back() == popped[i])
            {
                st.pop_back();
                i++;
            }
            else
                st.push_back(x);
        }

        return i == n;
    }

    // 3
    int jump(vector<int> &nums)
    {
        int left = 0, right = 0, maxPos = 0, ret = 0, n = nums.size();

        while (left <= right)
        {
            if (maxPos >= n - 1)
                return ret;

            for (int i = left; i <= right; i++)
                maxPos = max(maxPos, nums[i] + i);

            left = right + 1;
            right = maxPos;
            ret++;
        }

        return -1;
    }

    // 4
    ListNode *swapPairs(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *tmp = swapPairs(head->next->next);
        ListNode *ret = head->next;
        ret->next = head;
        head->next = tmp;

        return ret;
    }

    // 5
    ListNode *swapPairs(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *ret = new ListNode(0);
        ListNode *prev = ret;
        ListNode *cur = head, *next = cur->next, *nnext = next->next;

        while (cur && cur->next)
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

    // 6
    int tmp[50010];
    int reversePairs(vector<int> &nums)
    {
        return mergeSort(nums, 0, nums.size() - 1);
    }

    int mergeSort(vector<int> &nums, int left, int right)
    {
        if (left >= right)
            return 0;

        int mid = left + (right - left) / 2, ret = 0;
        ret += mergeSort(nums, left, mid);
        ret += mergeSort(nums, mid + 1, right);

        int i = 0, cur1 = left, cur2 = mid + 1;
        while (cur1 <= mid)
        {
            if (cur2 <= right && nums[cur1] <= 2.0 * nums[cur2])
                cur2++;
            else
            {
                ret += right - cur2 + 1;
                cur1++;
            }
        }

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
};