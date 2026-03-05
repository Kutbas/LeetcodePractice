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
    bool row[9][10];
    bool col[9][10];
    bool grid[3][3][10];
    void solveSudoku(vector<vector<char>> &board)
    {
        // 初始化
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
            {
                if (board[i][j] != '.')
                {
                    int num = board[i][j] - '0';
                    row[i][num] = col[j][num] = grid[i / 3][j / 3][num] = true;
                }
            }

        dfs(board);
    }

    bool dfs(vector<vector<char>> &board)
    {
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
            {
                if (board[i][j] == '.')
                {
                    for (int num = 1; num <= 9; num++)
                    {
                        if (!row[i][num] && !col[j][num] && !grid[i / 3][j / 3][num])
                        {
                            board[i][j] = num + '0';
                            row[i][num] = col[j][num] = grid[i / 3][j / 3][num] = true;
                            if (!dfs(board))
                            {
                                board[i][j] = '.';
                                row[i][num] = col[j][num] = grid[i / 3][j / 3][num] = false;
                            }
                            else
                                return true;
                        }
                    }
                    return false;
                }
            }

        return true;
    }

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    bool vis[7][7] = {0};
    int m, n;
    bool exist(vector<vector<char>> &board, string word)
    {
        m = board.size(), n = board[0].size();
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (board[i][j] == word[0])
                {
                    vis[i][j] = true;
                    if (dfs(board, i, j, word, 1))
                        return true;
                    vis[i][j] = false;
                }
            }
        return false;
    }

    bool dfs(vector<vector<char>> &board, int i, int j, string &word, int pos)
    {
        if (pos == word.size())
            return true;

        for (int k = 0; k < 4; k++)
        {
            int x = i + dx[k], y = j + dy[k];
            if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && board[x][y] == word[pos])
            {
                vis[x][y] = true;
                if (dfs(board, x, y, word, pos + 1))
                    return true;

                vis[x][y] = false;
            }
        }
        return false;
    }

    int ret, count;
    int kthSmallest(TreeNode *root, int k)
    {
        count = k;
        dfs(root);
        return ret;
    }

    void dfs(TreeNode *root)
    {
        if (root == nullptr || count == 0)
            return;

        dfs(root->left);
        count--;
        if (count == 0)
            ret = root->val;
        dfs(root->right);
    }

    bool check[16] = {0};
    int ret = 0;
    int countArrangement(int n)
    {
        dfs(1, n);
        return ret;
    }

    void dfs(int pos, int n)
    {
        if (pos == n + 1)
        {
            ret++;
            return;
        }

        for (int i = 1; i <= n; i++)
        {
            if (!check[i] && (pos % i == 0 || i % pos == 0))
            {
                check[i] = true;
                dfs(pos + 1, n);
                check[i] = false;
            }
        }
    }

    vector<vector<int>> ret;
    vector<int> path;
    vector<vector<int>> permute(vector<int> &nums)
    {
        dfs(0, nums);
        return ret;
    }

    void dfs(int pos, vector<int> &nums)
    {
        if (pos == nums.size())
        {
            ret.push_back(path);
            return;
        }

        for (int i = 0; i < nums.size(); i++)
        {
            path.push_back(nums[i]);
            dfs(i + 1, nums);
            path.pop_back();
        }
    }

    int widthOfBinaryTree(TreeNode *root)
    {
        int ret = 1;
        vector<pair<TreeNode *, int>> q;
        q.push_back({root, 1});

        while (q.size())
        {
            vector<pair<TreeNode *, int>> tmp;
            auto [x1, y1] = q[0];
            auto [x2, y2] = q.back();
            ret = max(ret, y2 - y1 + 1);

            for (auto &[x, y] : q)
            {
                if (x->left)
                    tmp.push_back({x->left, 2 * y});
                if (x->right)
                    tmp.push_back({x->right, 2 * y + 1});
            }

            q = tmp;
        }

        return ret;
    }

    vector<vector<int>> matrixBlockSum(vector<vector<int>> &mat, int k)
    {
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1] + mat[i - 1][j - 1];

        vector<vector<int>> ret(m, vector<int>(n));
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                int x1 = max(0, i - k) + 1, y1 = max(0, j - k) + 1;
                int x2 = min(m - 1, i + k) + 1, y2 = min(n - 1, j + k) + 1;
                ret[i][j] = dp[x2][y2] - dp[x1 - 1][y2] - dp[x2][y1 - 1] + dp[x1 - 1][y1 - 1];
            }

        return ret;
    }

    bool row[9][10];
    bool col[9][10];
    bool grid[3][3][10];

    void solveSudoku(vector<vector<char>> &board)
    {
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
            {
                if (board[i][j] != '.')
                {
                    int num = board[i][j] - '0';
                    row[i][num] = col[j][num] = grid[i / 3][j / 3][num] = true;
                }
            }

        dfs(board);
    }

    bool dfs(vector<vector<char>> &board)
    {
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
            {
                if (board[i][j] == '.')
                {
                    for (int num = 1; num <= 9; num++)
                    {
                        if (!row[i][num] && !col[j][num] && !grid[i / 3][j / 3][num])
                        {
                            board[i][j] = num + '0';
                            row[i][num] = col[j][num] = grid[i / 3][j / 3][num] = true;
                            if (dfs(board))
                                return true;

                            board[i][j] = '.';
                            row[i][num] = col[j][num] = grid[i / 3][j / 3][num] = false;
                        }
                    }

                    return false;
                }
            }

        return true;
    }

    vector<string> ret;
    string path;
    vector<string> binaryTreePaths(TreeNode *root)
    {
        if (root == nullptr)
            return ret;
        dfs(root);
        return ret;
    }

    void dfs(TreeNode *root)
    {
        path += to_string(root->val);
        if (root->left == nullptr && root->right == nullptr)
        {
            ret.push_back(path);
            return;
        }

        path += "->";
        if (root->left)
            dfs(root->left);
        if (root->right)
            dfs(root->right);
    }

    bool vis[16][16];
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n, ret = 0;
    int getMaximumGold(vector<vector<int>> &grid)
    {
        m = grid.size(), n = grid[0].size();
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j])
                {
                    vis[i][j] = true;
                    dfs(grid, i, j, grid[i][j]);
                    vis[i][j] = false;
                }
            }
    }

    void dfs(vector<vector<int>> &grid, int i, int j, int path)
    {
        ret = max(ret, path);
        for (int k = 0; k < 4; k++)
        {
            int x = i + dx[k], y = j + dy[k];
            if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && grid[x][y])
            {
                vis[x][y] = true;
                dfs(grid, x, y, path + grid[x][y]);
                vis[x][y] = false;
            }
        }
    }
};