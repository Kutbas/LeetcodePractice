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
    // 1
    vector<string> ret;
    vector<string> binaryTreePaths(TreeNode *root)
    {
        dfs2(root, "");
        return ret;
    }

    void dfs2(TreeNode *root, string path)
    {
        path += to_string(root->val);

        if (root->left == nullptr && root->right == nullptr)
        {
            ret.push_back(path);
            return;
        }

        path += "->";
        if (root->left)
            dfs2(root->left, path);
        if (root->right)
            dfs2(root->right, path);
    }

    // 2
    vector<vector<int>> ret1;
    vector<int> path1;
    vector<vector<int>> subsets(vector<int> &nums)
    {
        dfs(nums, 0);
        return ret1;
    }

    void dfs(vector<int> &nums, int pos)
    {
        ret1.push_back(path1);

        for (int i = pos; i < nums.size(); i++)
        {
            path1.push_back(nums[i]);
            dfs(nums, i + 1);
            path1.pop_back();
        }
    }

    // 3
    vector<vector<int>> ret2;
    vector<int> path2;
    bool vis2[9];
    vector<vector<int>> permuteUnique(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        dfs(nums, 0);
        return ret2;
    }

    void dfs(vector<int> &nums, int pos)
    {
        if (pos == nums.size())
        {
            ret2.push_back(path2);
            return;
        }

        for (int i = 0; i < nums.size(); i++)
        {
            if (vis2[i] || (i != 0 && nums[i] == nums[i - 1] && !vis2[i - 1]))
                continue;
            path2.push_back(nums[i]);
            vis2[i] = true;
            dfs(nums, pos + 1);
            vis2[i] = false;
            path2.pop_back();
        }
    }

    // 4
    TreeNode *pruneTree(TreeNode *root)
    {
        if (root == nullptr)
            return nullptr;

        if (root->left)
            root->left = pruneTree(root->left);
        if (root->right)
            root->right = pruneTree(root->right);

        if (root->left == nullptr && root->right == nullptr && root->val == 0)
            return nullptr;

        return root;
    }

    // 5
    int longestOnes(vector<int> &nums, int k)
    {
        int ret = 0;
        for (int left = 0, right = 0, count = 0; right < nums.size(); right++)
        {
            if (nums[right] == 0)
                count++;
            while (count > k)
                if (nums[left++] == 0)
                    count--;
            ret = max(ret, right - left + 1);
        }

        return ret;
    }

    // 6
    int count, ret3 = 0;
    int kthSmallest(TreeNode *root, int k)
    {
        count = k;
        dfs(root);
        return ret3;
    }

    void dfs(TreeNode *root)
    {
        if (root->left)
            dfs(root->left);

        if (--count == 0)
        {
            ret3 = root->val;
            return;
        }

        if (root->right)
            dfs(root->right);
    }
};