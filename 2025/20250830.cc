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
    int uniquePathsWithObstacles(vector<vector<int>> &ob)
    {
        int m = ob.size(), n = ob[0].size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        dp[1][0] = 1;

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                if (ob[i - 1][j - 1] == 0)
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];

        return dp[m][n];
    }

    // 1
    vector<int> advantageCount(vector<int> &nums1, vector<int> &nums2)
    {
        int n = nums1.size();
        sort(nums1.begin(), nums1.end());

        vector<int> index2(n);
        for (int i = 0; i < n; i++)
            index2[i] = i;

        sort(index2.begin(), index2.end(), [&](int i, int j)
             { return nums2[i] < nums2[j]; });

        vector<int> ret(n);
        int left = 0, right = n - 1;

        for (auto x : nums1)
        {
            if (x > nums2[index2[left]])
                ret[index2[left++]] = x;
            else
                ret[index2[right--]] = x;
        }

        return ret;
    }

    // 2
    vector<vector<int>> levelOrder(Node *root)
    {
        vector<vector<int>> ret;
        if (root == nullptr)
            return ret;

        queue<Node *> q;
        q.push(root);

        while (q.size())
        {
            vector<int> tmp;
            int sz = q.size();
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

    // 3
    typedef pair<TreeNode *, unsigned int> PTI;
    int widthOfBinaryTree(TreeNode *root)
    {
        unsigned int ret = 1;
        vector<PTI> q;
        q.push_back({root, 1});

        while (q.size())
        {
            vector<PTI> tmp;

            auto [x1, y1] = q[0];
            auto [x2, y2] = q.back();
            ret = max(ret, y2 - y1 + 1);

            for (auto [x, y] : q)
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

    // 4
    vector<string> ret;
    string path;
    vector<string> letterCasePermutation(string s)
    {
        dfs(s, 0);
        return ret;
    }

    void dfs(string &s, int pos)
    {
        if (pos == s.size())
        {
            ret.push_back(path);
            return;
        }

        char ch = s[pos];
        path.push_back(ch);
        dfs(s, pos + 1);
        path.pop_back();

        if (!isdigit(ch))
        {
            char tmp = change(ch);
            path.push_back(tmp);
            dfs(s, pos + 1);
            path.pop_back();
        }
    }

    char change(char ch)
    {
        if (ch >= 'a' && ch <= 'z')
            ch -= 32;
        else
            ch += 32;
        return ch;
    }

    // 5
    vector<string> Ret;
    vector<string> binaryTreePaths(TreeNode *root)
    {
        dfs(root, "");
        return Ret;
    }

    void dfs(TreeNode *root, string path)
    {
        path += to_string(root->val);

        if (root->left == nullptr && root->right == nullptr)
        {
            Ret.push_back(path);
            return;
        }

        path += "->";
        if (root->left)
            dfs(root->left, path);
        if (root->right)
            dfs(root->right, path);
    }

    // 6
    int memo[201][201];
    int getMoneyAmount(int n)
    {
        return dfs(1, n);
    }

    int dfs(int left, int right)
    {
        if (left >= right)
            return 0;

        if (memo[left][right])
            return memo[left][right];

        int ret = INT_MAX;
        for (int head = left; head <= right; head++)
        {
            int tmp1 = dfs(left, head - 1);
            int tmp2 = dfs(head + 1, right);

            ret = min(ret, head + max(tmp1, tmp2));
        }

        memo[left][right] = ret;
        return ret;
    }
};