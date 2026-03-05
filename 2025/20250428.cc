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
    bool vis[301][301] = {0};
    int m, n;
    int numIslands(vector<vector<char>> &grid)
    {
        m = grid.size(), n = grid[0].size();
        int ret = 0;

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (!vis[i][j] && grid[i][j] == '1')
                {
                    ret++;
                    bfs(grid, i, j);
                }
            }

        return ret;
    }

    void bfs(vector<vector<char>> &grid, int i, int j)
    {
        queue<pair<int, int>> q;
        q.push({i, j});

        vis[i][j] = true;

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
                    if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && grid[x][y] == '1')
                    {
                        q.push({x, y});
                        vis[x][y] = true;
                    }
                }
            }
        }
    }

    vector<vector<int>> matrixBlockSum(vector<vector<int>> &mat, int k)
    {
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        vector<vector<int>> ret(m, vector<int>(n));

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1] + mat[i - 1][j - 1];

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                int x1 = max(0, i - k) + 1, y1 = max(0, j - k) + 1;
                int x2 = min(m - 1, i + k) + 1, y2 = min(n - 1, j + k) + 1;
                ret[i][j] = dp[x2][y2] - dp[x1 - 1][y2] - dp[x2][y1 - 1] + dp[x1 - 1][y1 - 1];
            }

        return ret;
    }

    int tmp[50010];
    int reversePairs(vector<int> &nums)
    {
        return mergeSort(nums, 0, nums.size() - 1);
    }

    int mergeSort(vector<int> &nums, int left, int right)
    {
        if (left >= right)
            return 0;

        int mid = left + (right - left) / 2, ret = 0;
        ret += mergeSort(nums, left, mid);
        ret += mergeSort(nums, mid + 1, right);

        int i = 0, cur1 = left, cur2 = mid + 1;

        while (cur1 <= mid)
        {
            while (cur2 <= right && nums[cur1] <= 2.0 * nums[cur2])
                cur2++;

            ret += right - cur2 + 1;
            cur1++;
        }

        cur1 = left, cur2 = mid + 1;
        while (cur1 <= mid && cur2 <= right)
            tmp[i++] = nums[cur1] <= nums[cur2] ? nums[cur2++] : nums[cur1++];

        while (cur1 <= mid)
            tmp[i++] = nums[cur1++];
        while (cur2 <= right)
            tmp[i++] = nums[cur2++];

        for (int j = left; j <= right; j++)
            nums[j] = tmp[j - left];

        return ret;
    }

    vector<int> singleNumber(vector<int> &nums)
    {
        int xorsum = 0;
        for (auto n : nums)
            xorsum ^= n;

        int lsb = xorsum == INT_MIN ? xorsum : xorsum & (-xorsum);
        int x = 0, y = 0;

        for (auto n : nums)
        {
            if (n & lsb)
                x ^= n;
            else
                y ^= n;
        }

        return {x, y};
    }

    vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
    {
        vector<int> ret;
        vector<vector<int>> edges(numCourses);
        vector<int> in(numCourses);

        for (auto &v : prerequisites)
        {
            int a = v[0], b = v[1];
            edges[b].push_back(a);
            in[a]++;
        }

        queue<int> q;
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

    int findPeakElement(vector<int> &nums)
    {
        int left = 0, right = nums.size() - 1;
        while (left < right)
        {
            int mid = left + (right - left + 1) / 2;
            if (nums[mid] > nums[mid - 1])
                left = mid;
            else
                right = mid - 1;
        }
        return nums[left];
    }

    int calculate(string s)
    {
        vector<int> tmp;
        char op = '+';

        for (int i = 0; i < s.size();)
        {
            if (s[i] == ' ')
            {
                i++;
                continue;
            }
            else if (s[i] >= '0' && s[i] <= '9')
            {
                int t = 0;
                while (i < s.size() && s[i] >= '0' && s[i] <= '9')
                {
                    t = t * 10 + (s[i++] - '0');
                }

                if (op == '+')
                    tmp.push_back(t);
                else if (op == '-')
                    tmp.push_back(-t);
                else if (op == '*')
                    tmp.back() *= t;
                else
                    tmp.back() /= t;
            }
            else
                op = s[i++];
        }

        int ret = 0;
        for (auto n : tmp)
            ret += n;
        return ret;
    }

    string changeStr(string s)
    {
        string ret;
        for (auto ch : s)
        {
            if (ch != '#')
                ret += ch;
            else if (!ret.empty())
                ret.pop_back();
        }
        return ret;
    }

    bool backspaceCompare(string s, string t)
    {
        return changeStr(s) == changeStr(t);
    }

    int pivotIndex(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> f(n), g(n);

        for (int i = 1; i < n; i++)
            f[i] = f[i - 1] + nums[i - 1];
        for (int i = n - 2; i >= 0; i--)
            g[i] = g[i + 1] + nums[i + 1];

        for (int i = 0; i < n; i++)
            if (f[i] == g[i])
                return i;

        return -1;
    }

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    bool vis[51][51] = {0};
    int m, n;
    int maxAreaOfIsland(vector<vector<int>> &grid)
    {
        m = grid.size(), n = grid[0].size();
        int ret = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (!vis[i][j] && grid[i][j] == 1)
                    ret = max(ret, BFS(grid, i, j));
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
                        ret++;
                        q.push({x, y});
                        vis[x][y] = true;
                    }
                }
            }
        }

        return ret;
    }
};