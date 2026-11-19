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
    int longestPalindrome(string s)
    {
        int n = s.size();
        int hash[128] = {0};
        for (char ch : s)
            hash[ch]++;

        int ret = 0;
        for (auto i : hash)
            ret += i / 2 * 2;

        return ret < n ? ret + 1 : ret;
    }

    // 2
    int findContentChildren(vector<int> &g, vector<int> &s)
    {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());

        int m = g.size(), n = s.size();
        int ret = 0;
        for (int i = 0, j = 0; i < m && j < n; i++, j++)
        {
            while (j < n && s[j] < g[i])
                j++;

            if (j < n)
                ret++;
        }

        return ret;
    }

    // 3
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
            else
            {
                if (n == 3)
                {
                    n = 1;
                    ret += 2;
                }
                else if (n % 4 == 1)
                {
                    n = n / 2;
                    ret += 2;
                }
                else
                {
                    n = n / 2 + 1;
                    ret += 2;
                }
            }
        }

        return ret;
    }

    // 4
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