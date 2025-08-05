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
    // 1
    bool row[9][10];
    bool col[9][10];
    bool grid[3][3][10];
    int m, n;
    void solveSudoku(vector<vector<char>> &board)
    {
        m = board.size(), n = board[0].size();
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
                if (board[i][j] != '.')
                {
                    int num = board[i][j] - '0';
                    row[i][num] = col[j][num] = grid[i / 3][j / 3][num] = true;
                }

        dfs(board);
    }

    bool dfs(vector<vector<char>> &board)
    {
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
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
                            else
                            {
                                board[i][j] = '.';
                                row[i][num] = col[j][num] = grid[i / 3][j / 3][num] = false;
                            }
                        }
                    }
                    return false;
                }

        return true;
    }

    // 2
    int count, ret = 0;
    int kthSmallest(TreeNode *root, int k)
    {
        count = k;
        dfs(root);
        return ret;
    }

    void dfs(TreeNode *root)
    {
        if (root->left)
            dfs(root->left);

        ret = root->val;
        if (--count == 0)
            return;

        if (root->right)
            dfs(root->right);
    }

    // 3
    vector<vector<int>> ret1;
    vector<int> path;
    int aim;
    vector<vector<int>> combinationSum(vector<int> &candidates, int target)
    {
        aim = target;
        dfs(candidates, 0, 0);
        return ret1;
    }

    void dfs(vector<int> &nums, int sum, int pos)
    {
        if (sum > aim || pos == nums.size())
            return;
        if (sum == aim)
        {
            ret1.push_back(path);
            return;
        }

        for (int i = pos; i < nums.size(); i++)
        {
            path.push_back(nums[i]);
            dfs(nums, sum + nums[i], i);
            path.pop_back();
        }
    }

    // 4
    bool row[9][10];
    bool col[9][10];
    bool grid[3][3][10];
    int m, n;
    bool isValidSudoku(vector<vector<char>> &board)
    {
        m = board.size(), n = board[0].size();
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (board[i][j] != '.')
                {
                    int num = board[i][j] - '0';
                    if (row[i][num] || col[j][num] || grid[i / 3][j / 3][num])
                        return false;
                    row[i][num] = col[j][num] = grid[i / 3][j / 3][num] = true;
                }

        return true;
    }

    // 5
    vector<vector<int>> ret2;
    vector<int> path2;
    bool check[7];
    vector<vector<int>> permute(vector<int> &nums)
    {
        dfs(nums, 0);
        return ret2;
    }

    void dfs(vector<int> &nums, int pos)
    {
        if (path2.size() == nums.size())
        {
            ret2.push_back(path2);
            return;
        }

        for (int i = 0; i < nums.size(); i++)
        {
            if (!check[i])
            {
                path2.push_back(nums[i]);
                check[i] = true;
                dfs(nums, i + 1);
                path2.pop_back();
                check[i] = false;
            }
        }
    }

    // 6
    vector<vector<int>> ret3;
    vector<int> path3;
    bool vis[11];
    vector<vector<int>> subsets(vector<int> &nums)
    {
        dfs3(nums, 0);
        return ret3;
    }

    void dfs3(vector<int> &nums, int pos)
    {
        ret3.push_back(path3);

        if (pos == nums.size())
            return;

        for (int i = pos; i < nums.size(); i++)
        {
            if (!vis[i])
            {
                path3.push_back(nums[i]);
                vis[i] = true;
                dfs3(nums, i + 1);
                vis[i] = false;
                path3.pop_back();
            }
        }
    }

    // 7
    vector<string> ret4;
    string path4;
    vector<string> binaryTreePaths(TreeNode *root)
    {
        dfs4(root, "");
        return ret4;
    }

    void dfs4(TreeNode *root, string path)
    {
        path += to_string(root->val);

        if (root->left == nullptr && root->right == nullptr)
        {
            ret4.push_back(path);
            return;
        }

        path += "->";
        if (root->left)
            dfs4(root->left, path);
        if (root->right)
            dfs4(root->right, path);
    }
};