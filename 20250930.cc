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
    int numberOfArithmeticSlices(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> dp(n);

        int sum = 0;
        for (int i = 2; i < n; i++)
        {
            dp[i] = nums[i] - nums[i - 1] == nums[i - 1] - nums[i - 2] ? dp[i - 1] + 1 : 0;
            sum += dp[i];
        }
        return sum;
    }

    int maxTurbulenceSize(vector<int> &arr)
    {
        int n = arr.size();
        vector<int> f(n, 1), g(n, 1);

        int ret = 1;
        for (int i = 1; i < n; i++)
        {
            if (arr[i - 1] < arr[i])
                f[i] = g[i - 1] + 1;
            else if (arr[i - 1] < arr[i])
                g[i] = f[i - 1] + 1;
            ret = max(ret, max(f[i], g[i]));
        }

        return ret;
    }

    // 1
    int ladderLength(string beginWord, string endWord, vector<string> &wordList)
    {
        if (beginWord == endWord)
            return 0;

        unordered_set<string> hash(wordList.begin(), wordList.end());
        unordered_set<string> vis;

        if (!hash.count(endWord))
            return 0;

        int ret = 1;
        queue<string> q;
        q.push(beginWord);
        while (q.size())
        {
            ret++;
            int sz = q.size();
            while (sz--)
            {
                auto t = q.front();
                q.pop();
                for (int i = 0; i < t.size(); i++)
                {
                    string tmp = t;
                    for (char ch = 'a'; ch <= 'z'; ch++)
                    {
                        tmp[i] = ch;
                        if (hash.count(tmp) && !vis.count(tmp))
                        {
                            if (tmp == endWord)
                                return ret;
                            q.push(tmp);
                            vis.insert(tmp);
                        }
                    }
                }
            }
        }

        return 0;
    }

    // 2
    int m, n;
    bool Row[9][10], Col[9][10], grid[3][3][10];
    void solveSudoku(vector<vector<char>> &board)
    {
        m = board.size(), n = board[0].size();
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (board[i][j] != '.')
                {
                    int num = board[i][j] - '0';
                    Row[i][num] = Col[j][num] = grid[i / 3][j / 3][num] = true;
                }

        dfs(board);
    }

    bool dfs(vector<vector<char>> &board)
    {
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (board[i][j] == '.')
                {
                    for (int num = 1; num <= 9; num++)
                    {
                        if (!Row[i][num] && !Col[j][num] && !grid[i / 3][j / 3][num])
                        {
                            Row[i][num] = Col[j][num] = grid[i / 3][j / 3][num] = true;
                            board[i][j] = num + '0';
                            if (dfs(board))
                                return true;
                            Row[i][num] = Col[j][num] = grid[i / 3][j / 3][num] = false;
                            board[i][j] = '.';
                        }
                    }
                    return false;
                }

        return true;
    }

    // 3
    ListNode *reverseList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *tmp = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;

        return tmp;
    }

    // 4
    int m, n;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
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
                    ret = max(ret, dfs(grid, i, j) + grid[i][j]);
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

    // 5
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
                    q.push({x, y});
                    vis[x][y] = true;
                }
            }
        }
    }

    // 6
    bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
    {
        vector<vector<int>> edges(numCourses);
        vector<int> in(numCourses);

        for (auto e : prerequisites)
        {
            int a = e[0], b = e[1]; // b->a
            edges[b].push_back(a);
            in[a]++;
        }

        queue<int> q;
        for (int i = 0; i < numCourses; i++)
            if (in[i] == 0)
                q.push(i);

        while (q.size())
        {
            auto t = q.front();
            q.pop();

            for (auto a : edges[t])
                if (--in[a] == 0)
                    q.push(a);
        }

        for (int i = 0; i < numCourses; i++)
            if (in[i])
                return false;
        return true;
    }
};