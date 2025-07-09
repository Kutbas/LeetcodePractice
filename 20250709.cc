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
    bool vis[101][101];
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

    int widthOfBinaryTree(TreeNode *root)
    {
        unsigned int ret = 0;
        vector<pair<TreeNode *, unsigned int>> q;
        q.push_back({root, 1});

        while (q.size())
        {
            int sz = q.size();
            vector<pair<TreeNode *, unsigned int>> tmp;
            while (sz--)
            {
                auto [x1, y1] = q[0];
                auto [x2, y2] = q.back();
                ret = max(ret, y2 - y1 + 1);

                for (auto [x, y] : q)
                {
                    if (x->left)
                        tmp.push_back({x->left, 2 * y});
                    if (x->right)
                        tmp.push_back({x->right, 2 * y + 1});
                }
            }

            q = tmp;
        }

        return ret;
    }

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    bool vis[501][501];
    int numEnclaves(vector<vector<int>> &grid)
    {
        m = grid.size(), n = grid[0].size();
        for (int i = 0; i < m; i++)
        {
            if (grid[i][0] == 1)
                dfs(grid, i, 0);
            if (grid[i][n - 1] == 1)
                dfs(grid, i, n - 1);
        }

        for (int i = 0; i < n; i++)
        {
            if (grid[0][i] == 1)
                dfs(grid, 0, i);
            if (grid[m - 1][i] == 1)
                dfs(grid, m - 1, i);
        }

        int ret = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j] && !vis[i][j])
                    ret++;
        return ret;
    }

    void dfs(vector<vector<int>> &grid, int i, int j)
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
                if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && grid[x][y])
                {
                    q.push({x, y});
                    vis[x][y] = true;
                }
            }
        }
    }

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    vector<vector<int>> updateMatrix(vector<vector<int>> &mat)
    {
        m = mat.size(), n = mat[0].size();
        vector<vector<int>> dist(m, vector<int>(n, -1));
        queue<pair<int, int>> q;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (mat[i][j] == 0)
                {
                    dist[i][j] = 0;
                    q.push({i, j});
                }

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
                }
            }
        }

        return dist;
    }

    string minWindow(string s, string t)
    {
        int m = t.size();
        int hash1[128], hash2[128];
        for (char ch : t)
            hash1[ch]++;

        int begin = -1, minlen = INT_MAX;
        for (int left = 0, right = 0, count = 0; right < s.size(); right++)
        {
            char in = s[right];
            if (++hash2[in] <= hash1[in])
                count++;

            while (count == m)
            {
                if (right - left + 1 < minlen)
                {
                    begin = left;
                    minlen = right - left + 1;
                }
                char out = s[left++];
                if (hash2[out]-- <= hash1[out])
                    count--;
            }
        }

        return begin == -1 ? "" : s.substr(begin, minlen);
    }

    int lengthOfLIS(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> ret;
        ret.push_back(nums[0]);

        for (int i = 1; i < n; i++)
        {
            if (nums[i] > ret.back())
                ret.push_back(nums[i]);
            else
            {
                // 二分查找插入位置
                int left = 0, right = ret.size() - 1;
                while (left < right)
                {
                    int mid = left + (right - left) / 2;
                    if (ret[mid] < nums[i])
                        left = mid + 1;
                    else
                        right = mid;
                }
                ret[left] = nums[i];
            }
        }
        return ret.size();
    }

    bool increasingTriplet(vector<int> &nums)
    {
        int a = nums[0], b = INT_MAX;
        for (int i = 1; i < nums.size(); i++)
        {
            if (nums[i] > b)
                return true;
            else if (nums[i] > a)
                b = nums[i];
            else
                a = nums[i];
        }
        return false;
    }

    int findLengthOfLCIS(vector<int> &nums)
    {
        int ret = 0, n = nums.size();
        for (int i = 0; i < n;)
        {
            int j = i + 1;
            while (j < n && nums[j] > nums[j - 1])
                j++;
            ret = max(ret, j - i);
            i = j;
        }

        return ret;
    }

    int pivotIndex(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> f(n), g(n);
        for (int i = 1; i < nums.size(); i++)
            f[i] = f[i - 1] + nums[i - 1];
        for (int i = n - 2; i >= 0; i--)
            g[i] = g[i + 1] + nums[i + 1];
        for (int i = 0; i < n; i++)
            if (f[i] == g[i])
                return i;
        return -1;
    }

    string largestNumber(vector<int> &nums)
    {
        vector<string> strs;
        for (auto n : nums)
            strs.push_back(to_string(n));

        sort(strs.begin(), strs.end(), [&](const string &s1, const string &s2)
             { return s1 + s2 > s2 + s1; });

        string ret;
        for (auto &s : strs)
            ret += s;

        return ret[0] == '0' ? "0" : ret;
    }
};