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
    int minMutation(string startGene, string endGene, vector<string> &bank)
    {
        unordered_set<string> hash(bank.begin(), bank.end());
        unordered_set<string> vis;
        string change = "ATGC";

        if (!hash.count(endGene))
            return -1;
        if (startGene == endGene)
            return 0;

        int ret = 0;
        queue<string> q;
        q.push(startGene);
        while (q.size())
        {
            ret++;
            auto t = q.front();
            q.pop();
            for (int i = 0; i < 8; i++)
            {
                string tmp = t;
                for (int j = 0; j < 4; j++)
                {
                    tmp[i] = change[j];
                    if (hash.count(tmp) && !vis.count(tmp))
                    {
                        if (tmp == endGene)
                            return ret;
                        q.push(tmp);
                        vis.insert(tmp);
                    }
                }
            }
        }

        return -1;
    }

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

    typedef pair<int, int> PIR;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    int cutOffTree(vector<vector<int>> &f)
    {
        m = f.size(), n = f[0].size();
        vector<PIR> trees;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (f[i][j] > 1)
                    trees.push_back({i, j});

        sort(trees.begin(), trees.end(), [&](const PIR &p1, const PIR &p2)
             { return f[p1.first][p1.second] < f[p2.first][p2.second]; });

        int bx = 0, by = 0;
        int ret = 0;
        for (auto [a, b] : trees)
        {
            int step = BFS(f, bx, by, a, b);
            if (step == -1)
                return -1;
            ret += step;
            bx = a, by = b;
        }
        return ret;
    }

    int BFS(vector<vector<int>> &f, int bx, int by, int ex, int ey)
    {
        if (bx == ex && by == ey)
            return 0;

        int ret = 0;
        bool vis[51][51] = {0};
        queue<PIR> q;
        q.push({bx, by});
        vis[bx][by] = true;

        while (q.size())
        {
            ret++;

            int sz = q.size();
            while (sz--)
            {
                auto [a, b] = q.front();
                q.pop();
                for (int k = 0; k < 4; k++)
                {
                    int x = a + dx[k], y = b + dy[k];
                    if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && f[x][y])
                    {
                        if (x == ex && y == ey)
                            return ret;
                        q.push({x, y});
                        vis[x][y] = 1;
                    }
                }
            }
        }

        return -1;
    }

    vector<int> missingTwo(vector<int> &nums)
    {
        int xorsum = 0;
        for (auto n : nums)
            xorsum ^= n;
        for (int i = 1; i <= nums.size() + 2; i++)
            xorsum ^= i;

        int lsb = xorsum == INT_MIN ? xorsum : xorsum & (-xorsum);

        int x = 0, y = 0;
        for (auto n : nums)
        {
            if (lsb & n)
                x ^= n;
            else
                y ^= n;
        }
        for (int i = 1; i <= nums.size() + 2; i++)
        {
            if (lsb & i)
                x ^= i;
            else
                y ^= i;
        }

        return {x, y};
    }

    int widthOfBinaryTree(TreeNode *root)
    {
        unsigned int ret = 0;
        vector<pair<TreeNode *, unsigned int>> q;
        q.push_back({root, 1});

        while (q.size())
        {
            auto &[x1, y1] = q[0];
            auto &[x2, y2] = q.back();
            ret = max(ret, y2 - y1 + 1);

            vector<pair<TreeNode *, unsigned int>> tmp;
            for (auto &[a, b] : q)
            {
                if (a->left)
                    tmp.push_back({a->left, 2 * b});
                if (a->right)
                    tmp.push_back({a->right, 2 * b + 1});
            }
            q = tmp;
        }

        return ret;
    }

    int widthOfBinaryTree(TreeNode *root)
    {
        unsigned ret = 0;
        vector<pair<TreeNode *, unsigned int>> q;
        q.push_back({root, 1});

        while (q.size())
        {
            auto &[x1, y1] = q[0];
            auto &[x2, y2] = q.back();
            ret = max(ret, y2 - y1 + 1);

            vector<pair<TreeNode *, unsigned int>> tmp;
            for (auto &[a, b] : q)
            {
                if (a->left)
                    tmp.push_back({a->left, 2 * b});
                if (a->right)
                    tmp.push_back({a->right, 2 * b + 1});
            }
            q = tmp;
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
            LtIter it = ret->second;
            _LRUlist.splice(_LRUlist.begin(), _LRUlist, it);
            return it->second;
        }
        else
            return -1;
    }

    void put(int key, int value)
    {
        auto ret = _hash.find(key);
        if (ret == _hash.end())
        {
            if (_capacity == _hash.size())
            {
                pair<int, int> back = _LRUlist.back();
                _hash.erase(back.first);
                _LRUlist.pop_back();
            }

            _LRUlist.push_front(make_pair(key, value));
            _hash[key] = _LRUlist.begin();
        }
        else
        {
            LtIter it = ret->second;
            it->second = value;
            _LRUlist.splice(_LRUlist.begin(), _LRUlist, it);
        }
    }

private:
    typedef list<pair<int, int>>::iterator LtIter;
    list<pair<int, int>> _LRUlist;
    unordered_map<int, LtIter> _hash;
    size_t _capacity;
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
            LtIter it = ret->second;
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
            LtIter it = ret->second;
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

            _list.push_front(make_pair(key, value));
            _hash[key] = _list.begin();
        }
    }

private:
    typedef list<pair<int, int>>::iterator LtIter;
    list<pair<int, int>> _list;
    unordered_map<int, LtIter> _hash;
    size_t _capacity;
};

class LRUCache
{
public:
    LRUCache(int capacity) : _capacity(capacity) {}

    int get(int key)
    {
        auto ret = _hash.find(key);
        if (ret != _hash.end())
        {
            LtIter it = ret->second;
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
            LtIter it = ret->second;
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
            _list.push_front(make_pair(key, value));
            _hash[key] = _list.begin();
        }
    }

private:
    typedef list<pair<int, int>>::iterator LtIter;
    list<pair<int, int>> _list;
    unordered_map<int, LtIter> _hash;
    size_t _capacity;
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
            LtIter it = ret->second;
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
            LtIter it = ret->second;
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
            _list.push_front(make_pair(key, value));
            _hash[key] = _list.begin();
        }
    }

private:
    typedef list<pair<int, int>>::iterator LtIter;
    list<pair<int, int>> _list;
    unordered_map<int, LtIter> _hash;
    size_t _capacity;
};