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
    int tmp[50010];
    int reversePairs(vector<int> &nums)
    {
        return mergeSort(nums, 0, nums.size() - 1);
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
        while (cur1 <= mid)
        {
            while (cur2 <= right && nums[cur1] <= 2 * nums[cur2])
                cur2++;
            if (cur2 > right)
                break;

            ret += cur2 - mid + 1;
            cur1++;
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

    vector<int> largestValues(TreeNode *root)
    {
        vector<int> ret;
        if (root == nullptr)
            return ret;

        queue<TreeNode *> q;
        q.push(root);

        while (q.size())
        {
            int tmp = INT_MIN;
            int sz = q.size();
            while (sz--)
            {
                auto t = q.front();
                q.pop();
                tmp = max(tmp, t->val);

                if (t->left)
                    q.push(t->left);
                if (t->right)
                    q.push(t->right);
            }
            ret.push_back(tmp);
        }

        return ret;
    }

    int tmp[50010];
    vector<int> sortArray(vector<int> &nums)
    {
        merge_sort(nums, 0, nums.size() - 1);
        return nums;
    }

    void merge_sort(vector<int> &nums, int left, int right)
    {
        if (left >= right)
            return;

        int mid = left + (right - left) / 2;
        merge_sort(nums, left, mid);
        merge_sort(nums, mid + 1, right);

        int i = 0, cur1 = left, cur2 = mid + 1;
        while (cur1 <= mid && cur2 <= right)
            tmp[i++] = nums[cur1] <= nums[cur2] ? nums[cur1++] : nums[cur2++];
        while (cur1 <= mid)
            tmp[i++] = nums[cur1++];
        while (cur2 <= right)
            tmp[i++] = nums[cur2++];

        for (int j = left; j <= right; j++)
            nums[j] = tmp[j - left];
    }

    string longestCommonPrefix(vector<string> &strs)
    {
        for (int i = 0; i < strs[0].size(); i++)
        {
            for (int j = 1; j < strs.size(); j++)
                if (strs[0][i] != strs[j][i])
                    return strs[0].substr(0, i);
        }
        return strs[0];
    }

    bool validateStackSequences(vector<int> &pushed, vector<int> &popped)
    {
        stack<int> st;
        int i = 0, n = popped.size();

        for (auto num : pushed)
        {
            st.push(num);
            while (st.size() && st.top() == popped[i])
            {
                i++;
                st.pop();
            }
        }

        return i == n;
    }
};