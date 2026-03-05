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
    bool isUnique(string astr)
    {
        if (astr.size() > 26)
            return false;

        int bitMap = 0;
        for (char ch : astr)
        {
            int i = ch - 'a';
            if (bitMap & (1 << i) == 1)
                return false;
            bitMap |= (1 << i);
        }
        return true;
    }

    // 2
    int mySqrt(int x)
    {
        int left = 0, right = x;
        while (left < right)
        {
            int mid = left + (right - left + 1) / 2;
            if (mid * mid <= x)
                left = mid;
            else
                right = mid - 1;
        }
        return left;
    }

    // 3
    int cnt, ret = 0;
    int kthSmallest(TreeNode *root, int k)
    {
        cnt = k;
        dfs(root);
        return ret;
    }

    void dfs(TreeNode *root)
    {
        if (root->left)
            dfs(root->left);

        if (--cnt == 0)
        {
            ret = root->val;
            return;
        }

        if (root->right)
            dfs(root->right);
    }

    // 4
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
                    if (nums[i] > ret[mid])
                        left = mid + 1;
                    else
                        right = mid;
                }
                ret[left] = nums[i];
            }
        }

        return ret.size();
    }

    // 5
    vector<string> Ret;
    string Path;
    int left = 0, right = 0, N;
    vector<string> generateParenthesis(int n)
    {
        N = n;
        dfs();
        return Ret;
    }

    void dfs()
    {
        if (right == N)
        {
            Ret.push_back(Path);
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

    // 6
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    bool vis[101][101];
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
                    if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && maze[x][y] == '.')
                    {
                        if (x == 0 || y == 0 || x == m - 1 || y == n - 1)
                            return ret;
                        q.push({x, y});
                        vis[x][y] = true;
                    }
                }
            }
        }

        return -1;
    }
};