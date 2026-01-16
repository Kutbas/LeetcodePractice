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
    bool vis[51][51];
    typedef pair<int, int> PIR;
    int cutOffTree(vector<vector<int>> &forest)
    {
        m = forest.size(), n = forest[0].size();

        vector<PIR> trees;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (forest[i][j] > 1)
                    trees.push_back({i, j});

        sort(trees.begin(), trees.end(), [&](const PIR &p1, const PIR &p2)
             { return forest[p1.first][p1.second] < forest[p2.first][p2.second]; });

        int ret = 0, bx = 0, by = 0;
        for (auto [a, b] : trees)
        {
            int step = dfs(forest, bx, by, a, b);
            if (step == -1)
                return -1;
            ret += step;
            bx = a, by = b;
        }

        return ret;
    }

    int dfs(vector<vector<int>> &f, int bx, int by, int ex, int ey)
    {
        if (bx == ex && by == ey)
            return 0;

        memset(vis, 0, sizeof vis);
        vis[bx][by] = true;
        queue<PIR> q;
        q.push({bx, by});

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
                    if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] &&
                        f[x][y])
                    {
                        if (x == ex && y == ey)
                            return ret;
                        vis[x][y] = true;
                        q.push({x, y});
                    }
                }
            }
        }

        return -1;
    }

    // 2
    string tree2str(TreeNode *root)
    {
        if (root == nullptr)
            return "";

        string ret = to_string(root->val);
        if (root->left || root->right)
        {
            ret += "(";
            ret += tree2str(root->left);
            ret += ")";
        }

        if (root->right)
        {
            ret += "(";
            ret += tree2str(root->right);
            ret += ")";
        }

        return ret;
    }

    // 3
    int largestSumAfterKNegations(vector<int> &nums, int k)
    {
        int count = 0, minElem = INT_MAX, n = nums.size();

        for (auto num : nums)
        {
            if (num < 0)
                count++;
            minElem = min(minElem, abs(num));
        }

        int ret = 0;
        if (count > k)
        {
            sort(nums.begin(), nums.end());
            for (int i = 0; i < k; i++)
                ret += -nums[i];
            for (int i = k; i < n; i++)
                ret += nums[i];
        }
        else
        {
            for (auto num : nums)
                ret += abs(num);

            if ((k - count) % 2 == 1)
                ret -= 2 * minElem;
        }

        return ret;
    }

    // 4
    vector<int> productExceptSelf(vector<int> &nums)
    {
        int n = nums.size();

        vector<int> f(n), g(n), ret(n);
        f[0] = g[n - 1] = 1;
        for (int i = 1; i < n; i++)
            f[i] = f[i - 1] * nums[i - 1];
        for (int i = n - 2; i >= 0; i--)
            g[i] = g[i + 1] * nums[i + 1];
        for (int i = 0; i < n; i++)
            ret[i] = f[i] * g[i];

        return ret;
    }

    // 5
    vector<vector<int>> ret;
    vector<int> path;
    int aim;
    vector<vector<int>> combinationSum(vector<int> &candidates, int target)
    {
        aim = target;
        dfs(candidates, 0, 0);
        return ret;
    }

    void dfs(vector<int> &nums, int pos, int sum)
    {
        if (sum > aim)
            return;

        if (sum == aim)
        {
            ret.push_back(path);
            return;
        }

        for (int i = pos; i < nums.size(); i++)
        {
            path.push_back(nums[i]);
            dfs(nums, i, sum + nums[i]);
            path.pop_back();
        }
    }
};