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
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    int memo[101][101];
    bool vis[101][101];
    int getMaximumGold(vector<vector<int>> &grid)
    {
        m = grid.size(), n = grid[0].size();
        int ret = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j])
                {
                    vis[i][j] = true;
                    ret = max(ret, dfs(grid, i, j, grid[i][j]));
                    vis[i][j] = false;
                }

        return ret;
    }

    int dfs(vector<vector<int>> &grid, int i, int j, int sum)
    {

        int ret = sum;

        for (int k = 0; k < 4; k++)
        {
            int x = i + dx[k], y = j + dy[k];
            if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && grid[x][y])
            {
                vis[x][y] = true;
                ret = max(ret, dfs(grid, x, y, sum + grid[x][y]));
                vis[x][y] = false;
            }
        }

        return ret;
    }

    // 2
    string removeDuplicates(string s)
    {
        string ret;
        for (char ch : s)
        {
            if (ret.size() && ret.back() == ch)
                ret.pop_back();
            else
                ret += ch;
        }

        return ret;
    }

    // 3
    string longestCommonPrefix(vector<string> &strs)
    {
        for (int i = 0; i < strs[0].size(); i++)
            for (int j = 1; j < strs.size(); j++)
                if (i == strs[j].size() || strs[0][i] != strs[j][i])
                    return strs[0].substr(0, i);
        return strs[0];
    }

    // 4
    int minNumberOfFrogs(string croakOfFrogs)
    {
        string tmp = "croak";
        int n = tmp.size();
        unordered_map<char, int> index;
        int hash[5] = {0};

        for (int i = 0; i < n; i++)
            index[tmp[i]] = i;

        for (char ch : croakOfFrogs)
        {
            if (ch == 'c')
            {
                if (hash[n - 1])
                    hash[n - 1]--;
                hash[0]++;
            }
            else
            {
                int prevIndex = index[ch] - 1;
                if (hash[prevIndex] == 0)
                    return -1;
                hash[prevIndex]--;
                hash[index[ch]]++;
            }
        }

        for (int i = 0; i < n - 1; i++)
            if (hash[i])
                return -1;
        return hash[n - 1];
    }

    // 5
    void reorderList(ListNode *head)
    {
        ListNode *slow = head, *fast = head;
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode *cur = slow->next;
        slow->next = nullptr;

        ListNode *newhead = new ListNode(0);
        ListNode *prev = newhead;

        while (cur)
        {
            ListNode *next = cur->next;
            cur->next = prev->next;
            prev->next = cur;
            cur = next;
        }

        ListNode *ret = new ListNode(0);
        prev = ret;

        ListNode *cur1 = head, *cur2 = newhead->next;

        while (cur1)
        {
            prev->next = cur1;
            prev = prev->next;
            cur1 = cur1->next;

            if (cur2)
            {
                prev->next = cur2;
                prev = prev->next;
                cur2 = cur2->next;
            }
        }

        prev = ret->next;
        delete ret;
    }

    // 6
    vector<vector<int>> ret;
    vector<int> path;
    bool Vis[9];
    vector<vector<int>> permuteUnique(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        dfs(nums, 0);
        return ret;
    }

    void dfs(vector<int> &nums, int pos)
    {
        if (path.size() == nums.size())
        {
            ret.push_back(path);
            return;
        }

        for (int i = 0; i < nums.size(); i++)
        {
            if (Vis[i] || (i != 0 && nums[i] == nums[i - 1] && Vis[i - 1]))
                continue;
            Vis[i] = true;
            path.push_back(nums[i]);
            dfs(nums, pos + 1);
            path.pop_back();
            Vis[i] = false;
        }
    }

    int maxProfit(vector<int> &prices, int fee)
    {
        int n = prices.size();
        vector<int> f(n);

        auto g = f;
        f[0] = -prices[0];
        for (int i = 1; i < n; i++)
        {
            f[i] = max(f[i - 1], g[i - 1] - prices[i]);
            g[i] = max(g[i - 1], f[i - 1] + prices[i] - fee);
        }

        return g[n - 1];
    }
};