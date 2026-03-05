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
    // 1
    vector<vector<int>> res;
    vector<int> path;
    vector<vector<int>> subsets(vector<int> &nums)
    {
        dfs(nums, 0);
        return res;
    }

    void dfs(vector<int> &nums, int pos)
    {
        res.push_back(path);

        if (pos == nums.size())
            return;

        for (int i = pos; i < nums.size(); i++)
        {
            path.push_back(nums[i]);
            dfs(nums, i + 1);
            path.pop_back();
        }
    }

    // 2
    int sum = 0, xorsum = 0;
    int subsetXORSum(vector<int> &nums)
    {
        dfs(nums, 0);
        return sum;
    }

    void dfs(vector<int> &nums, int pos)
    {
        sum += xorsum;

        if (pos == nums.size())
            return;

        for (int i = pos; i < nums.size(); i++)
        {
            xorsum ^= nums[i];
            dfs(nums, i + 1);
            xorsum ^= nums[i];
        }
    }

    // 3
    bool vis[101][101];
    int K;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int wardrobeFinishing(int m, int n, int cnt)
    {
        K = cnt;

        int ret = 1;
        queue<pair<int, int>> q;
        q.push({0, 0});
        vis[0][0] = true;

        while (q.size())
        {
            auto [a, b] = q.front();
            q.pop();

            for (int k = 0; k < 4; k++)
            {
                int x = a + dx[k], y = b + dy[k];
                if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && Check(x, y))
                {
                    ret++;
                    q.push({x, y});
                    vis[x][y] = true;
                }
            }
        }

        return ret;
    }

    bool Check(int i, int j)
    {
        int tmp = 0;
        while (i)
        {
            tmp += i % 10;
            i /= 10;
        }
        while (j)
        {
            tmp += j % 10;
            j /= 10;
        }

        return tmp <= K;
    }

    // 4
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n, step = 0, ret = 0;
    bool vis[21][21];
    int uniquePathsIII(vector<vector<int>> &grid)
    {
        m = grid.size(), n = grid[0].size();

        int bx = 0, by = 0;
        step += 2;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == 0)
                    step++;
                else if (grid[i][j] == 1)
                    bx = i, by = j;
            }

        vis[bx][by] = true;
        dfs(grid, bx, by, 1);

        return ret;
    }

    void dfs(vector<vector<int>> &grid, int i, int j, int count)
    {
        if (grid[i][j] == 2)
        {
            if (count == step)
                ret++;
            return;
        }

        for (int k = 0; k < 4; k++)
        {
            int x = i + dx[k], y = j + dy[k];
            if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && grid[x][y] != -1)
            {
                vis[x][y] = true;
                dfs(grid, x, y, count + 1);
                vis[x][y] = false;
            }
        }
    }

    // 5
    int deleteAndEarn(vector<int> &nums)
    {
        const int N = 10001;
        int arr[N] = {0};
        for (auto n : nums)
            arr[n] += n;

        vector<int> f(N), g(N);
        for (int i = 1; i < N; i++)
        {
            f[i] = g[i - 1] + arr[i];
            g[i] = max(f[i - 1], g[i - 1]);
        }

        return max(f[N - 1], g[N - 1]);
    }

    // 6
    int findLengthOfLCIS(vector<int> &nums)
    {
        int n = nums.size();
        int ret = 0;
        for (int left = 0, right = 0; right < n; right++)
        {
            while (right + 1 < n && nums[right + 1] > nums[right])
                right++;
            ret = max(ret, right - left + 1);
            left = right + 1;
        }
        return ret;
    }

    // 7
    int K, N;
    vector<vector<int>> res;
    vector<int> path;
    bool Vis[21];
    vector<vector<int>> combine(int n, int k)
    {
        K = k, N = n;
        dfs(1);
        return res;
    }

    void dfs(int pos)
    {
        if (path.size() == K)
        {
            res.push_back(path);
            return;
        }

        for (int i = pos; i <= N; i++)
        {
            if (!Vis[i])
            {
                path.push_back(i);
                Vis[i] = true;
                dfs(i+1);
                Vis[i] = false;
                path.pop_back();
            }
        }
    }
};