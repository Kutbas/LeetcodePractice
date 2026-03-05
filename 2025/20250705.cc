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
    int uniquePaths(int m, int n)
    {
        vector<vector<int>> memo(m + 1, vector<int>(n + 1));
        return dfs(m, n, memo);
    }

    int dfs(int i, int j, vector<vector<int>> &memo)
    {
        if (memo[i][j] != 0)
            return memo[i][j];

        if (i == 0 || j == 0)
            return 0;
        if (i == 1 && j == 1)
        {
            memo[i][j] = 1;
            return 1;
        }

        memo[i][j] = dfs(i - 1, j, memo) + dfs(i, j - 1, memo);
        return memo[i][j];
    }

    string removeDuplicates(string s)
    {
        string ret;
        for (char ch : s)
        {
            while (ret.size() && ret.back() == ch)
                ret.pop_back();
            ret.push_back(ch);
        }
        return ret;
    }

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    vector<vector<int>> highestPeak(vector<vector<int>> &isWater)
    {
        m = isWater.size(), n = isWater[0].size();

        queue<pair<int, int>> q;
        vector<vector<int>> dist(m, vector<int>(n, -1));
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (isWater[i][j])
                {
                    dist[i][j] = 0;
                    q.push({i, j});
                }

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
                    if (x >= 0 && x < m && y >= 0 && y < n && dist[x][y] == -1)
                    {
                        q.push({x, y});
                        dist[x][y] = dist[a][b] + 1;
                    }
                }
            }
        }

        return dist;
    }

    int ladderLength(string beginWord, string endWord, vector<string> &wordList)
    {
        if (beginWord == endWord)
            return 1;

        unordered_set<string> hash(wordList.begin(), wordList.end());
        unordered_set<string> vis;
        if (!hash.count(endWord))
            return 0;

        queue<string> q;
        q.push(beginWord);
        int ret = 1;

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
                            vis.insert(tmp);
                            q.push(tmp);
                        }
                    }
                }
            }
        }

        return 0;
    }

    bool CheckPermutation(string s1, string s2)
    {
        if (s1.size() != s2.size())
            return false;
        int hash[128];
        for (char ch : s1)
            hash[ch]++;
        for (char ch : s2)
            if (--hash[ch] < 0)
                return false;

        return true;
    }

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int n;
    int maxDistance(vector<vector<int>> &grid)
    {
        n = grid.size();
        vector<vector<int>> dist(n, vector<int>(n, -1));
        queue<pair<int, int>> q;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j])
                {
                    q.push({i, j});
                    dist[i][j] = 0;
                }

        int ret = -1;

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
                    if (x >= 0 && x < n && y >= 0 && y < n && dist[x][y] == -1)
                    {
                        q.push({x, y});
                        dist[x][y] = dist[a][b] + 1;
                        ret = max(ret, dist[x][y]);
                    }
                }
            }
        }

        return ret;
    }
};