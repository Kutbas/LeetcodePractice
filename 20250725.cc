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
    vector<vector<int>> ret;
    vector<int> path;
    bool check[7];
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

        for (int i = pos; i < nums.size(); i++)
        {
            if (!check[i])
            {
                path.push_back(nums[i]);
                check[i] = true;
                dfs(pos + 1, nums);
                path.pop_back();
                check[i] = false;
            }
        }
    }

    vector<string> ret1;
    string path1;
    vector<string> binaryTreePaths(TreeNode *root)
    {
        if (root == nullptr)
            return ret1;

        dfs(root);
        return ret1;
    }

    void dfs(TreeNode *root)
    {
        path1 += to_string(root->val);
        if (root->left == nullptr && root->right == nullptr)
        {
            ret1.push_back(path1);
            return;
        }

        path1 += "->";
        if (root->left)
            dfs(root->left);
        if (root->right)
            dfs(root->right);
    }

    int count = 0, ret2 = 0;
    int kthSmallest(TreeNode *root, int k)
    {
        count = k;
        dfs3(root);
        return ret2;
    }

    void dfs3(TreeNode *root)
    {
        if (root == nullptr || count == 0)
            return;

        dfs3(root->left);
        if (--count == 0)
            ret2 = root->val;
        dfs3(root->right);
    }

    bool row[9][10];
    bool col[9][10];
    bool grid[3][3][10];
    void solveSudoku(vector<vector<char>> &board)
    {
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
                            if (!dfs(board))
                            {
                                board[i][j] = '.';
                                row[i][num] = col[j][num] = grid[i / 3][j / 3][num] = false;
                                ;
                            }
                            else
                                return true;
                        }
                    }
                    return false;
                }
        return true;
    }

    vector<vector<int>> res;
    vector<int> pa;
    vector<vector<int>> subsets(vector<int> &nums)
    {
        dfs(nums, 0);
        return res;
    }

    void dfs(vector<int> &nums, int pos)
    {
        res.push_back(pa);
        if (pos == nums.size())
            return;

        for (int i = pos; i < nums.size(); i++)
        {
            pa.push_back(nums[i]);
            dfs(nums, pos + 1);
            pa.pop_back();
        }
    }
};