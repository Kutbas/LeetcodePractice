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

typedef pair<string, int> PSI;

struct cmp
{
    bool operator()(const PSI &p1, const PSI &p2)
    {
        if (p1.second == p2.second)
            return p1.first < p2.first;
        return p1.second > p2.second;
    }
};

class Solution
{
public:
    vector<string> topKFrequent(vector<string> &words, int k)
    {
        unordered_map<string, int> hash;
        for (auto &word : words)
            hash[word]++;

        priority_queue<PSI, vector<PSI>, cmp> q;
        for (auto [a, b] : hash)
            q.push({a, b});

        vector<string> ret;
        while (k--)
        {
            auto [a, b] = q.top();
            q.pop();
            ret.push_back(a);
        }
        return ret;
    }

    string multiply(string num1, string num2)
    {
        int m = num1.size(), n = num2.size();
        vector<int> tmp(m + n - 1);

        for (int i = m - 1; i >= 0; i--)
            for (int j = n - 1; j >= 0; j--)
                tmp[i + j] += (num1[i] - '0') * (num2[j] - '0');

        string ret;
        int t = 0, i = m + n - 2;
        while (i >= 0 || t)
        {
            if (i >= 0)
                t += tmp[i--];
            ret += (t % 10 + '0');
            t /= 10;
        }

        reverse(ret.begin(), ret.end());
        while (ret.size() > 1 && ret.front() == '0')
            ret.erase(0, 1);

        return ret;
    }

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    bool vis[501][501] = {0};
    int m, n;
    int numEnclaves(vector<vector<int>> &grid)
    {
        m = grid.size(), n = grid[0].size();

        for (int i = 0; i < m; i++)
        {
            if (grid[i][0] == 1)
                BFS(grid, i, 0);
            if (grid[i][n - 1] == 1)
                BFS(grid, i, n - 1);
        }

        for (int i = 0; i < n; i++)
        {
            if (grid[0][i] == 1)
                BFS(grid, 0, i);
            if (grid[m - 1][i] == 1)
                BFS(grid, m - 1, i);
        }

        int ret = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j] == 1 && !vis[i][j])
                {
                    ret += BFS(grid, i, j);
                }
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
            int sz = q.size();
            while (sz--)
            {
                auto [a, b] = q.front();
                q.pop();
                for (int k = 0; k < 4; k++)
                {
                    int x = a + dx[k], y = b + dy[k];
                    if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && grid[x][y] == 1)
                    {
                        q.push({x, y});
                        vis[x][y] = true;
                        ret++;
                    }
                }
            }
        }
        return ret;
    }

    int ladderLength(string beginWord, string endWord, vector<string> &wordList)
    {
        unordered_set<string> hash(wordList.begin(), wordList.end());
        unordered_set<string> vis;

        if (!hash.count(endWord))
            return 0;
        if (beginWord == endWord)
            return 1;

        queue<string> q;
        q.push(beginWord);
        vis.insert(beginWord);
        int ret = 0;

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
            int sz = q.size();
            vector<int> tmp;
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

            if (level++ % 2 == 0)
                reverse(tmp.begin(), tmp.end());
            ret.push_back(tmp);
        }

        return ret;
    }

    bool validateStackSequences(vector<int> &pushed, vector<int> &popped)
    {
        stack<int> st;

        int i = 0, n = popped.size();
        for (auto x : pushed)
        {
            st.push(x);
            while (st.size() && st.top() == popped[i])
            {
                st.pop();
                i++;
            }
        }
        return i == n;
    }
};