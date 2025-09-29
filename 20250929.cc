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
    int maxProduct(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> f(n + 1), g(n + 1);
        f[0] = g[0] = 1;

        int ret = INT_MIN;
        for (int i = 1; i <= n; i++)
        {
            int x = nums[i - 1], y = f[i - 1] * nums[i - 1], z = g[i - 1] * nums[i - 1];
            f[i] = max(x, max(y, z));
            g[i] = min(x, min(y, z));
            ret = max(ret, f[i]);
        }

        return ret;
    }

    int m, n;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    bool vis[7][7];
    bool exist(vector<vector<char>> &board, string word)
    {
        m = board.size(), n = board[0].size();
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (board[i][j] == word[0])
                {
                    vis[i][j] = true;
                    if (dfs(board, word, i, j, 1))
                        return true;
                    vis[i][j] = false;
                }

        return false;
    }

    bool dfs(vector<vector<char>> &board, string &word, int i, int j, int pos)
    {
        if (pos == word.size())
            return true;

        for (int k = 0; k < 4; k++)
        {
            int x = i + dx[k], y = j + dy[k];
            if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && board[x][y] == word[pos])
            {
                vis[x][y] = true;
                if (dfs(board, word, x, y, pos + 1))
                    return true;
                vis[x][y] = false;
            }
        }

        return false;
    }

    // 2
    int lengthOfLIS(vector<int> &nums)
    {
        vector<int> ret;
        ret.push_back(nums[0]);

        for (int i = 1; i < nums.size(); i++)
        {
            if (nums[i] > ret.back())
                ret.push_back(nums[i]);
            else
            {
                int left = 0, right = ret.size() - 1;
                while (left < right)
                {
                    int mid = left + (right - left) / 2;
                    if (nums[i] < ret[mid])
                        left = mid + 1;
                    else
                        right = mid;
                }
                ret[left] = nums[i];
            }
        }

        return ret.size();
    }

    // 3
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

    // 4
    void hanota(vector<int> &A, vector<int> &B, vector<int> &C)
    {
        dfs(A, B, C, A.size());
    }

    void dfs(vector<int> &from, vector<int> &buffer, vector<int> &to, int n)
    {
        if (n == 1)
        {
            to.push_back(from.back());
            from.pop_back();
        }

        dfs(from, to, buffer, n - 1);
        to.push_back(from.back());
        from.pop_back();
        dfs(buffer, from, to, n - 1);
    }

    // 5
    vector<int> twoSum(vector<int> &nums, int target)
    {
        unordered_map<int, int> hash;
        for (int i = 0; i < nums.size(); i++)
        {
            int x = target - nums[i];
            if (hash.count(x))
                return {i, hash[x]};
            hash[nums[i]] = i;
        }
        return {-1, -1};
    }

    int getMaxLen(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> f(n + 1);
        auto g = f;

        int ret = INT_MIN;
        for (int i = 1; i <= n; i++)
        {
            if (nums[i - 1] > 0)
            {
                f[i] = f[i - 1] + 1;
                g[i] = g[i - 1] == 0 ? 0 : g[i - 1] + 1;
            }
            else if (nums[i - 1] < 0)
            {
                f[i] = g[i - 1] == 0 ? 0 : g[i - 1] + 1;
                g[i] = f[i - 1] + 1;
            }
            ret = max(ret, f[i]);
        }

        return ret;
    }

    // 6
    vector<int> largestValues(TreeNode *root)
    {
        vector<int> ret;
        if (root == nullptr)
            return ret;

        queue<TreeNode *> q;
        q.push(root);
        while (q.size())
        {
            int sz = q.size();
            int tmp = INT_MIN;
            while (sz--)
            {
                auto t = q.front();
                q.pop();
                tmp = max(tmp, t->val);
                if (t->left)
                    q.push(t->left);
                if (t->right)
                    q.push(t->right);
            }
            ret.push_back(tmp);
        }

        return ret;
    }
};