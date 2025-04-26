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
    vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
    {
        vector<vector<int>> edges(numCourses);
        vector<int> in(numCourses);

        for (auto &v : prerequisites)
        {
            int a = v[0], b = v[1];
            edges[b].push_back(a);
            in[a]++;
        }

        vector<int> ret;
        queue<int> q;

        for (int i = 0; i < numCourses; i++)
            if (in[i] == 0)
                q.push(i);

        while (q.size())
        {
            auto t = q.front();
            q.pop();
            ret.push_back(t);

            for (auto a : edges[t])
            {
                if (--in[a] == 0)
                    q.push(a);
            }
        }

        return ret.size() == numCourses ? ret : vector<int>{};
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

            if (level % 2 == 0)
                reverse(tmp.begin(), tmp.end());
            ret.push_back(tmp);
            level++;
        }

        return ret;
    }

    int singleNumber(vector<int> &nums)
    {
        int ret = 0;

        for (int i = 0; i < 31; i++)
        {
            int t = 0;
            for (auto n : nums)
                if ((n >> i) & 1 == 1)
                    t++;

            t %= 3;
            if (t == 1)
                ret |= (1 << i);
        }

        return ret;
    }

    int ladderLength(string beginWord, string endWord, vector<string> &wordList)
    {
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
            int sz = q.size();
            auto s = q.front();
            q.pop();
            ret++;

            for (int i = 0; i < s.size(); i++)
            {
                string tmp = s;
                for (char ch = 'a'; ch <= 'z'; ch++)
                {
                    tmp[i] = ch;
                    if (!vis.count(tmp) && hash.count(tmp))
                    {
                        if (tmp == endWord)
                            return ret;
                        vis.insert(tmp);
                        q.push(tmp);
                    }
                }
            }
        }

        return 0;
    }

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    void solve(vector<vector<char>> &board)
    {
        m = board.size(), n = board[0].size();

        for (int i = 0; i < m; i++)
        {
            if (board[i][0] == 'O')
                bfs(board, i, 0);
            if (board[i][n - 1] == 'O')
                bfs(board, i, n - 1);
        }

        for (int j = 0; j < n; j++)
        {
            if (board[0][j] == 'O')
                bfs(board, 0, j);
            if (board[m - 1][j] == 'O')
                bfs(board, m - 1, j);
        }

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (board[i][j] == 'O')
                    board[i][j] = 'X';
                else if (board[i][j] == '.')
                    board[i][j] = 'O';
            }
    }

    void bfs(vector<vector<char>> &board, int i, int j)
    {
        queue<pair<int, int>> q;
        q.push({i, j});
        board[i][j] = '.';

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
                    if (x >= 0 && x < m && y >= 0 && y < n &&
                        board[x][y] == 'O')
                    {
                        q.push({x, y});
                        board[x][y] = '.';
                    }
                }
            }
        }
    }

    vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
    {
        vector<vector<int>> edges(numCourses);
        vector<int> in(numCourses);

        for (auto &v : prerequisites)
        {
            int a = v[0], b = v[1];
            edges[b].push_back(a);
            in[a]++;
        }

        queue<int> q;
        vector<int> ret;

        for (int i = 0; i < numCourses; i++)
            if (in[i] == 0)
                q.push(i);

        while (q.size())
        {
            int sz = q.size();
            while (sz--)
            {
                auto t = q.front();
                q.pop();
                ret.push_back(t);
                for (auto a : edges[t])
                    if (--in[a] == 0)
                        q.push(a);
            }
        }

        return ret.size() == numCourses ? ret : vector<int>{};
    }

    bool isUnique(string astr)
    {
        if (astr.size() > 26)
            return false;

        int bitMap = 0;
        for (auto ch : astr)
        {
            int i = ch - 'a';
            if ((bitMap >> i) & 1 == 1)
                return false;
            bitMap |= (1 << i);
        }

        return true;
    }

    bool validateStackSequences(vector<int> &pushed, vector<int> &popped)
    {
        stack<int> st;
        int i = 0, n = popped.size();

        for (auto num : pushed)
        {
            st.push(num);
            while (!st.empty() && st.top() == popped[i])
            {
                st.pop();
                i++;
            }
        }

        return i == n;
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
            if (n & lsb)
                x ^= n;
            else
                y ^= n;
        }

        for (int i = 1; i <= nums.size() + 2; i++)
        {
            if (i & lsb)
                x ^= i;
            else
                y ^= i;
        }
        return {x, y};
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
};