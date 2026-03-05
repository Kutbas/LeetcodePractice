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
    bool check[7] = {0};
    vector<vector<int>> permute(vector<int> &nums)
    {
        dfs(nums);
        return ret;
    }

    void dfs(vector<int> &nums)
    {
        if (nums.size() == path.size())
        {
            ret.push_back(path);
            return;
        }

        for (int i = 0; i < nums.size(); i++)
        {
            if (!check[i])
            {
                path.push_back(nums[i]);
                check[i] = true;

                dfs(nums);

                path.pop_back();
                check[i] = false;
            }
        }
    }

    void hanota(vector<int> &A, vector<int> &B, vector<int> &C)
    {
        DFS(A, B, C, A.size());
    }

    void DFS(vector<int> &from, vector<int> &buffer, vector<int> &to, int n)
    {
        if (n == 1)
        {
            to.push_back(from.back());
            from.pop_back();
        }

        DFS(from, to, buffer, n - 1);
        to.push_back(from.back());
        from.pop_back();
        DFS(buffer, from, to, n - 1);
    }

    ListNode *swapPairs(ListNode *head)
    {
        if (head == nullptr && head->next == nullptr)
            return nullptr;

        ListNode *tmp = swapPairs(head->next->next);
        ListNode *ret = head->next;
        ret->next = head;
        head->next = tmp;

        return ret;
    }

    vector<vector<int>> ret;
    vector<int> path;
    bool check[7];
    vector<vector<int>> permute(vector<int> &nums)
    {
        dfs2(nums);
        return ret;
    }

    void dfs2(vector<int> &nums)
    {
        if (nums.size() == path.size())
        {
            ret.push_back(path);
            return;
        }

        for (int i = 0; i < nums.size(); i++)
        {
            if (!check[i])
            {
                path.push_back(nums[i]);
                check[i] = true;

                dfs2(nums);

                path.pop_back();
                check[i] = false;
            }
        }
    }

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    bool vis[201][201] = {0};
    void solve(vector<vector<char>> &board)
    {
        m = board.size(), n = board.size();
        for (int i = 0; i < m; i++)
        {
            if (board[i][0] == 'O')
                dfs3(board, i, 0);
            if (board[i][n - 1] == 'O')
                dfs3(board, i, n - 1);
        }

        for (int i = 0; i < n; i++)
        {
            if (board[0][i] == 'O')
                dfs3(board, 0, i);
            if (board[m - 1][i] == 'O')
                dfs3(board, m - 1, i);
        }

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (board[i][j] == '.')
                    board[i][j] = 'O';
                if (board[i][j] == 'O')
                    board[i][j] = 'X';
            }
    }

    void dfs3(vector<vector<char>> &board, int i, int j)
    {
        queue<pair<int, int>> q;
        q.push({i, j});
        vis[i][j] = true;
        board[i][j] = '.';

        while (q.size())
        {
            int sz = q.size();
            while (sz--)
            {
                auto [a, b] = q.front();
                q.pop();
                for (int k = 0; k < 4; k++)
                {
                    int x = a + dx[k], y = b + dy[k];
                    if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && board[x][y] == 'O')
                    {
                        q.push({x, y});
                        vis[x][y] = true;
                        board[x][y] = '.';
                    }
                }
            }
        }
    }

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    int maxDistance(vector<vector<int>> &grid)
    {
        m = grid.size(), n = grid[0].size();
        vector<vector<int>> dist(m, vector<int>(n, -1));
        queue<pair<int, int>> q;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j])
                {
                    dist[i][j] = 0;
                    q.push({i, j});
                }

        int ret = 0;
        while (q.size())
        {
            auto [a, b] = q.front();
            q.pop();
            for (int k = 0; k < 4; k++)
            {
                int x = a + dx[k], y = b + dy[k];
                if (x >= 0 && x < m && y >= 0 && y < n && dist[x][y] == -1)
                {
                    q.push({x, y});
                    dist[x][y] = dist[a][b] + 1;
                    ret = max(ret, dist[x][y]);
                }
            }
        }

        return ret;
    }

    int ladderLength(string beginWord, string endWord, vector<string> &wordList)
    {
        if (beginWord == endWord)
            return 1;
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

        return 0;
    }

    vector<string> ret2;
    vector<string> binaryTreePaths(TreeNode *root)
    {
        string path;
        if (root == nullptr)
            return ret2;
        dfs4(root, path);
        return ret2;
    }

    void dfs4(TreeNode *root, string path)
    {
        path += to_string(root->val);

        if (root->left == nullptr && root->right == nullptr)
        {
            ret2.push_back(path);
            return;
        }

        path += "->";
        if (root->left)
            dfs4(root->left, path);
        if (root->right)
            dfs4(root->right, path);
    }

    vector<vector<int>> ret;
    vector<int> path;
    vector<vector<int>> subsets(vector<int> &nums)
    {
        dfs(nums, 0);
        return ret;
    }

    void dfs(vector<int> &nums, int pos)
    {
        ret.push_back(path);

        for (int i = pos; i < nums.size(); i++)
        {
            path.push_back(nums[i]);
            dfs(nums, i + 1);
            path.pop_back();
        }
    }
};