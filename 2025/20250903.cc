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
    int calculateMinimumHP(vector<vector<int>> &d)
    {
        int m = d.size(), n = d[0].size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, INT_MAX));
        dp[m][n - 1] = dp[m - 1][n] = 1;

        for (int i = m - 1; i >= 0; i--)
            for (int j = n - 1; j >= 0; j--)
            {
                dp[i][j] = min(dp[i + 1][j], dp[i][j + 1]) - d[i][j];
                dp[i][j] = max(1, dp[i][j]);
            }

        return dp[0][0];
    }

    // 1
    vector<vector<string>> ret;
    vector<string> path;
    bool Col[10], Dig1[20], Dig2[20];
    int N;
    vector<vector<string>> solveNQueens(int n)
    {
        N = n;
        path.resize(n);
        for (int i = 0; i < n; i++)
            path[i].append(n, '.');

        dfs(0);

        return ret;
    }

    bool dfs(int row)
    {
        if (row == N)
        {
            ret.push_back(path);
            return true;
        }

        for (int col = 0; col < N; col++)
        {
            if (!Col[col] && !Dig1[row + col] && !Dig2[row - col + N])
            {
                Col[col] = Dig1[row + col] = Dig2[row - col + N] = true;
                path[row][col] = 'Q';
                dfs(row + 1);
                Col[col] = Dig1[row + col] = Dig2[row - col + N] = false;
                path[row][col] = '.';
            }
        }

        return false;
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
    int lengthOfLongestSubstring(string s)
    {
        int n = s.size(), ret = INT_MIN;
        int hash[128];

        for (int left = 0, right = 0; right < n; right++)
        {
            char in = s[right];
            ++hash[in];
            while (hash[in] > 1)
            {
                char out = s[left++];
                --hash[out];
            }
            ret = max(ret, right - left + 1);
        }

        return ret == INT_MIN ? 0 : ret;
    }

    // 4
    int m, n;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    vector<vector<int>> pacificAtlantic(vector<vector<int>> &heights)
    {
        m = heights.size(), n = heights[0].size();
        vector<vector<bool>> pac(m, vector<bool>(n));
        vector<vector<bool>> atl(m, vector<bool>(n));

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

    // 5
    vector<vector<int>> Ret;
    vector<int> Path;
    bool vis[7];
    vector<vector<int>> permute(vector<int> &nums)
    {
        dfs(nums);
        return Ret;
    }

    void dfs(vector<int> &nums)
    {
        if (Path.size() == nums.size())
        {
            Ret.push_back(Path);
            return;
        }

        for (int i = 0; i < nums.size(); i++)
        {
            if (!vis[i])
            {
                vis[i] = true;
                Path.push_back(nums[i]);
                dfs(nums);
                Path.pop_back();
                vis[i] = false;
            }
        }
    }

    // 6
    int K;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    bool check[101][101];
    int wardrobeFinishing(int m, int n, int cnt)
    {
        K = cnt;
        int ret = 1;
        queue<pair<int, int>> q;
        q.push({0, 0});
        check[0][0] = true;

        while (q.size())
        {
            auto [a, b] = q.front();
            q.pop();
            for (int k = 0; k < 4; k++)
            {
                int x = a + dx[k], y = b + dy[k];
                if (x >= 0 && x < m && y >= 0 && y < n && !check[x][y] && Check(x, y))
                {
                    ret++;
                    check[x][y] = true;
                    q.push({x, y});
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
};