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
    int minSubArrayLen(int target, vector<int> &nums)
    {
        int ret = INT_MAX;

        for (int left = 0, right = 0, tmp = 0; right < nums.size(); right++)
        {
            tmp += nums[right];
            while (tmp >= target)
            {
                ret = min(ret, right - left + 1);
                tmp -= nums[left++];
            }
        }

        return ret == INT_MAX ? 0 : ret;
    }

    // 2
    vector<int> twoSum(vector<int> &nums, int target)
    {
        unordered_map<int, int> hash;
        for (int i = 0; i < nums.size(); i++)
        {
            int x = target - nums[i];
            if (hash.count(x))
                return {i, hash[x]};
            hash[nums[i]] = i;
        }
        return {-1, -1};
    }

    // 3
    vector<string> ret;
    vector<string> binaryTreePaths(TreeNode *root)
    {
        dfs(root, "");
        return ret;
    }

    void dfs(TreeNode *root, string path)
    {
        path += to_string(root->val);

        if (root->left == nullptr && root->right == nullptr)
        {
            ret.push_back(path);
            return;
        }

        path += "->";
        if (root->left)
            dfs(root->left, path);
        if (root->right)
            dfs(root->right, path);
    }

    // 4
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        ListNode *ret = new ListNode(0);
        ListNode *prev = ret, *cur1 = l1, *cur2 = l2;

        int t = 0;
        while (cur1 || cur2 || t)
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

        prev = ret->next;
        delete ret;
        return prev;
    }

    // 5
    int peakIndexInMountainArray(vector<int> &arr)
    {
        int left = 0, right = arr.size() - 1;
        while (left < right)
        {
            int mid = left + (right - left + 1) / 2;
            if (arr[mid] >= arr[mid - 1])
                left = mid;
            else
                right = mid - 1;
        }
        return left;
    }

    // 6
    int getSum(int a, int b)
    {
        while (b)
        {
            int xorsum = a ^ b;
            int carry = (a & b) << 1;
            a = xorsum;
            b = carry;
        }

        return a;
    }
};
