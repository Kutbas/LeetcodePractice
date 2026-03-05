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
    int tar;
    vector<vector<int>> combinationSum(vector<int> &candidates, int target)
    {
        tar = target;
        dfs(candidates, 0, 0);
        return ret;
    }

    void dfs(vector<int> &nums, int pos, int sum)
    {
        if (sum == tar)
        {
            ret.push_back(path);
            return;
        }

        if (sum > tar || pos == nums.size())
            return;

        for (int i = 0; i < nums.size(); i++)
        {
            path.push_back(nums[i]);
            dfs(nums, pos + 1, sum + nums[i]);
            path.pop_back();
        }
    }

    ListNode *reverseList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *ret = reverseList(head->next);
        head->next->next = head;
        head->next = ret;
        return ret;
    }

    struct cmp
    {
        bool operator()(const ListNode *l1, const ListNode *l2)
        {
            return l1->val > l2->val;
        }
    };

    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        priority_queue<ListNode *, vector<ListNode *>, cmp> q;
        for (auto &list : lists)
            if (list)
                q.push(list);

        ListNode *head = new ListNode(0);
        ListNode *prev = head;

        while (q.size())
        {
            auto t = q.top();
            q.pop();
            prev->next = t;
            prev = prev->next;

            if (t->next)
                q.push(t->next);
        }

        prev = head->next;
        delete head;
        return prev;
    }

    int ret1 = 0;
    int sumNumbers(TreeNode *root)
    {
        dfs(root, 0);
        return ret1;
    }

    void dfs(TreeNode *root, int sum)
    {
        sum = sum * 10 + root->val;
        if (root->left == nullptr && root->right == nullptr)
        {
            ret1 += sum;
            return;
        }

        if (root->left)
            dfs(root->left, sum);
        if (root->right)
            dfs(root->right, sum);
    }

    int sum = 0, path1 = 0;
    int subsetXORSum(vector<int> &nums)
    {
        dfs(nums, 0);
        return sum;
    }

    void dfs(vector<int> &nums, int pos)
    {
        sum += path1;

        for (int i = pos; i < nums.size(); i++)
        {
            path1 ^= nums[i];
            dfs(nums, i + 1);
            path1 ^= nums[i];
        }
    }

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

    bool vis[16][16];
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n, ret2 = 0;
    int getMaximumGold(vector<vector<int>> &grid)
    {
        m = grid.size(), n = grid[0].size();
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j])
                {
                    vis[i][j] = true;
                    dfs(grid, i, j, grid[i][j]);
                    vis[i][j] = false;
                }
        return ret2;
    }

    void dfs(vector<vector<int>> &grid, int i, int j, int path)
    {
        ret2 = max(ret2, path);
        for (int k = 0; k < 4; k++)
        {
            int x = i + dx[k], y = j + dy[k];
            if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && grid[x][y])
            {
                vis[x][y] = true;
                dfs(grid, x, y, path + grid[x][y]);
                vis[x][y] = false;
            }
        }
    }
};