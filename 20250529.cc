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

                for (auto &node : t->children)
                    if (node)
                        q.push(node);
            }
            ret.push_back(tmp);
        }

        return ret;
    }

    string decodeString(string s)
    {
        stack<int> nums;
        stack<string> st;
        string ret;
        int k = 0;

        for (char ch : s)
        {
            if (isdigit(ch))
                k = k * 10 + k - '0';
            else if (ch == '[')
            {
                nums.push(k);
                k = 0;
                st.push(ret);
                ret = "";
            }
            else if (ch == ']')
            {
                int n = nums.top();
                nums.pop();
                string tmp = st.top();
                st.pop();
                while (n--)
                    tmp += ret;
                ret = tmp;
            }
            else
                ret += ch;
        }

        return ret;
    }

    int findMaxLength(vector<int> &nums)
    {
        unordered_map<int, int> hash;
        hash[0] = -1;
        int sum = 0, ret = 0;

        for (int i = 0; i < nums.size(); i++)
        {
            sum += nums[i] == 0 ? -1 : 1;
            if (hash.count(sum))
                ret = max(ret, i - hash[sum]);
            else
                hash[sum] = i;
        }
        return ret;
    }

    string decodeString(string s)
    {
        string ret;
        stack<int> nums;
        stack<string> st;
        int k = 0;

        for (char ch : s)
        {
            if (isdigit(ch))
                k = k * 10 + ch - '0';
            else if (ch == '[')
            {
                nums.push(k);
                k = 0;
                st.push(ret);
                ret = "";
            }
            else if (ch == ']')
            {
                string tmp = st.top();
                st.pop();
                int n = nums.top();
                nums.pop();
                while (n--)
                    tmp += ret;
                ret = tmp;
            }
            else
                ret += ch;
        }

        return ret;
    }

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    bool vis[51][51] = {0};
    int m, n;
    int maxAreaOfIsland(vector<vector<int>> &grid)
    {
        m = grid.size(), n = grid[0].size();
        int ret = 0;

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (!vis[i][j] && grid[i][j] == 1)
                    ret = max(ret, BFS(grid, i, j));

        return ret;
    }

    int BFS(vector<vector<int>> &grid, int i, int j)
    {
        queue<pair<int, int>> q;
        q.push({i, j});
        vis[i][j] = true;

        int ret = 1;
        while (q.size())
        {
            auto [a, b] = q.front();
            q.pop();
            for (int k = 0; k < 4; k++)
            {
                int x = a + dx[k], y = b + dy[k];
                if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && grid[x][y] == 1)
                {
                    ret++;
                    q.push({x, y});
                    vis[x][y] = true;
                }
            }
        }

        return ret;
    }
};

class LRUCache
{
public:
    LRUCache(int capacity)
        : _capacity(capacity)
    {
    }

    int get(int key)
    {
        auto ret = _hash.find(key);
        if (ret != _hash.end())
        {
            LtItor it = ret->second;
            _list.splice(_list.begin(), _list, it);
            return it->second;
        }
        else
            return -1;
    }

    void put(int key, int value)
    {
        auto ret = _hash.find(key);
        if (ret != _hash.end())
        {
            LtItor it = ret->second;
            it->second = value;
            _list.splice(_list.begin(), _list, it);
        }
        else
        {
            if (_capacity == _hash.size())
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
    typedef list<pair<int, int>>::iterator LtItor;
    int _capacity;
    list<pair<int, int>> _list;
    unordered_map<int, LtItor> _hash;
};