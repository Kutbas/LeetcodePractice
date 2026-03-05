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
    // 1
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    bool vis[16][16];
    int ret = INT_MIN;
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

        return ret;
    }

    void dfs(vector<vector<int>> &grid, int i, int j, int sum)
    {
        ret = max(ret, sum);
        for (int k = 0; k < 4; k++)
        {
            int x = i + dx[k], y = j + dy[k];
            if (x >= 0 && x < m && y >= 0 && y < n && grid[x][y] && !vis[x][y])
            {
                vis[x][y] = true;
                dfs(grid, x, y, sum + grid[x][y]);
                vis[x][y] = false;
            }
        }
    }

    // 2
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    int step = 0, ret = 0;
    bool check[20][20];
    int uniquePathsIII(vector<vector<int>> &grid)
    {
        m = grid.size(), n = grid[0].size();
        int bx = 0, by = 0;

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == 1)
                {
                    bx = i;
                    by = j;
                }
                else if (grid[i][j] == 0)
                    step++;
            }
        step += 2;

        check[bx][by] = true;
        dfs(grid, bx, by, 0);

        return ret;
    }

    void dfs(vector<vector<int>> &grid, int i, int j, int count)
    {
        if (count == step)
        {
            ret++;
            return;
        }

        for (int k = 0; k < 4; k++)
        {
            int x = i + dx[k], y = j + dy[k];
            if (x >= 0 && x < m && y >= 0 && y < n && grid[x][y] != -1 && !check[x][y])
            {
                check[x][y] = true;
                dfs(grid, x, y, ++count);
                check[x][y] = false;
            }
        }
    }

    // 3
    ListNode *reverseList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *ret = reverseList(head->next->next);
        head->next->next = head;
        head->next = nullptr;

        return ret;
    }

    // 5
    string removeDuplicates(string s)
    {
        int n = s.size();
        string ret;
        for (int i = 0; i < n; i++)
        {
            while (ret.size() && ret.back() == s[i])
            {
                i++;
                ret.pop_back();
            }
            ret.push_back(s[i]);
        }

        return ret;
    }

    // 6
    vector<vector<int>> ret1;
    vector<int> path1;
    bool vis1[9];
    vector<vector<int>> permuteUnique(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        dfs(nums, 0);
        return ret1;
    }

    void dfs(vector<int> &nums, int pos)
    {
        if (pos == nums.size())
        {
            ret1.push_back(path1);
            return;
        }

        for (int i = 0; i < nums.size(); i++)
        {
            if (vis1[i] || (i != 0 && nums[i] == nums[i - 1] && !vis1[i - 1]))
                continue;

            path1.push_back(nums[i]);
            vis1[i] = true;
            dfs(nums, i + 1);
            vis1[i] = false;
            path1.pop_back();
        }
    }

    // 7
    unordered_map<char, unordered_set<char>> hash;
    unordered_map<char, int> in;
    bool check1 = false;
    string alienOrder(vector<string> &words)
    {
        for (auto word : words)
            for (auto ch : word)
                in[ch] = 0;

        for (int i = 0; i < words.size(); i++)
            for (int j = i + 1; j < words.size(); j++)
            {
                add(words[i], words[j]);
                if (check1)
                    return "";
            }

        queue<char> q;
        for (auto [a, b] : in)
            if (b == 0)
                q.push(a);

        string ret;
        while (q.size())
        {
            auto t = q.front();
            q.pop();
            ret += t;

            for (auto a : hash[t])
                if (--in[a] == 0)
                    q.push(a);
        }

        for (auto [a, b] : in)
            if (b)
                return "";

        return ret;
    }

    void add(string &s1, string &s2)
    {
        int n = min(s1.size(), s2.size());
        int i = 0;

        for (; i < n; i++)
        {
            if (s1[i] != s2[i])
            {
                char a = s1[i], b = s2[i]; // a->b
                if (!hash.count(a) || !hash[a].count(b))
                {
                    hash[a].insert(b);
                    in[b]++;
                }
                break;
            }
        }

        // abc ab
        if (i == s2.size() && i < s1.size())
            check1 = true;
    }
};

// 4
class KthLargest
{
public:
    KthLargest(int k, vector<int> &nums)
        : _k(k)
    {
        for (auto n : nums)
        {
            q.push(n);
            if (q.size() > _k)
                q.pop();
        }
    }

    int add(int val)
    {
    }

private:
    priority_queue<int, vector<int>, greater<int>> q;
    int _k;
};