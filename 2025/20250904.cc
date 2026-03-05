#include <bits/stdc++.h>
#include <mutex>
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
    int massage(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 0)
            return 0;

        vector<int> f(n);
        auto g = f;

        f[0] = nums[0];
        for (int i = 1; i < n; i++)
        {
            f[i] = g[i - 1] + nums[i];
            g[i] = max(f[i - 1], g[i - 1]);
        }

        return max(f[n - 1], g[n - 1]);
    }

    // 1
    int triangleNumber(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        int ret = 0, n = nums.size();

        for (int i = n - 1; i >= 2; i--)
        {
            int left = 0, right = i - 1;
            while (left < right)
            {
                if (nums[left] + nums[right] > nums[i])
                {
                    ret += right - left;
                    right--;
                }
                else
                    left++;
            }
        }

        return ret;
    }

    // 2
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

    // 3
    vector<vector<int>> ret;
    vector<int> path;
    bool vis[9];
    vector<vector<int>> permuteUnique(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        dfs(nums);
        return ret;
    }

    void dfs(vector<int> &nums)
    {
        if (path.size() == nums.size())
        {
            ret.push_back(path);
            return;
        }

        for (int i = 0; i < nums.size(); i++)
        {
            if (vis[i] || (i != 0 && nums[i] == nums[i - 1] && !vis[i - 1]))
                continue;
            vis[i] = true;
            path.push_back(nums[i]);
            dfs(nums);
            vis[i] = false;
            path.pop_back();
        }
    }

    // 5
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    bool Vis[101][101];
    int getMaximumGold(vector<vector<int>> &grid)
    {
        m = grid.size(), n = grid[0].size();

        int ret = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j])
                {
                    Vis[i][j] = true;
                    ret = max(ret, dfs(grid, i, j, grid[i][j]));
                    Vis[i][j] = false;
                }

        return ret;
    }

    int dfs(vector<vector<int>> &grid, int i, int j, int sum)
    {
        int ret = 0;
        for (int k = 0; k < 4; k++)
        {
            int x = i + dx[k], y = j + dy[k];
            if (x >= 0 && x < m && y >= 0 && y < n && !Vis[x][y] && grid[x][y])
            {
                Vis[x][y] = true;
                ret = max(ret, dfs(grid, x, y, sum + grid[x][y]));
                Vis[x][y] = false;
            }
        }

        return ret;
    }

    // 6
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    bool check[301][301];
    int numIslands(vector<vector<char>> &grid)
    {
        m = grid.size(), n = grid[0].size();
        int ret = 0;

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j] == '1' && !check[i][j])
                {
                    ret++;
                    dfs(grid, i, j);
                }

        return ret;
    }

    void dfs(vector<vector<char>> &grid, int i, int j)
    {
        queue<pair<int, int>> q;
        q.push({i, j});
        check[i][j] = true;

        while (q.size())
        {
            auto [a, b] = q.front();
            q.pop();
            for (int k = 0; k < 4; k++)
            {
                int x = a + dx[k], y = b + dy[k];
                if (x >= 0 && x < m && y >= 0 && y < n && !check[x][y] && grid[x][y] == '1')
                {
                    q.push({x, y});
                    check[x][y] = true;
                }
            }
        }
    }
};

// 4
class MedianFinder
{
public:
    priority_queue<int> left;
    priority_queue<int, vector<int>, greater<int>> right;

    MedianFinder()
    {
    }

    void addNum(int num)
    {
        if (left.size() == right.size())
        {
            if (left.empty() || num < left.top())
                left.push(num);
            else
            {
                right.push(num);
                left.push(right.top());
                right.pop();
            }
        }
        else
        {
            if (num >= left.top())
                right.push(num);
            else
            {
                left.push(num);
                right.push(left.top());
                left.pop();
            }
        }
    }

    double findMedian()
    {
        return left.size() == right.size() ? (left.top() + right.top()) / 2.0 : left.top();
    }
};