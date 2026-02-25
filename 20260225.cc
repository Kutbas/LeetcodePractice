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
    int memo[101][101];
    int uniquePaths(int m, int n)
    {
        return dfs(m, n);
    }

    int dfs(int m, int n)
    {
        if (m == 0 || n == 0)
            return 0;

        if (m == 1 && n == 1)
            return 1;

        if (memo[m][n])
            return memo[m][n];

        int ret = dfs(m - 1, n) + dfs(m, n - 1);
        memo[m][n] = ret;

        return ret;
    }

    // 2
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

    // 3
    string removeDuplicates(string s)
    {
        string ret;
        for (char ch : s)
        {
            if (ret.size() && ret.back() == ch)
                ret.pop_back();
            else
                ret += ch;
        }
        return ret;
    }

    // 4
    int K;
    int prev = INT_MIN, ret = 0;
    int kthSmallest(TreeNode *root, int k)
    {
        K = k;
        dfs(root);
        return ret;
    }

    void dfs(TreeNode *root)
    {
        if (root->left)
            dfs(root->left);

        if (--K == 0)
        {
            ret = root->val;
            return;
        }

        if (root->right)
            dfs(root->right);
    }

    // 5
    void reorderList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
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
        while (cur1 || cur2)
        {
            if (cur1)
            {
                prev->next = cur1;
                cur1 = cur1->next;
                prev = prev->next;
            }
            if (cur2)
            {
                prev->next = cur2;
                cur2 = cur2->next;
                prev = prev->next;
            }
        }

        prev = ret->next;
        delete ret, slow, fast, cur1, cur2, head2;
    }

    // 6
    int wiggleMaxLength(vector<int> &nums)
    {
        int n = nums.size(), left = 0, right = 0, ret = 0;

        for (int i = 0; i < n - 1; i++)
        {
            right = nums[i + 1] - nums[i];
            if (right == 0)
                continue;
            else if (left * right <= 0)
                ret++;
            left = right;
        }

        return ret + 1;
    }

    // 7
    int singleNumber(vector<int> &nums)
    {
        int ret = 0;
        for (auto n : nums)
            ret ^= n;
        return ret;
    }

    // 8
    int searchInsert(vector<int> &nums, int target)
    {
        int n = nums.size(), left = 0, right = n - 1;

        while (left < right)
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] < target)
                left = mid + 1;
            else
                right = mid;
        }

        return nums[left] < target ? left + 1 : left;
    }
};