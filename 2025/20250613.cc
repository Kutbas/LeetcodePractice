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
    int lengthOfLongestSubstring(string s)
    {
        int hash[128] = {0};
        int begin = -1, maxlen = 1;
        for (int left = 0, right = 0; right < s.size(); right++)
        {
            char in = s[right];
            ++hash[in];
            while (hash[in] >= 2)
            {
                char out = s[left++];
                --hash[out];
            }
            if (right - left + 1 > maxlen)
            {
                maxlen = right - left + 1;
                begin = left;
            }
        }
        return maxlen;
    }

    int singleNumber(vector<int> &nums)
    {
        int ret = 0;

        for (int i = 0; i < 32; i++)
        {
            int tmp = 0;
            for (auto n : nums)
                if ((n >> i) & 1 == 1)
                    tmp++;
            tmp %= 3;
            if (tmp)
                ret |= (1 << i);
        }

        return ret;
    }

    int sumNumbers(TreeNode *root)
    {
        return dfs(root, 0);
    }

    int dfs(TreeNode *root, int presum)
    {
        presum = presum * 10 + root->val;

        if (root->left == nullptr && root->right == nullptr)
            return presum;

        int ret = 0;
        if (root->left)
            ret += dfs(root->left, presum);
        if (root->right)
            ret += dfs(root->right, presum);
        return ret;
    }

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    bool vis[501][501] = {0};
    int m, n;
    int numEnclaves(vector<vector<int>> &grid)
    {
        m = grid.size(), n = grid[0].size();
        for (int i = 0; i < m; i++)
        {
            if (grid[i][0])
                dfs(grid, i, 0);
            if (grid[i][n - 1])
                dfs(grid, i, n - 1);
        }

        for (int i = 0; i < n; i++)
        {
            if (grid[0][i])
                dfs(grid, 0, i);
            if (grid[m - 1][i])
                dfs(grid, m - 1, i);
        }

        int ret = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j] && !vis[i][j])
                    ret++;
        return ret;
    }

    void dfs(vector<vector<int>> &grid, int i, int j)
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
                if (x >= 0 && x < m && y >= 0 && y < n && grid[x][y] && !vis[x][y])
                {
                    q.push({x, y});
                    vis[x][y] = true;
                }
            }
        }
    }

    int sumNumbers(TreeNode *root)
    {
        return DFS(root, 0);
    }

    int DFS(TreeNode *root, int presum)
    {
        presum = presum * 10 + root->val;

        if (root->left == nullptr && root->right == nullptr)
            return presum;

        int ret = 0;
        if (root->left)
            ret += DFS(root->left, presum);
        if (root->right)
            ret += DFS(root->right, presum);
        return ret;
    }

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    bool vis[101][101] = {0};
    int nearestExit(vector<vector<char>> &maze, vector<int> &entrance)
    {
        m = maze.size(), n = maze[0].size();
        queue<pair<int, int>> q;
        q.push({entrance[0], entrance[1]});
        vis[entrance[0]][entrance[1]] = true;

        int ret = 0;
        while (q.size())
        {
            ret++;
            int sz = q.size();
            while (sz--)
            {
                auto [a, b] = q.front();
                q.pop();
                for (int k = 0; k < 4; k++)
                {
                    int x = a + dx[k], y = b + dy[k];
                    if (x >= 0 && x < m && y >= 0 && y < n && maze[x][y] == '.' && !vis[x][y])
                    {
                        if (x == 0 || x == m - 1 || y == 0 || y == n - 1)
                            return ret;
                        q.push({x, y});
                        vis[x][y] = true;
                    }
                }
            }
        }
        return -1;
    }

    int sumNumbers(TreeNode *root)
    {
        return sum(root, 0);
    }

    int sum(TreeNode *root, int presum)
    {
        presum = presum * 10 + root->val;

        if (root->left == nullptr && root->right == nullptr)
            return presum;

        int ret = 0;
        if (root->left)
            ret += sum(root->left, presum);
        if (root->right)
            ret += sum(root->right, presum);
        return ret;
    }

    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
    {
        if (l1 == nullptr)
            return l2;
        if (l2 == nullptr)
            return l1;

        if (l1->val <= l2->val)
        {
            l1->next = mergeTwoLists(l1->next, l2);
            return l1->next;
        }
        else
        {
            l2->next = mergeTwoLists(l1, l2->next);
            return l2->next;
        }
    }

    long prev = LONG_MIN;
    bool isValidBST(TreeNode *root)
    {
        if (root == nullptr)
            return true;

        // 中序遍历
        bool left = isValidBST(root->left);
        // 剪枝
        if (!left)
            return false;
        bool cur = false;
        if (root->val > prev)
            cur = true;

        if (!cur)
            return false;
        prev = root->val;
        bool right = isValidBST(root->right);
        return left && right && cur;
    }
};