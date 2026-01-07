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
    // 2
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

    // 3
    vector<int> findAnagrams(string s, string p)
    {
        int n = s.size(), m = p.size();
        int hash1[128] = {0};
        int hash2[128] = {0};
        for (char ch : p)
            hash1[ch]++;

        vector<int> ret;
        for (int left = 0, right = 0, count = 0; right < n; right++)
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

    // 4
    bool Col[10], Dig1[20], Dig2[20];
    int N;
    vector<vector<string>> res;
    vector<string> pa;
    vector<vector<string>> solveNQueens(int n)
    {
        N = n;
        pa.resize(n);
        for (int i = 0; i < n; i++)
            pa[i].append(n, '.');

        dfs(0);

        return res;
    }

    bool dfs(int row)
    {
        if (row == N)
        {
            res.push_back(pa);
            return true;
        }

        for (int col = 0; col < N; col++)
        {
            if (!Col[col] && !Dig1[row + col] && !Dig2[row - col + N])
            {
                pa[row][col] = 'Q';
                Col[col] = Dig1[row + col] = Dig2[row - col + N] = true;
                dfs(row + 1);
                pa[row][col] = '.';
                Col[col] = Dig1[row + col] = Dig2[row - col + N] = false;
            }
        }

        return false;
    }

    // 5
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
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
                if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && heights[x][y] >= heights[a][b])
                {
                    vis[x][y] = true;
                    q.push({x, y});
                }
            }
        }
    }

    // 6
    bool vis[7];
    vector<vector<int>> r;
    vector<int> p;
    vector<vector<int>> permute(vector<int> &nums)
    {
        dfs(nums, 0);
        return r;
    }

    void dfs(vector<int> &nums, int pos)
    {
        if (p.size() == nums.size())
        {
            r.push_back(p);
            return;
        }

        for (int i = 0; i < nums.size(); i++)
        {
            if (!vis[i])
            {
                p.push_back(nums[i]);
                vis[i] = true;
                dfs(nums, pos + 1);
                vis[i] = false;
                p.pop_back();
            }
        }
    }

    // 7
    int findNumberOfLIS(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> longestLength(n, 1);
        vector<int> ways(n, 1);
        int globalLongestLength = 1;
        int globalWays = 1;

        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (nums[j] < nums[i])
                {
                    int newlen = longestLength[j] + 1;
                    if (newlen == longestLength[i])
                        ways[i] += ways[j];
                    else if (newlen > longestLength[i])
                    {
                        longestLength[i] = newlen;
                        ways[i] = ways[j];
                    }
                }
            }

            if (longestLength[i] == globalLongestLength)
                globalWays += ways[i];
            else if (longestLength[i] > globalLongestLength)
            {
                globalLongestLength = longestLength[i];
                globalWays = ways[i];
            }
        }

        return globalWays;
    }
};

// 1
const int N = 1010;
int n, v;
int V[N], W[N];
int dp[N][N];

int main()
{
    cin >> n >> v;
    for (int i = 1; i <= n; i++)
        cin >> V[i] >> W[i];

    memset(dp, 0, sizeof dp);
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= v; j++)
        {
            dp[i][j] = dp[i - 1][j];

            if (j >= V[i])
                dp[i][j] = max(dp[i][j], dp[i][j - V[i]] + W[i]);
        }

    cout << dp[n][v] << endl;

    memset(dp, 0, sizeof dp);
    for (int i = 1; i <= v; i++)
        dp[0][i] = -1;

    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= v; j++)
        {
            dp[i][j] = dp[i - 1][j];

            if (j >= V[i] && dp[i][j - V[i]] != -1)
                dp[i][j] = max(dp[i][j], dp[i][j - V[i]] + W[i]);
        }
    cout << (dp[n][v] == -1 ? 0 : dp[n][v]) << endl;
    return 0;
}