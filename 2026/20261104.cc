#include <mutex>
#include <vector>
#include <algorithm>
#include <climits>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <iostream>
#include <sstream>
#include <regex>
#include <map>
#include <set>
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
    int findMaxLength(vector<int> &nums)
    {
        int n = nums.size();
        unordered_map<int, int> hash;
        hash[0] = -1;

        int sum = 0, ret = 0;
        for (int i = 0; i < n; i++)
        {
            sum += nums[i] == 0 ? -1 : 1;

            if (hash.count(sum))
                ret = max(ret, i - hash[sum]);
            else
                hash[sum] = i;
        }

        return ret;
    }

    // 2
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

    // 3
    int maxSubArray(vector<int> &nums)
    {
        int n = nums.size(), ret = INT_MIN;
        vector<int> f(n + 1);
        for (int i = 1; i <= n; i++)
        {
            f[i] = max(f[i - 1] + nums[i - 1], nums[i - 1]);
            ret = max(ret, f[i]);
        }

        return ret;
    }

    // 4
    int FindGreatestSumOfSubArray(vector<int> &array)
    {
        int n = array.size(), ret = INT_MIN;
        vector<int> f(n + 1);

        for (int i = 1; i <= n; i++)
        {
            f[i] = max(f[i - 1] + array[i - 1], array[i - 1]);
            ret = max(ret, f[i]);
        }

        return ret;
    }

    // 5
    bool GetPath(TreeNode *root, TreeNode *x, stack<TreeNode *> &path)
    {
        if (root == nullptr)
            return false;

        path.push(root);

        if (root == x)
            return true;

        if (GetPath(root->left, x, path))
            return true;
        if (GetPath(root->right, x, path))
            return true;

        path.pop();

        return false;
    }

    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        stack<TreeNode *> qPath, pPath;

        GetPath(root, p, pPath);
        GetPath(root, q, qPath);

        while (qPath.size() != pPath.size())
        {
            if (qPath.size() > pPath.size())
                qPath.pop();
            else
                pPath.pop();
        }

        while (qPath.top() != pPath.top())
            qPath.pop(), pPath.pop();

        return qPath.top();
    }
};