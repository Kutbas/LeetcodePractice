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
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    bool vis[201][201];

    void solve(vector<vector<char>> &board)
    {
        m = board.size(), n = board[0].size();
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (i == 0 || j == 0 || i == m - 1 || j == n - 1)
                    if (board[i][j] == 'O')
                        dfs(board, i, j);
            }

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (board[i][j] == '.')
                    board[i][j] = 'O';
                else if (board[i][j] == 'O')
                    board[i][j] = 'X';
            }
    }

    void dfs(vector<vector<char>> &board, int i, int j)
    {
        queue<pair<int, int>> q;
        q.push({i, j});
        board[i][j] = '.';
        vis[i][j] = true;

        while (q.size())
        {
            auto [a, b] = q.front();
            q.pop();
            for (int k = 0; k < 4; k++)
            {
                int x = i + dx[k], y = j + dy[k];
                if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && board[x][y] == 'O')
                {
                    q.push({x, y});
                    vis[x][y] = true;
                    board[x][y] = '.';
                }
            }
        }
    }

    // 2
    int ret = 0, N;
    bool v[16];
    int countArrangement(int n)
    {
        N = n;
        dfs(1);
        return ret;
    }

    void dfs(int pos)
    {
        if (pos == N)
        {
            ret++;
            return;
        }

        for (int i = 1; i <= N; i++)
        {
            if (!v[i] && (pos % i == 0 || i % pos == 0))
            {
                v[i] = true;
                dfs(pos + 1);
                v[i] = false;
            }
        }
    }

    // 3
    bool increasingTriplet(vector<int> &nums)
    {
        int a = nums[0], b = INT_MAX;
        for (int i = 1; i < nums.size(); i++)
        {
            if (nums[i] > b)
                return true;
            else if (nums[i] > a)
                b = nums[i];
            else
                a = nums[i];
        }
        return false;
    }

    // 4
    vector<vector<string>> ret1;
    vector<string> path;
    int N;
    bool check[10], checkDig1[20], checkDig2[20];
    vector<vector<string>> solveNQueens(int n)
    {
        N = n;
        path.resize(n);
        for (int i = 0; i < n; i++)
            path[i].append(n, '.');

        dfs(0);
        return ret1;
    }

    void dfs(int row)
    {
        if (row == N)
        {
            ret1.push_back(path);
            return;
        }

        for (int col = 0; col < N; col++)
        {
            if (!check[col] && !checkDig1[row + col] && !checkDig2[row - col + N])
            {
                check[col] = checkDig1[row + col] = checkDig2[row - col + N] = true;
                path[row][col] = 'Q';
                dfs(row + 1);
                path[row][col] = '.';
                check[col] = checkDig1[row + col] = checkDig2[row - col + N] = false;
            }
        }
    }

    // 5
    TreeNode *pruneTree(TreeNode *root)
    {
        if (root == nullptr)
            return nullptr;

        if (root->left)
            root->left = pruneTree(root->left);
        if (root->right)
            root->right = pruneTree(root->right);

        if (root->left == nullptr && root->right == nullptr && root->val == 0)
            return nullptr;

        return root;
    }

    // 6
    vector<string> ret2;
    string path2;
    vector<string> letterCasePermutation(string s)
    {
        dfs(s, 0);
        return ret2;
    }

    void dfs(string &s, int pos)
    {
        if (pos == s.size())
        {
            ret2.push_back(path2);
            return;
        }

        char ch = s[pos];

        path2.push_back(ch);
        dfs(s, pos + 1);
        path2.pop_back();

        if (!isdigit(ch))
        {
            char tmp = change(ch);
            path2.push_back(tmp);
            dfs(s, pos + 1);
            path2.pop_back();
        }
    }

    char change(char ch)
    {
        if (ch >= 'a' && ch <= 'z')
            ch -= 32;
        else
            ch += 32;
        return ch;
    }

    // 7
    int aim, ret = 0;
    int findTargetSumWays(vector<int> &nums, int target)
    {
        aim = target;
        dfs(nums, 0, 0);
        return ret;
    }

    void dfs(vector<int> &nums, int sum, int pos)
    {
        if (pos == nums.size())
        {
            if (sum == aim)
                ret++;
            return;
        }

        dfs(nums, sum + nums[pos], pos + 1);
        dfs(nums, sum - nums[pos], pos + 1);
    }
};