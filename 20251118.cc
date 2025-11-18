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
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    int memo[16][16];
    bool vis[101][101];
    int getMaximumGold(vector<vector<int>> &grid)
    {
        m = grid.size(), n = grid[0].size();
        int ret = 0;

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j])
                    ret = max(ret, grid[i][j] + dfs(grid, i, j));

        return ret;
    }

    int dfs(vector<vector<int>> &grid, int i, int j)
    {
        if (memo[i][j])
            return memo[i][j];

        memset(vis, 0, sizeof vis);
        vis[i][j] = true;
        int ret = 0;
        for (int k = 0; k < 4; k++)
        {
            int x = i + dx[k], y = j + dy[k];
            if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && grid[x][y])
            {
                vis[x][y] = true;
                ret = max(ret, grid[x][y] + dfs(grid, x, y));
                vis[x][y] = false;
            }
        }

        memo[i][j] = ret;
        return ret;
    }

    // 3
    int findNumberOfLIS(vector<int> &nums)
    {
        int n = nums.size();

        vector<int> longestLen(n, 1);
        vector<int> ways(n, 1);
        int globalLongest = 1;
        int globalWays = 1;

        for (int i = 1; i < n; i++)
            for (int j = 0; j < i; j++)
            {
                if (nums[j] < nums[i])
                {
                    int newlen = longestLen[j] + 1;
                    if (newlen == longestLen[i])
                        ways[i] += ways[j];
                    else if (newlen > longestLen[i])
                    {
                        longestLen[i] = newlen;
                        ways[i] = ways[j];
                    }
                }

                if (globalLongest == longestLen[i])
                    globalWays += ways[i];
                else if (longestLen[i] > globalLongest)
                {
                    globalLongest = longestLen[i];
                    globalWays = ways[i];
                }
            }
        return globalWays;
    }

    // 4
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost)
    {
        int n = gas.size();

        for (int i = 0; i < n; i++)
        {
            int rest = 0, step = 0;
            for (; step < n; step++)
            {
                int index = (i + step) % n;
                rest += gas[index] - cost[index];
                if (rest < 0)
                    break;
            }

            if (rest >= 0)
                return i;
            i = i + step;
        }

        return -1;
    }
};

// 2
class DiningPhilosophers
{
public:
    DiningPhilosophers() {}

    void wantsToEat(int philosopher, function<void()> pickLeftFork,
                    function<void()> pickRightFork, function<void()> eat,
                    function<void()> putLeftFork,
                    function<void()> putRightFork)
    {
        int l = philosopher;
        int r = (philosopher + 1) % 5;

        if (l % 2 == 0)
        {
            lock[l].lock();
            lock[r].lock();
            pickLeftFork();
            pickRightFork();
        }
        else
        {
            lock[r].lock();
            lock[l].lock();
            pickLeftFork();
            pickRightFork();
        }
        eat();
        putLeftFork();
        putRightFork();
        lock[l].unlock();
        lock[r].unlock();
    }

private:
    std::mutex lock[5];
};