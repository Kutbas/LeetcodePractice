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
    vector<vector<int>> ret;
    vector<int> path;

    vector<vector<int>> subsets(vector<int> &nums)
    {
        dfs(nums, 0);
        return ret;
    }

    void dfs(vector<int> &nums, int pos)
    {
        ret.push_back(path);

        for (int i = pos; i < nums.size(); i++)
        {
            path.push_back(nums[i]);
            dfs(nums, i + 1);
            path.pop_back();
        }
    }

    // 2
    typedef pair<TreeNode *, int> PTI;
    int widthOfBinaryTree(TreeNode *root)
    {
        vector<PTI> q;
        q.push_back({root, 1});

        int ret = 1;
        while (q.size())
        {
            int sz = q.size();
            vector<PTI> tmp;
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

    // 3
    long prev = LONG_MIN;
    bool isValidBST(TreeNode *root)
    {
        if (root == nullptr)
            return true;

        bool left = isValidBST(root->left);
        if (!left)
            return false;

        bool cur = false;
        if (prev < root->val)
            cur = true;
        if (!cur)
            return false;

        prev = root->val;
        bool right = isValidBST(root->right);
        return right;
    }

    // 4
    int m, n;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int step = 0, res = 0;
    bool Vis[21][21];
    int uniquePathsIII(vector<vector<int>> &grid)
    {
        m = grid.size(), n = grid[0].size();

        step += 2;
        int bx, by;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == 0)
                {
                    step++;
                    continue;
                }
                else if (grid[i][j] == 1)
                    bx = i, by = j;
            }

        Vis[bx][by] = true;
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
            if (x >= 0 && x < m && y >= 0 && y < n && !Vis[x][y] && grid[x][y] != -1)
            {
                Vis[x][y] = true;
                dfs(grid, x, y, count + 1);
                Vis[x][y] = false;
            }
        }
    }

    // 5
    int sum = 0, xorsum = 0;
    int subsetXORSum(vector<int> &nums)
    {
        DFS(nums, 0);
        return sum;
    }

    void DFS(vector<int> &nums, int pos)
    {
        sum += xorsum;

        for (int i = pos; i < nums.size(); i++)
        {
            xorsum ^= nums[i];
            DFS(nums, i + 1);
            xorsum ^= nums[i];
        }
    }

    // 6
    int fib(int n)
    {
        if (n == 0 || n == 1)
            return n;

        return fib(n - 2) + fib(n - 1);
    }

    // 7
    int waysToStep(int n)
    {
        if (n < 3)
            return n;

        int base = 1000000007;
        int dp1 = 1, dp2 = 2, dp3 = 4; // dp4=7,dp5=

        while (n-- != 3)
        {
            int tmp = ((dp1 + dp2) % base + dp3) % base;
            dp1 = dp2, dp2 = dp3, dp3 = tmp;
        }
        return dp3;
    }
};