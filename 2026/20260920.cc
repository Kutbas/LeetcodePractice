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

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution
{
public:
    // 1
    vector<vector<int>> zigzagLevelOrder(TreeNode *root)
    {
        vector<vector<int>> ret;
        if (root == nullptr)
            return ret;

        queue<TreeNode *> q;
        q.push(root);
        int level = 1;

        while (q.size())
        {
            vector<int> tmp;
            int sz = q.size();
            while (sz--)
            {
                auto t = q.front();
                q.pop();

                tmp.push_back(t->val);

                if (t->left)
                    q.push(t->left);
                if (t->right)
                    q.push(t->right);
            }

            if (level % 2 == 0)
                reverse(tmp.begin(), tmp.end());
            ret.push_back(tmp);
            level++;
        }

        return ret;
    }

    // 2
    int ladderLength(string beginWord, string endWord, vector<string> &wordList)
    {
        if (beginWord == endWord)
            return 0;

        unordered_set<string> hash(wordList.begin(), wordList.end());
        unordered_set<string> vis;

        if (!hash.count(endWord))
            return 0;

        queue<string> q;
        q.push(beginWord);
        vis.insert(beginWord);
        int ret = 1;

        while (q.size())
        {
            ret++;
            int sz = q.size();
            while (sz--)
            {
                auto t = q.front();
                q.pop();

                for (int i = 0; i < t.size(); i++)
                {
                    string tmp = t;
                    for (char ch = 'a'; ch <= 'z'; ch++)
                    {
                        tmp[i] = ch;
                        if (hash.count(tmp) && !vis.count(tmp))
                        {
                            if (tmp == endWord)
                                return ret;
                            q.push(tmp);
                            vis.insert(tmp);
                        }
                    }
                }
            }
        }

        return 0;
    }

    // 3
    class LRUCache
    {
    public:
        LRUCache(int capacity) : _capacity(capacity)
        {
        }

        int get(int key)
        {
            auto ret = _hash.find(key);
            if (ret != _hash.end())
            {
                auto it = ret->second;
                _list.splice(_list.begin(), _list, it);
                return it->second;
            }
            return -1;
        }

        void put(int key, int value)
        {
            auto ret = _hash.find(key);
            if (ret != _hash.end())
            {
                auto it = ret->second;
                it->second = value;
                _list.splice(_list.begin(), _list, it);
            }
            else
            {
                if (_hash.size() == _capacity)
                {
                    pair<int, int> back = _list.back();
                    _hash.erase(back.first);
                    _list.pop_back();
                }
                _list.push_front({key, value});
                _hash[key] = _list.begin();
            }
        }

    private:
        typedef list<pair<int, int>>::iterator LstItor;
        int _capacity;
        unordered_map<int, LstItor> _hash;
        list<pair<int, int>> _list;
    };

    // 4
    int monotoneIncreasingDigits(int n)
    {
        string s = to_string(n);

        int i = 0, m = s.size();

        while (i + 1 < m && s[i] <= s[i + 1])
            i++;

        if (i + 1 == m)
            return n;

        while (i - 1 >= 0 && s[i] == s[i - 1])
            i--;

        s[i]--;
        for (int j = i + 1; j < m; j++)
            s[j] = '9';

        return stoi(s);
    }

    // 5
    int getMaxLen(vector<int> &nums)
    {
        int n = nums.size();

        vector<int> f(n + 1);
        auto g = f;
        int ret = 0;

        for (int i = 1; i <= n; i++)
        {
            if (nums[i - 1] > 0)
            {
                f[i] = f[i - 1] + 1;
                g[i] = g[i - 1] == 0 ? 0 : g[i - 1] + 1;
            }
            else if (nums[i - 1] < 0)
            {
                f[i] = g[i - 1] == 0 ? 0 : g[i - 1] + 1;
                g[i] = f[i - 1] + 1;
            }
            ret = max(ret, f[i]);
        }

        return ret;
    }

    // 6
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