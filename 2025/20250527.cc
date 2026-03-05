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

class Solution
{
public:
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    bool vis[301][301] = {0};
    int numIslands(vector<vector<char>> &grid)
    {
        m = grid.size(), n = grid[0].size();
        int ret = 0;

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (!vis[i][j] && grid[i][j] == '1')
                {
                    ret++;
                    BFS(grid, i, j);
                }

        return ret;
    }

    void BFS(vector<vector<char>> &grid, int i, int j)
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
                if (x >= 0 && x < m && y >= 0 && y < n && grid[x][y] == '1' && !vis[x][y])
                {
                    q.push({x, y});
                    vis[x][y] = true;
                }
            }
        }
    }

    struct cmp
    {
        bool operator()(const ListNode *l1, const ListNode *l2)
        {
            return l1->val > l2->val;
        }
    };

    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        priority_queue<ListNode *, vector<ListNode *>, cmp> q;

        for (auto &list : lists)
            if (list)
                q.push(list);

        ListNode *head = new ListNode(0);
        ListNode *prev = head;

        while (q.size())
        {
            auto t = q.top();
            q.pop();
            prev->next = t;
            prev = prev->next;

            if (t->next)
                q.push(t->next);
        }

        prev = head->next;
        delete head;
        return prev;
    }

    int widthOfBinaryTree(TreeNode *root)
    {
        unsigned int ret = 0;
        vector<pair<TreeNode *, unsigned int>> q;
        q.push_back({root, 1});

        while (q.size())
        {
            auto [x1, y1] = q[0];
            auto [x2, y2] = q.back();
            ret = max(ret, y2 - y1 + 1);

            vector<pair<TreeNode *, unsigned int>> tmp;
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

    vector<int> singleNumber(vector<int> &nums)
    {
        int xorsum = 0;
        for (auto n : nums)
            xorsum ^= n;
        for (int i = 1; i < nums.size() + 2; i++)
            xorsum ^= i;

        int lsb = xorsum == INT_MIN ? xorsum : xorsum & (-xorsum);

        int x = 0, y = 0;

        for (auto n : nums)
        {
            if (n & lsb)
                x ^= n;
            else
                y ^= n;
        }

        for (int i = 1; i < nums.size() + 2; i++)
        {
            if (i & lsb)
                x ^= i;
            else
                y ^= i;
        }

        return {x, y};
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
        int ret = 1;

        while (q.size())
        {
            ret++;
            int sz = q.size();
            while (sz--)
            {
                string t = q.front();
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
};