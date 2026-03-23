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
    int integerReplacement(int n)
    {
        int ret = 0;

        while (n != 1)
        {
            if (n % 2 == 0)
            {
                n /= 2;
                ret++;
            }
            else if (n == 3)
            {
                n = 1;
                ret += 2;
            }
            else if (n % 4 == 1)
            {
                n /= 2;
                ret += 2;
            }
            else
            {
                n = n / 2 + 1;
                ret += 2;
            }
        }

        return ret;
    }

    // 2
    int wiggleMaxLength(vector<int> &nums)
    {
        int ret = 0, left = 0, right = 0, n = nums.size();

        for (int i = 0; i < n - 1; i++)
        {
            right = nums[i + 1] - nums[i];
            if (right == 0)
                continue;
            if (left * right <= 0)
                ret++;
            left = right;
        }

        return ret + 1;
    }

    // 3
    vector<int> ret;
    vector<int> preorderTraversal(TreeNode *root)
    {
        dfs(root);
        return ret;
    }

    void dfs(TreeNode *root)
    {
        if (root == nullptr)
            return;

        ret.push_back(root->val);
        dfs(root->left);
        dfs(root->right);
    }
};