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
    int m, n, step = 0, res = 0;
    bool vis[21][21];
    int uniquePathsIII(vector<vector<int>> &grid)
    {
        m = grid.size(), n = grid[0].size();

        step += 2;
        int bx = 0, by = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == 0)
                {
                    step++;
                    continue;
                }
                else if (grid[i][j] == 1)
                {
                    bx = i, by = j;
                }
            }

        vis[bx][by] = true;
        dfs(grid, bx, by, 1);

        return res;
    }

    void dfs(vector<vector<int>> &grid, int i, int j, int count)
    {
        if (grid[i][j] == 2)
        {
            if (count == step)
                res++;
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

    // 2
    vector<vector<int>> ret;
    vector<int> path;
    bool check[7];
    vector<vector<int>> permute(vector<int> &nums)
    {
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
            if (!check[i])
            {
                path.push_back(nums[i]);
                check[i] = true;
                dfs(nums);
                path.pop_back();
                check[i] = false;
            }
        }
    }

    // 3
    int memo[201][201];
    int getMoneyAmount(int n)
    {
        return dfs(1, n);
    }

    int dfs(int left, int right)
    {
        if (memo[left][right])
            return memo[left][right];

        if (left > right)
            return 0;

        int ret = INT_MAX;
        for (int head = left; head <= right; head++)
        {
            int x = dfs(left, head - 1);
            int y = dfs(head + 1, right);

            ret = min(ret, head + max(x, y));
        }

        memo[left][right] = ret;
        return ret;
    }

    // 5
    int K;
    bool Check[101][101];
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int wardrobeFinishing(int m, int n, int cnt)
    {
        K = cnt;

        int ret = 1;
        queue<pair<int, int>> q;
        q.push({0, 0});
        Check[0][0] = true;

        while (q.size())
        {
            auto [a, b] = q.front();
            q.pop();
            for (int k = 0; k < 4; k++)
            {
                int x = a + dx[k], y = b + dy[k];
                if (x >= 0 && x < m && y >= 0 && y < n && !Check[x][y] && Check2(x, y))
                {
                    q.push({x, y});
                    Check[x][y] = true;
                    ret++;
                }
            }
        }

        return ret;
    }

    bool Check2(int i, int j)
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

    // 6
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
};

// 4
class KthLargest
{
public:
    KthLargest(int k, vector<int> &nums)
        : _k(k)
    {
        for (auto n : nums)
        {
            q.push(n);
            if (q.size() > _k)
                q.pop();
        }
    }

    int add(int val)
    {
        q.push(val);
        if (q.size() > _k)
            q.pop();
        return q.top();
    }

private:
    int _k;
    priority_queue<int, vector<int>, greater<int>> q;
};