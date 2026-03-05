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
    int maxDistance(vector<vector<int>> &grid)
    {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dist(m, vector<int>(n, -1));

        queue<pair<int, int>> q;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j])
                {
                    dist[i][j] = 0;
                    q.push({i, j});
                }

        int ret = -1;
        while (q.size())
        {
            auto [a, b] = q.front();
            q.pop();
            for (int k = 0; k < 4; k++)
            {
                int x = a + dx[k], y = b + dy[k];
                if (x >= 0 && x < m && y >= 0 && y < n && dist[x][y] == -1)
                {
                    dist[x][y] = dist[a][b] + 1;
                    q.push({x, y});
                    ret = max(ret, dist[x][y]);
                }
            }
        }

        return ret;
    }

    string removeDuplicates(string s)
    {
        string ret;
        for (auto ch : s)
        {
            if (ret.size() && ch == ret.back())
                ret.pop_back();
            else
                ret += ch;
        }

        return ret;
    }

    bool CheckPermutation(string s1, string s2)
    {
        if (s1.size() != s2.size())
            return false;
        unordered_map<char, int> hash;
        for (auto ch : s1)
            hash[ch]++;
        for (auto ch : s2)
            if (--hash[ch] < 0)
                return false;
        return true;
    }

    int calculate(string s)
    {
        vector<int> st;
        char op = '+';

        int i = 0, n = s.size();
        while (i < n)
        {
            int tmp = 0;
            if (s[i] == ' ')
                i++;
            else if (s[i] >= '0' && s[i] <= '9')
            {
                while (i < n && s[i] >= '0' && s[i] <= '9')
                    tmp = tmp * 10 + (s[i++] - '0');
                if (op == '+')
                    st.push_back(tmp);
                else if (op == '-')
                    st.push_back(-tmp);
                else if (op == '*')
                    st.back() *= tmp;
                else
                    st.back() /= tmp;
            }
            else
                op = s[i++];
        }

        int ret = 0;
        for (auto n : st)
            ret += n;
        return ret;
    }

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int maxDistance(vector<vector<int>> &grid)
    {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dist(m, vector<int>(n, -1));

        queue<pair<int, int>> q;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j])
                {
                    dist[i][j] = 0;
                    q.push({i, j});
                }

        int ret = 0;
        while (q.size())
        {
            auto [a, b] = q.front();
            q.pop();
            for (int k = 0; k < 4; k++)
            {
                int x = a + dx[k], y = b + dy[k];
                if (x >= 0 && x < m && y >= 0 && y < n && grid[x][y] == 0)
                {
                    q.push({x, y});
                    dist[x][y] = dist[a][b] + 1;
                    ret = max(ret, dist[x][y]);
                }
            }
        }

        return ret;
    }

    string addBinary(string a, string b)
    {
        int m = a.size(), n = b.size();
        string ret;

        int cur1 = m - 1, cur2 = n - 1;
        int t = 0;
        while (t || cur1 >= 0 || cur2 >= 0)
        {
            if (cur1 >= 0)
                t += (a[cur1--] - '0');
            if (cur2 >= 0)
                t += (b[cur2--] - '0');
            ret += (t % 2 + '0');
            t /= 2;
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    bool vis[101][101] = {0};
    int nearestExit(vector<vector<char>> &maze, vector<int> &entrance)
    {
        m = maze.size(), n = maze[0].size();

        queue<pair<int, int>> q;
        q.push({entrance[0], entrance[1]});
        vis[entrance[0]][entrance[1]] = true;

        int ret = 0;
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
                    if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && maze[x][y] == '.')
                    {
                        if (x == 0 || x == m - 1 || y == 0 || y == n - 1)
                            return ret;
                        q.push({x, y});
                        vis[x][y] = true;
                    }
                }
            }
        }

        return -1;
    }
};