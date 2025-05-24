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
    string decodeString(string s)
    {
        stack<int> nums;
        stack<string> st;
        string ret;
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
                int k = nums.top();
                nums.pop();
                while (k--)
                    tmp += ret;
                ret = tmp;
            }
            else
                ret += ch;
        }

        return ret;
    }

    bool validateStackSequences(vector<int> &pushed, vector<int> &popped)
    {
        stack<int> st;
        int i = 0, n = popped.size();
        for (int num : pushed)
        {
            if (st.size() && num == st.top())
            {
                st.pop();
                i++;
            }
            else
                st.push(num);
        }
        return i == n;
    }

    void duplicateZeros(vector<int> &arr)
    {
        int dest = -1, cur = 0, n = arr.size();
        while (cur < n)
        {
            if (arr[cur])
                dest++;
            else
                dest += 2;
            if (dest >= n - 1)
                break;
            cur++;
        }

        if (dest == n)
        {
            arr[n - 1] = 0;
            dest -= 2;
            cur--;
        }

        while (cur >= 0)
        {
            if (arr[cur])
                arr[dest--] = arr[cur--];
            else
            {
                arr[dest--] = 0;
                arr[dest--] = 0;
                cur--;
            }
        }
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
                string tmp = st.top();
                st.pop();
                int k = nums.top();
                nums.pop();
                while (k--)
                    tmp += ret;
                ret = tmp;
            }
            else
                ret += ch;
        }

        return ret;
    }

    typedef pair<int, int> PIR;

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    int cutOffTree(vector<vector<int>> &forest)
    {
        m = forest.size(), n = forest[0].size();
        vector<PIR> trees;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (forest[i][j] > 1)
                    trees.push_back({i, j});

        sort(trees.begin(), trees.end(), [&](const PIR &p1, const PIR &p2)
             { return forest[p1.first][p1.second] < forest[p2.first][p2.second]; });

        int ret = 0;
        int bx = 0, by = 0;
        for (auto [a, b] : trees)
        {
            int step = BFS(forest, bx, by, a, b);
            if (step == -1)
                return -1;
            ret += step;
            bx = a, by = b;
        }

        return ret;
    }

    int BFS(vector<vector<int>> &forest, int bx, int by, int ex, int ey)
    {
        if (bx == ex && by == ey)
            return 0;

        int ret = 0;
        queue<pair<int, int>> q;
        bool vis[51][51] = {0};
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
                    int x = a + dx[4], y = b + dy[4];
                    if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && forest[x][y] >= 1)
                    {
                        if (x == ex && y == ey)
                            return ret;
                        q.push({x, y});
                        vis[x][y] = true;
                        forest[x][y] = 1;
                    }
                }
            }
        }
        return -1;
    }

    vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
    {
        unordered_map<int, vector<int>> edges;
        vector<int> in(numCourses);
        for (auto &e : prerequisites)
        {
            int a = e[0], b = e[1]; // b->a
            edges[b].push_back(a);
            in[a]++;
        }

        queue<int> q;
        for (int i = 0; i < numCourses; i++)
            if (in[i] == 0)
                q.push(i);

        vector<int> ret;
        while (q.size())
        {
            auto t = q.front();
            q.pop();
            ret.push_back(t);

            for (auto a : edges[t])
                if (--in[a] == 0)
                    q.push(a);
        }

        return ret.size() == numCourses ? ret : vector<int>{};
    }
};