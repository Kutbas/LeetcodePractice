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
    int tribonacci(int n)
    {
        if (n == 0)
            return 0;
        if (n == 1 || n == 2)
            return 1;
        // 滚动数组
        int a = 0, b = 1, c = 1, d = 0;
        // 填表
        for (int i = 3; i <= n; i++)
        {
            d = a + b + c;
            a = b;
            b = c;
            c = d;
        }
        // 返回值
        return d;
    }

    // 1
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
        if (sum > aim || pos == nums.size())
            return;

        if (sum == aim)
        {
            ret.push_back(path);
            return;
        }

        for (int i = pos; i < nums.size(); i++)
        {
            path.push_back(nums[i]);
            dfs(nums, i, sum + nums[i]);
            path.pop_back();
        }
    }

    // 2
    long prev = LONG_MIN;
    bool isValidBST(TreeNode *root)
    {
        if (root == nullptr)
            return true;

        bool left = isValidBST(root->left);
        if (!left)
            return false;

        bool cur = false;
        if (prev < root->val)
            cur = true;
        if (!cur)
            return false;

        prev = root->val;
        bool right = isValidBST(root->right);
        return right;
    }

    // 3
    vector<vector<string>> Ret;
    vector<string> Path;
    bool Col[10], Dig1[20], Dig2[20];
    int N;
    vector<vector<string>> solveNQueens(int n)
    {
        N = n;
        Path.resize(n);
        for (int i = 0; i < n; i++)
            Path[i].append(n, '.');

        dfs(0);

        return Ret;
    }

    bool dfs(int row)
    {
        if (row == N)
        {
            Ret.push_back(Path);
            return true;
        }

        for (int col = 0; col < N; col++)
        {
            if (!Col[col] && !Dig1[row + col] && !Dig2[row - col + N])
            {
                Path[col] = 'Q';
                Col[col] = Dig1[row + col] = Dig2[row - col + N] = true;
                if (dfs(row + 1))
                    return true;
                else
                {
                    Col[col] = Dig1[row + col] = Dig2[row - col + N] = false;
                    Path[col] = '.';
                }
            }
        }
        return false;
    }

    // 4
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n, step = 0, res = 0;
    bool vis[21][21];
    int uniquePathsIII(vector<vector<int>> &grid)
    {
        m = grid.size(), n = grid[0].size();

        int bx = 0, by = 0;
        step += 2;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == 1)
                {
                    bx = i;
                    by = j;
                    continue;
                }
                else if (grid[i][j] == 0)
                    step++;
            }

        vis[bx][by] = true;
        dfs(grid, bx, by, 1);

        return res;
    }

    void dfs(vector<vector<int>> &grid, int i, int j, int count)
    {
        if (count == step)
        {
            res++;
            return;
        }

        for (int k = 0; k < 4; k++)
        {
            int x = i + dx[k], y = j + dy[k];
            if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && grid[x][y] != -1)
            {
                vis[x][y] = true;
                dfs(grid, x, y, count + 1);
                vis[x][y] = false;
            }
        }
    }

    // 5
    ListNode *swapPairs(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *tmp = swapPairs(head->next->next);
        ListNode *ret = head->next;
        ret->next = head;
        head->next = tmp;

        return ret;
    }

    // 6
    int maxSumDivThree(vector<int> &nums)
    {
        const int INF = 0x3f3f3f;
        int x1 = INF, x2 = INF;
        int y1 = INF, y2 = INF;

        int sum = 0;
        for (auto x : nums)
        {
            sum += x;

            if (x % 3 == 1)
            {
                if (x < x1)
                    x2 = x1, x1 = x;
                else if (x < x2)
                    x2 = x;
            }
            else if (x % 3 == 2)
            {
                if (x < y1)
                    y2 = y1, y1 = x;
                else if (x < y2)
                    y2 = x;
            }
        }

        if (sum % 3 == 0)
            return sum;
        else if (sum % 3 == 1)
            return max(sum - x1, sum - y1 - y2);
        else
            return max(sum - y1, sum - x1 - x2);
    }
};