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
    vector<int> twoSum(vector<int> &nums, int target)
    {
        unordered_map<int, int> hash;
        for (int i = 0; i < nums.size(); i++)
        {
            int x = target - nums[i];
            if (hash.count(x))
                return {i, hash[x]};
            else
                hash[nums[i]] = i;
        }
        return {-1, -1};
    }

    int singleNumber(vector<int> &nums)
    {
        int ret = 0;
        for (int i = 0; i < 32; i++)
        {
            int tmp = 0;
            for (auto n : nums)
                if ((n >> i) & 1 == 1)
                    tmp++;

            tmp %= 3;
            if (tmp == 1)
                ret |= (1 << i);
        }

        return ret;
    }

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    bool vis[501][501] = {0};
    int numEnclaves(vector<vector<int>> &grid)
    {
        m = grid.size(), n = grid[0].size();
        for (int i = 0; i < m; i++)
        {
            if (grid[i][0] == 1)
                BFS(grid, i, 0);
            if (grid[i][n - 1] == 1)
                BFS(grid, i, n - 1);
        }

        for (int i = 0; i < n; i++)
        {
            if (grid[0][i] == 1)
                BFS(grid, 0, i);
            if (grid[m - 1][i] == 1)
                BFS(grid, m - 1, i);
        }

        int ret = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (!vis[i][j] && grid[i][j] == 1)
                    ret++;

        return ret;
    }

    void BFS(vector<vector<int>> &grid, int i, int j)
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
                if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && grid[x][y] == 1)
                {
                    q.push({x, y});
                    vis[x][y] = true;
                }
            }
        }
    }

    int findMin(vector<int> &nums)
    {
        int left = 0, n = nums.size(), right = n - 1;
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

    string changeStr(string s)
    {
        string ret;
        for (char ch : s)
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
};