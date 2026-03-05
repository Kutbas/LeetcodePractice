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
            for (int j = 1; j < strs.size(); j++)
                if (i == strs[j].size() || strs[0][i] != strs[j][i])
                    return strs[0].substr(0, i);
        return strs[0];
    }

    // 2
    int tribonacci(int n)
    {
        if (n == 0)
            return 0;
        if (n == 1 || n == 2)
            return 1;

        int a = 0, b = 1, c = 1, d = 0;
        for (int i = 3; i <= n; i++)
        {
            d = a + b + c;
            a = b;
            b = c;
            c = d;
        }

        return d;
    }

    // 3 二维数组前缀和

    // 4
    void reorderList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return;

        ListNode *slow = head, *fast = head;
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode *head2 = new ListNode(0);
        ListNode *cur = slow->next;
        slow->next = nullptr;

        while (cur)
        {
            ListNode *next = cur->next;
            cur->next = head2->next;
            head2->next = cur;
            cur = next;
        }

        ListNode *ret = new ListNode(0);
        ListNode *prev = ret, *cur1 = head, *cur2 = head2->next;
        while (cur1 || cur2)
        {
            if (cur1)
            {
                prev->next = cur1;
                prev = prev->next;
                cur1 = cur1->next;
            }
            if (cur2)
            {
                prev->next = cur2;
                prev = prev->next;
                cur2 = cur2->next;
            }
        }

        prev = ret->next;
        delete head2, cur, ret, cur1, cur2;
    }

    // 5
    int jump(vector<int> &nums)
    {
        int n = nums.size(), cur = 0, far = 0, ret = 0;

        for (int i = 0; i < n - 1; i++)
        {
            far = max(far, i + nums[i]);

            if (i == cur)
            {
                cur = far;
                ret++;

                if (cur >= n - 1)
                    break;
            }
        }

        return ret;
    }

    // 6
    int findNumberOfLIS(vector<int> &nums)
    {
        int n = nums.size();

        vector<int> longestLen(n, 1);
        vector<int> ways(n, 1);
        int globalLongestLen = 1;
        int globalWays = 1;

        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (nums[j] < nums[i])
                {
                    int newlen = longestLen[j] + 1;
                    if (newlen == longestLen[i])
                        ways[i] += ways[j];
                    else if (newlen > longestLen[i])
                    {
                        longestLen[i] = newlen;
                        ways[i] = ways[j];
                    }
                }
            }

            if (longestLen[i] == globalLongestLen)
                globalWays += ways[i];
            else if (longestLen[i] > globalLongestLen)
            {
                globalLongestLen = longestLen[i];
                globalWays = ways[i];
            }
        }

        return globalWays;
    }

    // 7
    int m, n;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    bool vis[16][16];
    int getMaximumGold(vector<vector<int>> &grid)
    {
        m = grid.size(), n = grid[0].size();
        int ret = 0;

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j])
                {
                    vis[i][j] = true;
                    ret = max(ret, grid[i][j] + dfs(grid, i, j));
                    vis[i][j] = false;
                }

        return ret;
    }

    int dfs(vector<vector<int>> &grid, int i, int j)
    {
        int ret = 0;
        for (int k = 0; k < 4; k++)
        {
            int x = i + dx[k], y = j + dy[k];
            if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && grid[x][y])
            {
                vis[x][y] = true;
                ret = max(ret, grid[x][y] + dfs(grid, x, y));
                vis[x][y] = false;
            }
        }
        return ret;
    }
};