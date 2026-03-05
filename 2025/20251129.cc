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
    int lastStoneWeight(vector<int> &stones)
    {
        priority_queue<int> q;
        for (auto n : stones)
            q.push(n);

        while (q.size() >= 2)
        {
            auto x = q.top();
            q.pop();
            auto y = q.top();
            q.pop();

            q.push(x - y);
        }

        return q.top();
    }

    // 2
    int findNumberOfLIS(vector<int> &nums)
    {
        int n = nums.size();

        vector<int> longestLen(n, 1);
        vector<int> ways(n, 1);
        int globalLongestLen = 1;
        int globalWays = 1;

        for (int i = 1; i < n; i++)
        {
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
            }

            if (globalLongestLen == longestLen[i])
                globalWays += ways[i];
            else if (globalLongestLen < longestLen[i])
            {
                globalLongestLen = longestLen[i];
                globalWays = ways[i];
            }
        }

        return globalWays;
    }

    // 3
    int findMin(vector<int> &nums)
    {
        int n = nums.size(), left = 0, right = n - 1;
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

    // 4
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    bool vis[16][16];
    int getMaximumGold(vector<vector<int>> &grid)
    {
        m = grid.size(), n = grid[0].size();

        int ret = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j])
                {
                    vis[i][j] = true;
                    ret = max(ret, grid[i][j] + dfs(grid, i, j));
                    vis[i][j] = false;
                }

        return ret;
    }

    int dfs(vector<vector<int>> &grid, int i, int j)
    {
        int ret = 0;
        for (int k = 0; k < 4; k++)
        {
            int x = i + dx[k], y = j + dy[k];
            if (x >= 0 && x < m && y >= 0 && y < n && grid[x][y])
            {
                vis[x][y] = true;
                ret = max(ret, grid[x][y] + dfs(grid, x, y));
                vis[x][y] = false;
            }
        }

        return ret;
    }

    // 5
    int lastStoneWeightII(vector<int> &stones)
    {
        int n = stones.size(), sum = 0;
        for (auto n : stones)
            sum += n;

        int m = sum / 2;

        vector<vector<int>> dp(n + 1, vector<int>(m + 1));
        for (int i = 1; i <= n; i++)
            for (int j = 0; j <= m; j++)
            {
                dp[i][j] = dp[i - 1][j];
                if (j >= stones[i - 1])
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - stones[i - 1]] + stones[i - 1]);
            }

        return sum - 2 * dp[n][m];
    }
};