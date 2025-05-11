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

                for (auto node : t->children)
                    if (node != nullptr)
                        q.push(node);
            }
            ret.push_back(tmp);
        }

        return ret;
    }

    int tmp[50010];
    vector<int> sortArray(vector<int> &nums)
    {
        mergeSort(nums, 0, nums.size() - 1);
        return nums;
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
            tmp[i++] = nums[cur1] <= nums[cur2] ? nums[cur1++] : nums[cur2++];

        while (cur1 <= mid)
            tmp[i++] = nums[cur1++];

        while (cur2 <= right)
            tmp[i++] = nums[cur2++];

        for (int j = left; j <= right; j++)
            nums[j] = tmp[j - left];
    }

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

                for (auto node : t->children)
                    if (node)
                        q.push(node);
            }
            ret.push_back(tmp);
        }

        return ret;
    }

    int lastStoneWeight(vector<int> &stones)
    {
        priority_queue<int> q;
        for (auto n : stones)
            q.push(n);

        while (q.size() > 1)
        {
            int x = q.top();
            q.pop();
            int y = q.top();
            q.pop();

            q.push(x - y);
        }

        return q.top();
    }

    bool containsDuplicate(vector<int> &nums)
    {
        unordered_map<int, int> hash;
        for (auto n : nums)
            if (++hash[n] >= 2)
                return true;
        return false;
    }

    vector<int> largestValues(TreeNode *root)
    {
        vector<int> ret;
        if (!root)
            return ret;

        queue<TreeNode *> q;
        q.push(root);

        while (q.size())
        {
            int sz = q.size();
            int tmp = INT_MIN;
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

    int widthOfBinaryTree(TreeNode *root)
    {
        vector<pair<TreeNode *, unsigned int>> q;
        q.push_back({root, 1});

        unsigned int ret = 0;

        while (q.size())
        {
            auto &[x1, y1] = q[0];
            auto &[x2, y2] = q.back();
            ret = max(ret, y2 - y1 + 1);

            vector<pair<TreeNode *, unsigned int>> tmp;
            for (auto &[x, y] : q)
            {
                if (x->left)
                    tmp.push_back({x->left, 2 * y});
                if (x->right)
                    tmp.push_back({x->right, 2 * y + 1});
            }
            q = tmp;
        }

        return ret;
    }
};