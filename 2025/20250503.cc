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
    vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int color)
    {
        int origin = image[sr][sc];
        if (origin == color)
            return image;

        m = image.size(), n = image[0].size();

        queue<pair<int, int>> q;
        q.push({sr, sc});
        image[sr][sc] = color;

        while (q.size())
        {
            auto [a, b] = q.front();
            q.pop();

            for (int k = 0; k < 4; k++)
            {
                int x = a + dx[k], y = b + dy[k];
                if (x >= 0 && x < m && y >= 0 && y < n && image[x][y] == origin)
                {
                    q.push({x, y});
                    image[x][y] = color;
                }
            }
        }

        return image;
    }

    string multiply(string num1, string num2)
    {
        int m = num1.size(), n = num2.size();

        string ret;
        vector<int> tmp(m + n - 1);

        for (int i = m - 1; i >= 0; i--)
            for (int j = n - 1; j >= 0; j--)
                tmp[i + j] += (num1[i] - '0') * (num2[j] - '0');

        int t = 0, cur = m + n - 2;
        while (t || cur >= 0)
        {
            if (cur >= 0)
                t += tmp[cur--];
            ret += (t % 10 + '0');
            t /= 10;
        }

        reverse(ret.begin(), ret.end());

        while (ret.size() > 1 && *ret.begin() == '0')
            ret.erase(0, 1);

        return ret;
    }

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    bool vis[201][201] = {0};
    int m, n;
    void solve(vector<vector<char>> &board)
    {
        m = board.size(), n = board[0].size();

        for (int i = 0; i < m; i++)
        {
            if (board[i][0] == 'O')
                BFS(board, i, 0);
            if (board[i][n - 1] == 'O')
                BFS(board, i, n - 1);
        }

        for (int j = 0; j < n; j++)
        {
            if (board[0][j] == 'O')
                BFS(board, 0, j);
            if (board[m - 1][j] == 'O')
                BFS(board, m - 1, j);
        }

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (board[i][j] == 'O')
                    board[i][j] = 'X';
                if (board[i][j] == '.')
                    board[i][j] = 'O';
            }

        return;
    }

    void BFS(vector<vector<char>> &board, int i, int j)
    {
        queue<pair<int, int>> q;
        q.push({i, j});
        board[i][j] = '.';
        vis[i][j] = true;

        while (q.size())
        {
            auto [a, b] = q.front();
            q.pop();

            for (int k = 0; k < 4; k++)
            {
                int x = a + dx[k], y = b + dy[k];
                if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && board[x][y] == 'O')
                {
                    q.push({x, y});
                    vis[x][y] = true;
                    board[x][y] = '.';
                }
            }
        }
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

    bool containsNearbyDuplicate(vector<int> &nums, int k)
    {
        unordered_map<int, int> hash;

        for (int i = 0; i < nums.size(); i++)
        {
            if (hash.count(nums[i]))
                if (i - hash[nums[i]] <= k)
                    return true;
            hash[nums[i]] = i;
        }
        return false;
    }

    int ladderLength(string beginWord, string endWord, vector<string> &wordList)
    {
        unordered_map<string, unordered_set<string>> hash(wordList.begin(), wordList.end());
        unordered_map<string, int> vis;

        if (!hash.count(endWord))
            return 0;

        int ret = 1;

        queue<string> q;
        q.push(beginWord);
        vis[beginWord] = 1;

        while (q.size())
        {
            int sz = q.size();
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
                        ret++;
                        q.push(tmp);
                        vis[tmp] = 1;
                    }
                }
            }
        }

        return 0;
    }

    int findMin(vector<int> &nums)
    {
        int left = 0, right = nums.size() - 1;
        int n = nums.size();
        while (left < right)
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] > nums[n - 1])
                left = mid + 1;
            else
                right = mid;
        }
        return nums[left];
    }

    vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
    {
        unordered_map<int, vector<int>> edges(numCourses);
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
                if (--in[a] == 0)
                    q.push(a);
        }

        return ret.size() == numCourses ? ret : vector<int>{};
    }

    int m, n;
    typedef pair<int, int> PIR;
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

        int x = 0, y = 0, ret = 0;
        for (auto &[a, b] : trees)
        {
            int step = bfs(f, x, y, a, b);
            if (step == -1)
                return -1;
            ret += step;
            x = a, y = b;
        }

        return ret;
    }

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};

    int bfs(vector<vector<int>> &f, int bx, int by, int ex, int ey)
    {
        if (bx == ex && by == ey)
            return 0;
        bool vis[51][51] = {0};

        queue<PIR> q;
        q.push({bx, by});
        vis[bx][by] = true;
        int step = 0;

        while (q.size())
        {
            step++;
            int sz = q.size();
            while (sz--)
            {
                auto [a, b] = q.front();
                q.pop();

                for (int k = 0; k < 4; k++)
                {
                    int x = a + dx[k], y = b + dy[k];
                    if (x >= 0 && x < m && y >= 0 && y < n && f[x][y] && !vis[x][y])
                    {
                        if (x == ex && y == ey)
                            return step;
                        q.push({x, y});
                        vis[x][y] = true;
                    }
                }
            }
        }
        return -1;
    }

    unordered_map<char, unordered_set<char>> hash;
    unordered_map<char, int> in;
    bool check;
    string alienOrder(vector<string> &words)
    {
        int n = words.size();
        for (auto &s : words)
            for (char ch : s)
                in[ch] = 0;

        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
            {
                add(words[i], words[j]);

                if (check)
                    return "";
            }

        string ret;
        queue<char> q;

        for (auto &[a, b] : in)
            if (b == 0)
                q.push(a);

        while (q.size())
        {
            auto t = q.front();
            q.pop();
            ret += t;

            for (auto a : hash[t])
                if (--in[a] == 0)
                    q.push(a);
        }

        for (auto &[a, b] : in)
            if (b != 0)
                return "";

        return ret;
    }

    void add(string &s1, string &s2)
    {
        int n = min(s1.size(), s2.size());
        int i = 0;

        for (; i < n; i++)
        {
            if (s1[i] != s2[i])
            {
                char a = s1[i], b = s2[i];
                if (!in.count(b) || !hash[a].count(b))
                {
                    hash[a].insert(b);
                    in[b]++;
                }
                break;
            }
        }

        if (i == s2.size() && i < s1.size())
            check = true;
    }

    typedef pair<int, int> PIR;
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

        int bx = 0, by = 0, ret = 0;
        for (auto &[a, b] : trees)
        {
            int step = BFS(f, bx, by, a, b);
            if (step == -1)
                return step;
            ret += step;
            bx = a, by = b;
        }
        return ret;
    }

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int BFS(vector<vector<int>> &f, int bx, int by, int ex, int ey)
    {
        if (bx == ex && by == ey)
            return 0;

        bool vis[51][51] = {0};
        int ret = 0;

        queue<PIR> q;
        q.push({bx, by});
        vis[bx][by] = true;

        while (q.size())
        {
            ret++;
            int sz = q.size();

            while (sz--)
            {
                auto &[a, b] = q.front();
                q.pop();

                for (int k = 0; k < 4; k++)
                {
                    int x = bx + dx[k], y = by + dy[k];
                    if (x >= 0 && x < m && y >= 0 && y < n && f[x][y] && !vis[x][y])
                    {
                        if (x == ex && y == ey)
                            return ret;
                        q.push({x, y});
                        vis[x][y] = true;
                    }
                }
            }
        }

        return ret;
    }
};