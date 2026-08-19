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
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
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

                for (auto &a : t->children)
                    q.push(a);
            }

            ret.push_back(tmp);
        }

        return ret;
    }

    // 2
    class LRUCache
    {
    public:
        LRUCache(int capacity) : _capacity(capacity) {}

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
        typedef list<pair<int, int>>::iterator LstItor;
        int _capacity;
        unordered_map<int, LstItor> _hash;
        list<pair<int, int>> _list;
    };

    // 3
    bool lemonadeChange(vector<int> &bills)
    {
        int hash[128] = {0};

        for (auto n : bills)
        {
            if (n == 5)
                hash[5]++;
            else if (n == 10)
            {
                if (!hash[5])
                    return false;
                hash[5]--, hash[10]++;
            }
            else
            {
                if (hash[5] && hash[10])
                    hash[5]--, hash[10]--;
                else if (hash[5] >= 3)
                    hash[5] -= 3;
                else
                    return false;
            }
        }

        return true;
    }

    // 4
    int minCost(vector<vector<int>> &costs)
    {
        int n = costs.size();
        vector<vector<int>> dp(n + 1, vector<int>(3));

        for (int i = 1; i <= n; i++)
        {
            dp[i][0] = min(dp[i - 1][1], dp[i - 1][2]) + costs[i - 1][0];
            dp[i][1] = min(dp[i - 1][0], dp[i - 1][2]) + costs[i - 1][1];
            dp[i][2] = min(dp[i - 1][1], dp[i - 1][0]) + costs[i - 1][2];
        }

        return min(dp[n][0], min(dp[n][1], dp[n][2]));
    }

    // 5
    bool checkPartitioning(string s)
    {
        int n = s.size();
        vector<vector<bool>> dp(n, vector<bool>(n));
        for (int i = n - 1; i >= 0; i--)
            for (int j = i; j < n; j++)
                if (s[i] == s[j])
                    dp[i][j] = j - i + 1 > 3 ? dp[i + 1][j - 1] : true;

        for (int i = 1; i < n - 1; i++)
            for (int j = i; j < n - 1; j++)
                if (dp[0][i - 1] && dp[i][j] && dp[j + 1][n - 1])
                    return true;

        return false;
    }

    // 6
    class MyQueue
    {
    private:
        stack<int> in, out;

        void in2out()
        {
            while (in.size())
            {
                out.push(in.top());
                in.pop();
            }
        }

    public:
        MyQueue() {}

        void push(int x) { in.push(x); }

        int pop()
        {
            if (out.empty())
                in2out();

            int r = out.top();
            out.pop();
            return r;
        }

        int peek()
        {
            if (out.empty())
                in2out();
            int r = out.top();
            return r;
        }

        bool empty() { return in.empty() && out.empty(); }
    };

    // 7
    vector<string> uncommonFromSentences(string s1, string s2)
    {
        unordered_map<string, int> hash;

        auto countWords = [&](const string &s)
        {
            istringstream iss(s);
            string word;
            while (iss >> word)
                hash[word]++;
        };

        countWords(s1);
        countWords(s2);

        vector<string> ret;
        for (auto &[a, b] : hash)
            if (b == 1)
                ret.push_back(a);

        return ret;
    }
};