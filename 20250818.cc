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
    int brokenCalc(int startValue, int target)
    {
        int ret = 0;

        while (target > startValue)
        {
            if (target % 2 == 0)
                target /= 2;
            else
                target += 1;
            ret++;
        }

        return ret + startValue - target;
    }

    // 1
    int ret = 0;
    int sumNumbers(TreeNode *root)
    {
        dfs(root, 0);
        return ret;
    }

    void dfs(TreeNode *root, int sum)
    {
        sum = sum * 10 + root->val;

        if (root->left == nullptr && root->right == nullptr)
        {
            ret += sum;
            return;
        }

        if (root->left)
            dfs(root->left, sum);
        if (root->right)
            dfs(root->right, sum);
    }

    // 2
    bool Row[10], Col[10], Dig1[20], Dig2[20];
    vector<vector<string>> Ret;
    vector<string> path;
    int N;
    vector<vector<string>> solveNQueens(int n)
    {
        N = n;
        path.resize(n);
        for (int i = 0; i < n; i++)
            path[i].append(n, '.');

        dfs(0);

        return Ret;
    }

    bool dfs(int row)
    {
        if (row == N)
        {
            Ret.push_back(path);
            return true;
        }

        for (int col = 0; col < N; col++)
        {
            if (!Col[col] && !Dig1[row + col] && !Dig2[row - col + N])
            {
                Col[col] = Dig1[row + col] = Dig2[row - col + N] = true;
                path[row][col] = 'Q';
                if (!dfs(row + 1))
                {
                    Col[col] = Dig1[row + col] = Dig2[row - col + N] = false;
                    path[row][col] = '.';
                }
            }
        }

        return false;
    }

    // 3
    bool check[101][101];
    int K, res = 0, M, N;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};

    int wardrobeFinishing(int m, int n, int cnt)
    {
        K = cnt;

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
                    res++;
                    check[x][y] = true;
                    q.push({x, y});
                }
            }
        }
        return res;
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

    // 4
    bool vis[9];
    vector<vector<int>> ret1;
    vector<int> path1;
    vector<vector<int>> permuteUnique(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        dfs(nums);
        return ret1;
    }

    void dfs(vector<int> &nums)
    {
        if (path1.size() == nums.size())
        {
            ret1.push_back(path1);
            return;
        }

        for (int i = 0; i < nums.size(); i++)
        {
            if (vis[i] || (i != 0 && nums[i] == nums[i - 1] && vis[i - 1]))
                continue;
            else
            {
                vis[i] = true;
                path1.push_back(nums[i]);
                dfs(nums);
                vis[i] = false;
                path1.pop_back();
            }
        }
    }

    // 5
    vector<vector<int>> ret2;
    vector<int> path2;
    int K, N;
    bool vis2[20];
    vector<vector<int>> combine(int n, int k)
    {
        N = n, K = k;
        DFS();
        return ret2;
    }

    void DFS()
    {
        if (path2.size() == K)
        {
            ret2.push_back(path2);
            return;
        }

        for (int i = 1; i <= N; i++)
        {
            if (!vis2[i])
            {
                vis2[i] = true;
                path2.push_back(i);
                DFS();
                path2.pop_back();
                vis2[i] = false;
            }
        }
    }

    // 6
    vector<vector<int>> ret3;
    vector<int> path3;
    vector<vector<int>> subsets(vector<int> &nums)
    {
        dfs(nums, 0);
        return ret3;
    }

    void dfs(vector<int> &nums, int pos)
    {
        ret3.push_back(path3);

        if (pos == nums.size())
        {
            return;
        }

        for (int i = pos; i < nums.size(); i++)
        {
            path3.push_back(nums[i]);
            dfs(nums, i + 1);
            path3.pop_back();
        }
    }
};