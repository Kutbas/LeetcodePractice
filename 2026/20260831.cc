#include <mutex>
#include <vector>
#include <algorithm>
#include <climits>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <iostream>
#include <sstream>
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
    int m, n, count = 0, ret = 0;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    bool vis[21][21] = {0};
    int uniquePathsIII(vector<vector<int>> &grid)
    {
        m = grid.size(), n = grid[0].size();
        int bx = -1, by = -1;

        count += 2;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == 0)
                    count++;
                else if (grid[i][j] == 1)
                    bx = i, by = j;
            }

        vis[bx][by] = true;
        bfs(grid, bx, by, 1);

        return ret;
    }

    void bfs(vector<vector<int>> &grid, int i, int j, int step)
    {
        if (grid[i][j] == 2)
        {
            if (step == count)
                ret++;
            return;
        }

        for (int k = 0; k < 4; k++)
        {
            int x = i + dx[k], y = j + dy[k];
            if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && grid[x][y] != -1)
            {
                vis[x][y] = true;
                bfs(grid, x, y, step + 1);
                vis[x][y] = false;
            }
        }
    }

    // 2
    int K;
    bool vis[101][101] = {0};
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int wardrobeFinishing(int m, int n, int cnt)
    {
        K = cnt;

        int ret = 1;
        queue<pair<int, int>> q;
        vis[0][0] = true;
        q.push({0, 0});

        while (q.size())
        {
            auto [a, b] = q.front();
            q.pop();
            for (int k = 0; k < 4; k++)
            {
                int x = a + dx[k], y = b + dy[k];
                if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && Check(x, y))
                {
                    ret++;
                    vis[x][y] = true;
                    q.push({x, y});
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

    // 3
    vector<vector<int>> merge(vector<vector<int>> &intervals)
    {
        sort(intervals.begin(), intervals.end());
        int n = intervals.size(), left = intervals[0][0], right = intervals[0][1];
        vector<vector<int>> ret;

        for (int i = 1; i < n; i++)
        {
            int a = intervals[i][0], b = intervals[i][1];
            if (a <= right)
                right = max(right, b);
            else
            {
                ret.push_back({left, right});
                left = a, right = b;
            }
        }

        ret.push_back({left, right});

        return ret;
    }

    // 4
    int maxProfit(int k, vector<int> &prices)
    {
        const int INF = 0x3f3f3f;
        int n = prices.size();
        k = min(k, n / 2);
        vector<vector<int>> f(n, vector<int>(k + 1, -INF));
        auto g = f;
        f[0][0] = -prices[0];
        g[0][0] = 0;

        for (int i = 1; i < n; i++)
            for (int j = 0; j <= k; j++)
            {
                f[i][j] = max(f[i - 1][j], g[i - 1][j] - prices[i]);
                g[i][j] = g[i - 1][j];
                if (j >= 1)
                    g[i][j] = max(g[i][j], f[i - 1][j - 1] + prices[i]);
            }

        int ret = -INF;
        for (int i = 0; i <= k; i++)
            ret = max(ret, g[n - 1][i]);

        return ret;
    }

    // 5
    int numberOfArithmeticSlices(vector<int> &nums)
    {
        int n = nums.size();
        if (n < 3)
            return 0;

        int sum = 0, prev = 0;
        for (int i = 2; i < n; i++)
        {
            if (nums[i - 1] - nums[i] == nums[i - 2] - nums[i - 1])
            {
                prev += 1;
                sum += prev;
            }
            else
                prev = 0;
        }

        return sum;
    }

    // 6
    int findSubstringInWraproundString(string s)
    {
        int n = s.size();
        vector<int> dp(n, 1);
        // s=" "+s;

        for (int i = 1; i < n; i++)
        {
            if (s[i - 1] + 1 == s[i] || (s[i - 1] == 'z' && s[i] == 'a'))
                dp[i] += dp[i - 1];
        }

        int hash[26] = {0};
        for (int i = 0; i < n; i++)
        {
            int index = s[i] - 'a';
            hash[index] = max(hash[index], dp[i]);
        }

        int sum = 0;
        for (auto n : hash)
            sum += n;

        return sum;
    }

    // 7
    int longestSubsequence(vector<int> &arr, int difference)
    {
        int n = arr.size(), ret = 0;
        unordered_map<int, int> hash;
        hash[arr[0]] = 1;

        for (int i = 1; i < n; i++)
        {
            hash[arr[i]] = hash[arr[i] - difference] + 1;
            ret = max(ret, hash[arr[i]]);
        }

        return ret;
    }

    // 8
    class MyStack
    {
    private:
        queue<int> q;

    public:
        MyStack()
        {
        }

        void push(int x)
        {
            int n = q.size();
            q.push(x);
            for (int i = 0; i < n; i++)
            {
                q.push(q.front());
                q.pop();
            }
        }

        int pop()
        {
            int r = q.front();
            q.pop();
            return r;
        }

        int top()
        {
            int r = q.front();
            return r;
        }

        bool empty()
        {
            return q.empty();
        }
    };
};