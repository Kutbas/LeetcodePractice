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
    string longestCommonPrefix(vector<string> &strs)
    {
        for (int i = 0; i < strs[0].size(); i++)
        {
            char tmp = strs[0][i];
            for (int j = 1; j < strs.size(); j++)
            {
                if (i == strs[j].size() || tmp != strs[j][i])
                    return strs[0].substr(0, i);
            }
        }
        return strs[0];
    }

    // 2
    vector<vector<int>> ret;
    vector<int> path;
    int aim;
    vector<vector<int>> combinationSum(vector<int> &candidates, int target)
    {
        aim = target;
        dfs(candidates, 0, 0);
        return ret;
    }

    void dfs(vector<int> &nums, int pos, int sum)
    {
        if (sum > aim)
            return;

        if (sum == aim)
        {
            ret.push_back(path);
            return;
        }

        for (int i = pos; i < nums.size(); i++)
        {
            path.push_back(nums[i]);
            dfs(nums, pos, sum + nums[i]);
            path.pop_back();
        }
    }

    // 3
    vector<string> res;
    string Path;
    int left = 0, right = 0, N;
    vector<string> generateParenthesis(int n)
    {
        N = n;
        dfs();
        return res;
    }

    void dfs()
    {
        if (right == N)
        {
            res.push_back(Path);
            return;
        }

        if (left < N)
        {
            left++;
            Path.push_back('(');
            dfs();
            Path.pop_back();
            left--;
        }

        if (right < left)
        {
            right++;
            Path.push_back(')');
            dfs();
            Path.pop_back();
            right--;
        }
    }

    // 4
    string multiply(string num1, string num2)
    {
        int m = num1.size(), n = num2.size();
        vector<int> tmp(m + n - 1);

        for (int i = m - 1; i >= 0; i--)
            for (int j = n - 1; j >= 0; j--)
                tmp[i + j] += (num1[i] - '0') * (num2[j] - '0');

        string ret;
        int i = m + n - 2, t = 0;
        while (i >= 0 || t)
        {
            if (i >= 0)
                t += tmp[i--];

            ret += to_string(t % 10);
            t /= 10;
        }

        reverse(ret.begin(), ret.end());
        while (ret.size() > 1 && ret[0] == '0')
            ret.erase(0, 1);

        return ret;
    }

    // 5
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    int memo[201][201];
    int longestIncreasingPath(vector<vector<int>> &matrix)
    {
        m = matrix.size(), n = matrix[0].size();
        int ret = 0;

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                ret = max(ret, dfs(matrix, i, j));

        return ret;
    }

    int dfs(vector<vector<int>> &matrix, int i, int j)
    {
        if (memo[i][j])
            return memo[i][j];

        int ret = 1;
        for (int k = 0; k < 4; k++)
        {
            int x = i + dx[k], y = j + dy[k];
            if (x >= 0 && x < m && y >= 0 && y < n && matrix[x][y] > matrix[i][j])
                ret = max(ret, dfs(matrix, x, y) + 1);
        }

        memo[i][j] = ret;
        return ret;
    }

    // 6
    bool Row[9][10], Col[9][10], grid[3][3][10];
    int m, n;
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
                            board[i][j] = num + '0';
                            Row[i][num] = Col[j][num] = grid[i / 3][j / 3][num] = true;
                            if (dfs(board))
                                return true;
                            board[i][j] = '.';
                            Row[i][num] = Col[j][num] = grid[i / 3][j / 3][num] = false;
                        }
                    }
                    return false;
                }

        return true;
    }
};