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
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        ListNode *ret = new ListNode(0);
        ListNode *prev = ret;

        ListNode *cur1 = l1, *cur2 = l2;
        int t = 0;
        while (t || cur1 || cur2)
        {
            if (cur1)
            {
                t += cur1->val;
                cur1 = cur1->next;
            }
            if (cur2)
            {
                t += cur2->val;
                cur2 = cur2->next;
            }

            prev->next = new ListNode(t % 10);
            prev = prev->next;
            t /= 10;
        }

        prev = ret->next;
        delete ret;
        return prev;
    }

    ListNode *swapPairs(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *ret = new ListNode(0);
        ListNode *prev = ret, *cur = head, *next = cur->next, *nnext = next->next;

        while (cur && next)
        {
            prev->next = next;
            next->next = cur;
            cur->next = nnext;

            prev = cur;
            cur = nnext;

            if (cur)
                next = cur->next;
            if (next)
                nnext = next->next;
        }

        prev = ret->next;
        delete ret;
        return prev;
    }

    int m, n;
    bool vis[301][301];
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int numIslands(vector<vector<char>> &grid)
    {
        m = grid.size(), n = grid[0].size();
        int ret = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j] == '1' && !vis[i][j])
                {
                    ret++;
                    dfs(grid, i, j);
                }
        return ret;
    }

    void dfs(vector<vector<char>> &grid, int i, int j)
    {
        vis[i][j] = true;
        queue<pair<int, int>> q;
        q.push({i, j});
        while (q.size())
        {
            auto [a, b] = q.front();
            q.pop();
            for (int k = 0; k < 4; k++)
            {
                int x = a + dx[k], y = b + dy[k];
                if (x >= 0 && x < m && y >= 0 && y < n && grid[x][y] == '1' &&
                    !vis[x][y])
                {
                    q.push({x, y});
                    vis[x][y] = true;
                }
            }
        }
    }

    string convert(string s, int numRows)
    {
        if (numRows == 1)
            return s;
        int n = s.size(), d = 2 * n - 2;
        string ret;

        for (int i = 0; i < n; i += d)
            ret += s[i];
        for (int k = 1; k < numRows - 1; k++)
            for (int i = k, j = d - k; i < n || j < n; i += d, j += d)
            {
                if (i < n)
                    ret += s[i];
                if (j < n)
                    ret += s[j];
            }
        for (int i = numRows - 1; i < n; i += d)
            ret += s[i];

        return ret;
    }

    string longestCommonPrefix(vector<string> &strs)
    {
        for (int i = 0; i < strs[0].size(); i++)
            for (int j = 1; j < strs.size(); j++)
                if (strs[0][i] != strs[j][i])
                    return strs[0].substr(0, i);
        return "";
    }

    int uniquePaths(int m, int n)
    {
        vector<vector<int>> memo(m + 1, vector<int>(n + 1));
        return dfs(m, n, memo);
    }

    int dfs(int i, int j, vector<vector<int>> &memo)
    {
        if (memo[i][j] != 0)
            return memo[i][j];

        if (i == 0 || j == 0)
            return 0;
        if (i == 1 && j == 1)
        {
            memo[i][j] = 1;
            return 1;
        }

        memo[i][j] = dfs(i - 1, j, memo) + dfs(i, j - 1, memo);
        return memo[i][j];
    }

    int lengthOfLIS(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> memo(n);
        int ret = 0;
        for (int i = 0; i < n; i++)
            ret = max(ret, dfs(i, nums, memo));
        return ret;
    }

    int dfs(int pos, vector<int> &nums, vector<int> &memo)
    {
        if (memo[pos] != 0)
            return memo[pos];

        int ret = 1;
        for (int i = pos + 1; i < nums.size(); i++)
        {
            if (nums[i] > nums[pos])
                ret = max(ret, dfs(i, nums, memo) + 1);
        }

        memo[pos] = ret;
        return ret;
    }

    int memo[201][201];
    int getMoneyAmount(int n)
    {
        return dfs(1, n);
    }

    int dfs(int left, int right)
    {
        if (left >= right)
            return 0;
        if (memo[left][right] != 0)
            return memo[left][right];

        int ret = INT_MAX;
        for (int head = left; head <= right; head++)
        {
            int x = dfs(left, head - 1);
            int y = dfs(head + 1, right);

            ret = min(ret, head + max(x, y));
        }
        memo[left][right] = ret;
        return ret;
    }

    int m, n;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int memo[201][201];
    int longestIncreasingPath(vector<vector<int>> &matrix)
    {
        m = matrix.size(), n = matrix[0].size();
        int ret = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                ret = max(ret, dfs(matrix, i, j));
            }
        return ret;
    }

    int dfs(vector<vector<int>> &matrix, int i, int j)
    {
        if (memo[i][j] != 0)
            return memo[i][j];
        int ret = 1;
        for (int k = 0; k < 4; k++)
        {
            int x = i + dx[k], y = j + dy[k];
            if (x >= 0 && x < m && y >= 0 && y < n && matrix[x][y] > matrix[i][j])
            {
                ret = max(ret, dfs(matrix, x, y) + 1);
            }
        }
        memo[i][j] = ret;
        return ret;
    }
};