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
    bool wordBreak(string s, vector<string> &wordDict)
    {
        unordered_set<string> hash(wordDict.begin(), wordDict.end());

        int n = s.size();
        vector<bool> dp(n + 1);
        dp[0] = true; // 保证后续填表是正确的

        s = ' ' + s; // 使原始字符串的下标统一加1

        for (int i = 1; i <= n; i++)
        {
            for (int j = i; j >= 1; j--) // 最后一个单词的起始位置
            {
                if (dp[j - 1] && hash.count(s.substr(j, i - j + 1)))
                {
                    dp[i] = true;
                    break;
                }
            }
        }

        return dp[n];
    }

    int findSubstringInWraproundString(string s)
    {
        int n = s.size();
        vector<int> dp(n, 1);

        for (int i = 1; i < n; i++)
        {
            if (s[i - 1] + 1 == s[i] || (s[i - 1] == 'z' && s[i] == 'a'))
                dp[i] += dp[i - 1];
        }

        int hash[26];
        for (int i = 0; i < n; i++)
            hash[s[i] - 'a'] = max(hash[s[i] - 'a'], dp[i]);

        int sum = 0;
        for (auto x : hash)
            sum += x;
        return sum;
    }

    // 1
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    void solve(vector<vector<char>> &board)
    {
        m = board.size(), n = board[0].size();

        for (int i = 0; i < m; i++)
        {
            if (board[i][0] == 'O')
                dfs(board, i, 0);
            if (board[i][n - 1] == 'O')
                dfs(board, i, n - 1);
        }
        for (int i = 0; i < n; i++)
        {
            if (board[0][i] == 'O')
                dfs(board, 0, i);
            if (board[m - 1][i] == 'O')
                dfs(board, m - 1, i);
        }

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (board[i][j] == 'O')
                    board[i][j] = 'X';
                else if (board[i][j] == '.')
                    board[i][j] = 'O';
            }
    }

    void dfs(vector<vector<char>> &board, int i, int j)
    {
        queue<pair<int, int>> q;
        q.push({i, j});
        board[i][j] = '.';

        while (q.size())
        {
            auto [a, b] = q.front();
            q.pop();
            for (int k = 0; k < 4; k++)
            {
                int x = a + dx[k], y = b + dy[k];
                if (x >= 0 && x < m && y >= 0 && y < n && board[x][y] == 'O')
                {
                    q.push({x, y});
                    board[x][y] = '.';
                }
            }
        }
    }

    // 2
    int sum = 0;
    int sumNumbers(TreeNode *root)
    {
        dfs(root, 0);
        return sum;
    }

    void dfs(TreeNode *root, int path)
    {
        path = path * 10 + root->val;

        if (root->left == nullptr && root->right == nullptr)
        {
            sum += path;
            return;
        }

        if (root->left)
            dfs(root->left, path);
        if (root->right)
            dfs(root->right, path);
    }

    // 3
    int memo[101][101];
    int uniquePaths(int m, int n)
    {
        return dfs(m, n);
    }

    int dfs(int m, int n)
    {
        if (m == 0 && n == 0)
            return 0;

        if (memo[m][n])
            return memo[m][n];

        if (m == 1 || n == 1)
        {
            memo[m][n] = 1;
            return 1;
        }

        memo[m][n] = dfs(m - 1, n) + dfs(m, n - 1);
        return memo[m][n];
    }

    // 4
    bool vis[9];
    vector<vector<int>> ret;
    vector<int> path;
    vector<vector<int>> permuteUnique(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        dfs(nums, 0);
        return ret;
    }

    void dfs(vector<int> &nums, int pos)
    {
        if (pos == nums.size())
        {
            ret.push_back(path);
            return;
        }

        for (int i = 0; i < nums.size(); i++)
        {
            if (vis[i] || (i != 0 && nums[i] == nums[i - 1] && vis[i - 1]))
                continue;
            vis[i] = true;
            path.push_back(nums[i]);
            dfs(nums, pos + 1);
            vis[i] = false;
            path.pop_back();
        }
    }

    // 5
    vector<int> searchRange(vector<int> &nums, int target)
    {
        int left = 0, right = nums.size() - 1;

        while (left < right)
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] < target)
                left = mid + 1;
            else
                right = mid;
        }

        if (nums[left] != target)
            return {-1, -1};

        int begin = left;
        left = 0, right = nums.size() - 1;

        while (left < right)
        {
            int mid = left + (right - left + 1) / 2;
            if (nums[mid] <= target)
                left = mid;
            else
                right = mid - 1;
        }

        return {begin, left};
    }

    // 6
    int K;
    bool check[101][101];
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int wardrobeFinishing(int m, int n, int cnt)
    {
        K = cnt;
        int ret = 1;

        queue<pair<int, int>> q;
        q.push({0, 0});
        check[0][0] = true;

        while (q.size())
        {
            auto [a, b] = q.front();
            q.pop();
            for (int k = 0; k < 4; k++)
            {
                int x = a + dx[k], y = b + dy[k];
                if (x >= 0 && x < m && y >= 0 && y < n && !check[x][y] && Check(x, y))
                {
                    q.push({x, y});
                    ret++;
                    check[x][y] = true;
                }
            }
        }

        return ret;
    }

    bool Check(int i, int j)
    {
        int tmp = 0;
        while (i)
        {
            tmp += i % 10;
            i /= 10;
        }
        while (j)
        {
            tmp += j % 10;
            j /= 10;
        }

        return tmp <= K;
    }

    // 7
    int N;
    vector<vector<int>> res;
    vector<int> tmp;
    vector<vector<int>> combine(int n, int k)
    {
        N = n;
        DFS(1, k);
        return res;
    }

    void DFS(int pos, int k)
    {
        if (tmp.size() == k)
        {
            res.push_back(tmp);
            return;
        }

        for (int i = pos; i <= N; i++)
        {
            tmp.push_back(i);
            DFS(i + 1, k);
            tmp.pop_back();
        }
    }
};