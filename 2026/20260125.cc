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

// Definition for a Node.
class Node
{
public:
    int val;
    vector<Node *> children;

    Node() {}

    Node(int _val)
    {
        val = _val;
    }

    Node(int _val, vector<Node *> _children)
    {
        val = _val;
        children = _children;
    }
};

class Solution
{
public:
    // 1
    vector<vector<int>> levelOrder(Node *root)
    {
        vector<vector<int>> ret;
        if (root == nullptr)
            return ret;

        queue<Node *> q;
        q.push(root);
        while (q.size())
        {
            int sz = q.size();
            vector<int> tmp;
            while (sz--)
            {
                auto t = q.front();
                q.pop();
                tmp.push_back(t->val);

                for (auto &node : t->children)
                    if (node)
                        q.push(node);
            }
            ret.push_back(tmp);
        }

        return ret;
    }

    // 2
    vector<int> searchRange(vector<int> &nums, int target)
    {
        int n = nums.size(), begin = -1, left = 0, right = n - 1;
        if (n == 0)
            return {-1, -1};

        while (left < right)
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] < target)
                left = mid + 1;
            else
                right = mid;
        }

        if (nums[left] != target)
            return {-1, -1};
        begin = left, left = 0, right = n - 1;

        while (left < right)
        {
            int mid = left + (right - left + 1) / 2;
            if (nums[mid] <= target)
                left = mid;
            else
                right = mid - 1;
        }

        return {begin, left};
    }

    // 3
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        int i = 0;
        return _buildTree(preorder, inorder, i, 0, inorder.size() - 1);
    }

    TreeNode *_buildTree(vector<int> &preorder, vector<int> &inorder,
                         int &previ, int inBegin, int inEnd)
    {
        if (inBegin > inEnd)
            return nullptr;

        TreeNode *ret = new TreeNode(preorder[previ]);

        int rooti = inBegin;
        while (rooti <= inEnd)
            if (inorder[rooti] != preorder[previ])
                rooti++;
            else
                break;

        previ++;
        ret->left = _buildTree(preorder, inorder, previ, inBegin, rooti - 1);
        ret->right = _buildTree(preorder, inorder, previ, rooti + 1, inEnd);

        return ret;
    }

    // 4
    int findLength(vector<int> &nums1, vector<int> &nums2)
    {
        int m = nums1.size(), n = nums2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));

        int ret = 0;
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                if (nums1[i - 1] == nums2[j - 1])
                {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);

                    ret = max(ret, dp[i][j]);
                }

        return ret;
    }
};