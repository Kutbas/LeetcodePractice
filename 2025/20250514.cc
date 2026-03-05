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

struct cmp
{
    bool operator()(const ListNode *a, const ListNode *b)
    {
        return a->val > b->val;
    }
};

class Solution
{
public:
    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        priority_queue<ListNode *, vector<ListNode *>, cmp> q;
        for (auto &a : lists)
        {
            if (a)
                q.push(a);
        }

        ListNode *ret = new ListNode(0);
        ListNode *prev = ret;

        while (q.size())
        {
            auto t = q.top();
            q.pop();
            prev->next = t;
            prev = prev->next;

            if (t->next)
                q.push(t->next);
        }

        prev = ret->next;
        delete ret;
        return prev;
    }

    string longestCommonPrefix(vector<string> &strs)
    {
        for (int i = 0; i < strs[0].size(); i++)
        {
            for (int j = 1; j < strs.size(); j++)
                if (strs[0][i] != strs[j][i])
                    return strs[0].substr(0, i);
        }
        return strs[0];
    }

    bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
    {
        unordered_map<int, vector<int>> edges;
        vector<int> in(numCourses);

        for (auto v : prerequisites)
        {
            int a = v[0], b = v[1]; // b->a;
            edges[b].push_back(a);
            in[a]++;
        }

        queue<int> q;
        string ret;
        for (int i = 0; i < numCourses; i++)
            if (in[i] == 0)
                q.push(i);

        while (q.size())
        {
            auto t = q.front();
            q.pop();
            ret += t;

            for (auto a : edges[t])
                if (--in[a] == 0)
                    q.push(a);
        }

        return ret.size() == numCourses;
    }

    string convert(string s, int numRows)
    {
        if (numRows == 1)
            return s;

        string ret;
        int n = s.size(), d = 2 * numRows - 2;

        for (int i = 0; i < n; i += d)
            ret += s[i];
        for (int k = 1; k < numRows - 1; k++)
            for (int i = k, j = d - k; i < n || j < n; i += d, j += d)
            {
                if (i < n)
                    ret += s[i];
                if (j < n)
                    ret += s[j];
            }
        for (int i = numRows - 1; i < n; i += d)
            ret += s[i];

        return ret;
    }

    vector<int> findSubstring(string s, vector<string> &words)
    {
        int m = words.size(), len = words[0].size();
        vector<int> ret;

        unordered_map<string, int> hash1;
        for (auto word : words)
            hash1[word]++;

        for (int i = 0; i < len; i++)
        {
            unordered_map<string, int> hash2;
            for (int left = i, right = i, count = 0; right + len <= s.size(); right += len)
            {
                string in = s.substr(right, len);
                ++hash2[in];
                if (hash1.count(in) && hash2[in] <= hash1[in])
                    count++;
                while (right - left + 1 > len * m)
                {
                    string out = s.substr(left, len);
                    if (hash1.count(out) && hash2[out] <= hash1[out])
                        count--;
                    --hash2[out];
                    left += len;
                }
                if (count == m)
                    ret.push_back(left);
            }
        }

        return ret;
    }

    int m, n;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    bool vis[501][501] = {0};
    int numEnclaves(vector<vector<int>> &grid)
    {
        m = grid.size(), n = grid[0].size();

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (i == 0 || i == m - 1 || j == 0 || j == n - 1)
                {
                    if (grid[i][j] == 1)
                    {
                        BFS(grid, i, j);
                    }
                }

        int ret = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (!vis[i][j] && grid[i][j] == 1)
                {
                    ret++;
                    BFS(grid, i, j);
                }
        return ret;
    }

    void BFS(vector<vector<int>> &grid, int i, int j)
    {
        queue<pair<int, int>> q;
        q.push({i, j});
        vis[i][j] = true;

        while (q.size())
        {

            auto [a, b] = q.front();
            q.pop();
            for (int k = 0; k < 4; k++)
            {
                int x = a + dx[k], y = b + dy[k];
                if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && grid[x][y] == 1)
                {
                    q.push({x, y});
                    vis[x][y] = 1;
                }
            }
        }
    }
};