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
    string changeStr(string s)
    {
        string ret;
        for (auto ch : s)
        {
            if (ch != '#')
                ret += ch;
            else if (ret.size())
                ret.pop_back();
        }
        return ret;
    }

    bool backspaceCompare(string s, string t)
    {
        return changeStr(s) == changeStr(t);
    }

    unordered_map<char, unordered_set<char>> hash;
    unordered_map<char, int> in;
    bool check = 0;
    string alienOrder(vector<string> &words)
    {
        for (auto &s : words)
            for (auto ch : s)
                in[ch] = 0;

        for (int i = 0; i < words.size(); i++)
            for (int j = i + 1; j < words.size(); j++)
            {
                add(words[i], words[j]);

                if (check)
                    return "";
            }

        queue<char> q;
        string ret;

        for (auto [a, b] : in)
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

        for (auto [a, b] : in)
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
                int a = s1[i], b = s2[i]; // a=t,b=f,t->f
                if (!hash.count(a) || !hash[a].count(b))
                {
                    hash[a].insert(b);
                    in[b]++;
                }
                break;
            }
        }

        if (i == s2.size() && i < s1.size())
            check = true;
        return;
    }

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int nearestExit(vector<vector<char>> &maze, vector<int> &e)
    {
        int m = maze.size(), n = maze[0].size();
        bool vis[101][101] = {0};

        queue<pair<int, int>> q;
        q.push({e[0], e[1]});
        vis[e[0]][e[1]] = true;

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
                    if (x >= 0 && x < m && y >= 0 && y < n && maze[x][y] == '.' && !vis[x][y])
                    {
                        if (x == 0 || x == m - 1 || y == 0 || y == n - 1)
                            return step;
                        q.push({x, y});
                        vis[x][y] = true;
                    }
                }
            }
        }

        return -1;
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

    vector<int> twoSum(vector<int> &nums, int target)
    {
        unordered_map<int, int> hash;

        for (int i = 0; i < nums.size(); i++)
        {
            if (hash.count(target - nums[i]))
                return {i, hash[target - nums[i]]};
            hash[nums[i]] = i;
        }
        return {-1, -1};
    }

    string removeDuplicates(string s)
    {
        string ret;
        for (auto ch : s)
        {
            if (ret.size() && ret.back() == ch)
                ret.pop_back();
            else
                ret += ch;
        }
        return ret;
    }

    int dx[4] = {0, 0, 1, -1};
    int dx[4] = {1, -1, 0, 0};
    int nearestExit(vector<vector<char>> &maze, vector<int> &entrance)
    {
        int m = maze.size(), n = maze[0].size();
        bool vis[101][101] = {0};

        queue<pair<int, int>> q;
        q.push({entrance[0], entrance[1]});
        vis[entrance[0]][entrance[1]] = true;

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
                    if (x >= 0 && x < m && y >= 0 && y < n && maze[x][y] == '.' && !vis[x][y])
                    {
                        if (x == 0 || x == m - 1 || y == 0 || y == n - 1)
                            return step;
                        q.push({x, y});
                        vis[x][y] = true;
                    }
                }
            }
        }

        return -1;
    }
};