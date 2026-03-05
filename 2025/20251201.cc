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
    int m, n;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    vector<vector<int>> pacificAtlantic(vector<vector<int>> &heights)
    {
        m = heights.size(), n = heights[0].size();

        vector<vector<bool>> pac(m, vector<bool>(n)), atl(m, vector<bool>(n));

        for (int i = 0; i < m; i++)
        {
            dfs(heights, i, 0, pac);
            dfs(heights, i, n - 1, atl);
        }
        for (int i = 0; i < n; i++)
        {
            dfs(heights, 0, i, pac);
            dfs(heights, m - 1, i, atl);
        }

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
                dfs(heights, x, y, vis);
        }
    }

    // 2
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

    // 3
    int cnt, ret = 0;
    int kthSmallest(TreeNode *root, int k)
    {
        cnt = k;
        dfs(root);
        return ret;
    }

    void dfs(TreeNode *root)
    {
        if (root->left)
            dfs(root->left);

        if (--cnt == 0)
        {
            ret = root->val;
            return;
        }

        if (root->right)
            dfs(root->right);
    }

    // 4
    bool isInterleave(string s1, string s2, string s3)
    {
        int m = s1.size(), n = s2.size();
        if (m + n != s3.size())
            return false;

        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1));
        dp[0][0] = true;

        s1 = " " + s1;
        s2 = " " + s2;
        s3 = " " + s3;

        for (int i = 1; i <= m; i++)
        {
            if (s1[i] == s3[i])
                dp[i][0] = dp[i - 1][0];
            else
                break;
        }

        for (int i = 1; i <= n; i++)
        {
            if (s2[i] == s3[i])
                dp[0][i] = dp[0][i - 1];
            else
                break;
        }

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                bool from_s1 = (s1[i] == s3[i + j] && dp[i - 1][j]);
                bool from_s2 = (s2[j] == s3[i + j] && dp[i][j - 1]);

                dp[i][j] = from_s1 || from_s2;
            }

        return dp[m][n];
    }

    // 5
    int m, n;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    typedef pair<int, int> PIR;
    bool vis[51][51];

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

        int bx = 0, by = 0, ret = 0;
        for (auto &p : trees)
        {
            int a = p.first, b = p.second;
            int step = dfs(forest, bx, by, a, b);
            if (step == -1)
                return -1;
            ret += step;
            bx = a, by = b;
        }

        return ret;
    }

    int dfs(vector<vector<int>> &forest, int bx, int by, int ex, int ey)
    {
        if (bx == ex && by == ey)
            return 0;

        memset(vis, 0, sizeof vis);
        int ret = 0;
        queue<PIR> q;
        q.push({bx, by});
        vis[bx][by] = false;

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
                    if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && forest[x][y])
                    {
                        if (x == ex && y == ey)
                            return ret;

                        q.push({x, y});
                        vis[x][y] = true;
                    }
                }
            }
        }

        return ret;
    }

    // 6
    int subarraysDivByK(vector<int> &nums, int k)
    {
        int ret = 0, sum = 0;
        unordered_map<int, int> hash;
        hash[0] = 1;

        for (auto n : nums)
        {
            sum += n;
            int r = (sum + k) % k;
            if (hash.count(r))
                ret += hash[r];
            hash[r]++;
        }
        return ret;
    }

    // 7
    int subarraySum(vector<int> &nums, int k)
    {
        int sum = 0, ret = 0;
        unordered_map<int, int> hash;
        hash[0] = 1;

        for (auto n : nums)
        {
            sum += n;
            if (hash.count(sum - k))
                ret += hash[sum - k];
            else
                hash[sum]++;
        }

        return ret;
    }
};