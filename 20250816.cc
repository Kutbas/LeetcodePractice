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
    int subarraySum(vector<int> &nums, int k)
    {
        unordered_map<int, int> hash;
        hash[0] = 1;

        int ret = 0, sum = 0;

        for (auto n : nums)
        {
            sum += n;
            if (hash.count(sum - k))
                ret += hash[sum - k];
            hash[sum]++;
        }

        return ret;
    }

    // 2
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    vector<vector<int>> pacificAtlantic(vector<vector<int>> &heights)
    {
        m = heights.size(), n = heights[0].size();
        vector<vector<bool>> pac(m, vector<bool>(n));
        vector<vector<bool>> atl(m, vector<bool>(n));

        for (int i = 0; i < m; i++)
            dfs(heights, i, 0, pac);
        for (int i = 0; i < n; i++)
            dfs(heights, 0, i, pac);
        for (int i = 0; i < m; i++)
            dfs(heights, i, n - 1, atl);
        for (int i = 0; i < n; i++)
            dfs(heights, m - 1, i, atl);

        vector<vector<int>> ret;

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (pac[i][j] && atl[i][j])
                    ret.push_back({i, j});

        return ret;
    }

    void dfs(vector<vector<int>> &heights, int i, int j, vector<vector<bool>> &vis)
    {
        vis[i][j] = true;

        for (int k = 0; k < 4; k++)
        {
            int x = i + dx[k], y = j + dy[k];
            if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && heights[x][y] >= heights[i][j])
            {
                vis[x][y] = true;
                dfs(heights, x, y, vis);
                vis[x][y] = false;
            }
        }
    }

    // 3
    int dx[8] = {0, 0, 1, -1, 1, 1, -1, -1};
    int dy[8] = {1, -1, 0, 0, 1, -1, 1, -1};
    int m, n;
    vector<vector<char>> updateBoard(vector<vector<char>> &board, vector<int> &click)
    {
        m = board.size(), n = board[0].size();

        int x = click[0], y = click[1];
        if (board[x][y] == 'M')
        {
            board[x][y] = 'X';
            return board;
        }

        dfs(board, x, y);

        return board;
    }

    void dfs(vector<vector<char>> &board, int i, int j)
    {
        int count = 0;

        for (int k = 0; k < 8; k++)
        {
            int x = i + dx[k], y = j + dy[k];
            if (x >= 0 && x < m && y >= 0 && y < n && board[x][y] == 'M')
                count++;
        }

        if (count)
            board[i][j] = count + '0';
        else
        {
            board[i][j] = 'B';

            for (int k = 0; k < 8; k++)
            {
                int x = i + dx[k], y = j + dy[k];
                if (x >= 0 && x < m && y >= 0 && y < n && board[x][y] == 'E')
                    dfs(board, x, y);
            }
        }
    }

    // 4
    int findPeakElement(vector<int> &nums)
    {
        int left = 0, right = nums.size() - 1;
        while (left < right)
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] > nums[mid - 1])
                left = mid + 1;
            else
                right = mid;
        }

        return nums[left];
    }

    // 5
    int m, n, step = 0, ret = 0;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    bool check[21][21];
    int uniquePathsIII(vector<vector<int>> &grid)
    {
        m = grid.size(), n = grid[0].size();

        int bx = 0, by = 0;
        step += 2;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == 1)
                {
                    bx = i;
                    by = j;
                }
                else if (grid[i][j] == 0)
                    step++;
            }

        check[bx][by] = true;
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
            if (x >= 0 && x < m && y >= 0 && y < n && !check[x][y] && grid[x][y] == 0)
            {
                check[x][y] = true;
                dfs(grid, x, y, count + 1);
                check[x][y] = false;
            }
        }
    }

    // 6
    int fib(int n)
    {
        if (n < 2)
            return n;

        return fib(n - 2) + fib(n - 1);
    }

    int canCompleteCircuit(vector<int> &gas, vector<int> &cost)
    {
        int n = gas.size();
        for (int i = 0; i < n; i++)
        {
            int rest = 0, step = 0;
            for (; step < n; step++)
            {
                int index = (i + step) % n;
                rest = rest + gas[index] - cost[index];
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