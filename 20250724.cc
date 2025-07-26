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

        int ret = 0, mid = left + (right - left) / 2;
        ret += mergeSort(nums, left, mid);
        ret += mergeSort(nums, mid + 1, right);

        int cur1 = left, cur2 = mid + 1;
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

    bool check[16];
    int ret = 0;
    int countArrangement(int n)
    {
        dfs(1, n);
        return ret;
    }

    void dfs(int pos, int n)
    {
        if (pos == n + 1)
        {
            ret++;
            return;
        }

        for (int i = 1; i <= n; i++)
        {
            if (!check[i] && i % pos == 0 && pos % i == 0)
            {
                check[i] = true;
                dfs(pos + 1, n);
                check[i] = false;
            }
        }
    }

    vector<int> ret1;
    vector<int> tmp1;
    vector<int> index;
    vector<int> tmpIndex;
    vector<int> countSmaller(vector<int> &nums)
    {
        int n = nums.size();
        ret1.resize(n);
        tmp1.resize(n);
        index.resize(n);
        tmpIndex.resize(n);

        for (int i = 0; i < n; i++)
            index[i] = i;

        mergesort(nums, 0, nums.size() - 1);
        return ret1;
    }

    void mergesort(vector<int> &nums, int left, int right)
    {
        if (left >= right)
            return;

        int mid = left + (right - left) / 2;
        mergesort(nums, left, mid);
        mergesort(nums, mid + 1, right);

        int i = 0, cur1 = left, cur2 = mid + 1;
        while (cur1 <= mid && cur2 <= right)
        {
            if (nums[cur1] <= nums[cur2])
            {
                tmp1[i] = nums[cur2];
                tmpIndex[i++] = index[cur2++];
            }
            else
            {
                ret1[index[cur1]] += right - cur2 + 1;
                tmp1[i] = nums[cur1];
                tmpIndex[i++] = index[cur1++];
            }
        }
        while (cur1 <= mid)
        {
            tmp1[i] = nums[cur1];
            tmpIndex[i++] = index[cur1++];
        }
        while (cur2 <= right)
        {
            tmp1[i] = nums[cur2];
            tmpIndex[i++] = index[cur2++];
        }

        for (int j = left; j <= right; j++)
        {
            nums[j] = tmp1[j - left];
            index[j] = tmpIndex[j - left];
        }
    }

    ListNode *mergeTwoLists(ListNode *list1, ListNode *list2)
    {
        if (list1 == nullptr)
            return list2;
        if (list2 == nullptr)
            return list1;

        if (list1->val < list2->val)
        {
            list1->next = mergeTwoLists(list1->next, list2);
            return list1;
        }
        else
        {
            list2->next = mergeTwoLists(list1, list2->next);
            return list2;
        }
    }

    bool row[9][10];
    bool col[9][10];
    bool grid[3][3][10];
    bool isValidSudoku(vector<vector<char>> &board)
    {
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
            {
                if (board[i][j] != '.')
                {
                    int num = board[i][j] - '0';
                    if (row[i][num] || col[j][num] || grid[i / 3][j / 3][num])
                        return false;

                    row[i][num] = col[j][num] = grid[i / 3][j / 3][num] = true;
                }
            }
        return true;
    }

    vector<int> productExceptSelf(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> f(n), g(n), ret(n);
        f[0] = g[n - 1] = 1;
        for (int i = 1; i < n; i++)
            f[i] = f[i - 1] * nums[i - 1];
        for (int i = n - 2; i >= 0; i--)
            g[i] = g[i + 1] * nums[i + 1];
        for (int i = 0; i < n; i++)
            ret[i] = f[i] * g[i];

        return ret;
    }
};