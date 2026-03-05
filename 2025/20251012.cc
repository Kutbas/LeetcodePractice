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
    bool isMatch(string s, string p)
    {
        int m = s.size(), n = p.size();
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1));

        s = ' ' + s;
        p = ' ' + p;
        dp[0][0] = true;
        for (int j = 2; j <= n; j += 2)
            if (p[j] == '*')
                dp[0][j] = true;
            else
                break;

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                if (p[j] == '*')
                    dp[i][j] = dp[i][j - 2] && (p[j - 1] == '.' || p[j - 1] == s[i]) && dp[i - 1][j];
                else
                    dp[i][j] = (p[j] == s[i] || p[j] == '.') && dp[i - 1][j - 1];

        return dp[m][n];
    }

    bool isInterleave(string s1, string s2, string s3)
    {
        int m = s1.size(), n = s2.size();
        if (m + n != s3.size())
            return false;

        s1 = " " + s1, s2 = " " + s2, s3 = " " + s3;
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1));
        dp[0][0] = true;
        for (int j = 1; j <= n; j++)
            if (s2[j] == s3[j])
                dp[0][j] = true;
            else
                break;

        for (int i = 1; i <= m; i++)
            if (s1[i] == s3[i])
                dp[i][0] = true;
            else
                break;

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                dp[i][j] = (s1[i] == s3[i + j] && dp[i - 1][j]) || (s2[j] == s3[i + j] && dp[i][j - 1]);

        return dp[m][n];
    }

    // 1
    vector<int> productExceptSelf(vector<int> &nums)
    {
        int n = nums.size();

        vector<int> f(n), g(n);
        f[0] = g[n - 1] = 1;

        for (int i = 1; i < n; i++)
            f[i] = f[i - 1] * nums[i - 1];
        for (int i = n - 2; i >= 0; i--)
            g[i] = g[i + 1] * nums[i + 1];

        vector<int> ret(n);
        for (int i = 0; i < n; i++)
            ret[i] = f[i] * g[i];

        return ret;
    }

    // 2
    int dx[8] = {0, 0, 1, -1, 1, 1, -1, -1};
    int dy[8] = {1, -1, 0, 0, 1, -1, 1, -1};
    int m, n;
    vector<vector<char>> updateBoard(vector<vector<char>> &board, vector<int> &click)
    {
        m = board.size(), n = board[0].size();

        int bx = click[0], by = click[1];
        if (board[bx][by] == 'M')
        {
            board[bx][by] = 'X';
            return board;
        }

        dfs(board, bx, by);

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
        {
            board[i][j] = count + '0';
            return;
        }
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

    // 3
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
            if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && grid[x][y])
            {
                vis[x][y] = true;
                ret = max(ret, grid[x][y] + dfs(grid, x, y));
                vis[x][y] = false;
            }
        }

        return ret;
    }

    // 4
    vector<int> twoSum(vector<int> &nums, int target)
    {
        unordered_map<int, int> hash;
        for (int i = 0; i < nums.size(); i++)
        {
            int x = target - nums[i];
            if (hash.count(x))
                return {i, hash[x]};
            hash[nums[i]] = i;
        }

        return {-1, -1};
    }

    // 5
    int jump(vector<int> &nums)
    {
        int n = nums.size(), left = 0, right = 0, maxPos = 0, ret = 0;

        while (left <= right)
        {
            if (maxPos >= n - 1)
                return ret;

            for (int i = 0; i < right; i++)
                maxPos = max(maxPos, i + nums[i]);

            left = right + 1;
            right = maxPos;
            ret++;
        }

        return -1;
    }

    // 6
    vector<vector<int>> ret;
    vector<int> path;
    int K;
    vector<vector<int>> combinationSum(vector<int> &candidates, int target)
    {
        K = target;
        dfs(candidates, 0, 0);
        return ret;
    }

    void dfs(vector<int> &nums, int sum, int pos)
    {
        if (sum > K)
            return;

        if (sum == K)
        {
            ret.push_back(path);
            return;
        }

        for (int i = pos; i < nums.size(); i++)
        {
            path.push_back(nums[i]);
            dfs(nums, sum + nums[i], i);
            path.pop_back();
        }
    }

    // 7
    vector<int> findAnagrams(string s, string p)
    {
        int m = p.size();
        int hash1[128] = {0};
        int hash2[128] = {0};

        for (char ch : p)
            hash1[ch]++;

        vector<int> ret;
        for (int left = 0, right = 0, count = 0; right < s.size(); right++)
        {
            char in = s[right];
            if (++hash2[in] <= hash1[in])
                count++;

            while (right - left + 1 > m)
            {
                char out = s[left++];
                if (hash2[out]-- <= hash1[out])
                    count--;
            }
            if (count == m)
                ret.push_back(left);
        }

        return ret;
    }
};