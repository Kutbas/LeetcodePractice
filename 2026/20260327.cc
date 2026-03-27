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
    bool Row[9][10], Col[9][10], Grid[3][3][10];
    int m, n;
    void solveSudoku(vector<vector<char>> &board)
    {
        m = board.size(), n = board[0].size();
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (isdigit(board[i][j]))
                {
                    int num = board[i][j] - '0';
                    Row[i][num] = Col[j][num] = Grid[i / 3][j / 3][num] = true;
                }

        dfs(board);
    }

    bool dfs(vector<vector<char>> &board)
    {
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (board[i][j] == '.')
                {
                    for (int num = 1; num <= 9; num++)
                    {
                        if (!Row[i][num] && !Col[j][num] &&
                            !Grid[i / 3][j / 3][num])
                        {
                            board[i][j] = num + '0';
                            Row[i][num] = Col[j][num] =
                                Grid[i / 3][j / 3][num] = true;
                            if (dfs(board))
                                return true;
                            board[i][j] = '.';
                            Row[i][num] = Col[j][num] =
                                Grid[i / 3][j / 3][num] = false;
                        }
                    }
                    return false;
                }
            }
        return true;
    }

    // 2
    vector<int> ret;
    vector<int> preorderTraversal(TreeNode *root)
    {
        if (root == nullptr)
            return ret;

        dfs(root);

        return ret;
    }

    void dfs(TreeNode *root)
    {
        if (root == nullptr)
            return;

        ret.push_back(root->val);
        dfs(root->left);
        dfs(root->right);
    }

    // 3
    vector<vector<string>> ret;
    vector<string> path;
    int N;
    bool Col[10], Dig1[20], Dig2[20];
    vector<vector<string>> solveNQueens(int n)
    {
        N = n;
        path.resize(n);
        for (int i = 0; i < n; i++)
            path[i].append(n, '.');

        dfs(0);

        return ret;
    }

    void dfs(int row)
    {
        if (row == N)
        {
            ret.push_back(path);
            return;
        }

        for (int col = 0; col < N; col++)
        {
            if (!Col[col] && !Dig1[row + col] && !Dig2[row - col + N])
            {
                path[row][col] = 'Q';
                Col[col] = Dig1[row + col] = Dig2[row - col + N] = true;
                dfs(row + 1);
                path[row][col] = '.';
                Col[col] = Dig1[row + col] = Dig2[row - col + N] = false;
            }
        }
    }
};