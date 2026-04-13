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
    int largestSumAfterKNegations(vector<int> &nums, int k)
    {
        int n = nums.size(), minElem = INT_MAX, count = 0;

        for (auto num : nums)
        {
            if (num < 0)
            {
                count++;
            }
            minElem = min(minElem, abs(num));
        }

        int ret = 0;
        if (count > k)
        {
            sort(nums.begin(), nums.end());
            for (int i = 0; i < k; i++)
                ret += abs(nums[i]);
            for (int i = k; i < n; i++)
                ret += nums[i];
        }
        else
        {
            for (auto num : nums)
                ret += abs(num);

            if ((k - count) % 2 == 1)
                ret -= 2 * minElem;
        }

        return ret;
    }

    // 2
    int m, n;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int maxDistance(vector<vector<int>> &grid)
    {
        m = grid.size(), n = grid[0].size();
        vector<vector<int>> dist(m, vector<int>(n, -1));

        queue<pair<int, int>> q;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j] == 1)
                {
                    dist[i][j] = 0;
                    q.push({i, j});
                }

        int ret = -1;
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
                    if (x >= 0 && x < m && y >= 0 && y < n && dist[x][y] == -1)
                    {
                        dist[x][y] = dist[a][b] + 1;
                        ret = max(ret, dist[x][y]);
                        q.push({x, y});
                    }
                }
            }
        }

        return ret;
    }

    // 3
    int firstUniqChar(string s)
    {
        int hash[128] = {0};
        for (char ch : s)
            hash[ch]++;

        for (int i = 0; i < s.size(); i++)
            if (hash[s[i]] == 1)
                return i;

        return -1;
    }

    // 4
    vector<vector<int>> ret;
    vector<int> path;
    int N, K;
    bool vis[20] = {0};
    vector<vector<int>> combine(int n, int k)
    {
        N = n, K = k;
        dfs(1);
        return ret;
    }

    void dfs(int pos)
    {
        if (path.size() == K)
        {
            ret.push_back(path);
            return;
        }

        for (int i = pos; i <= N; i++)
        {
            if (!vis[i])
            {
                vis[i] = true;
                path.push_back(i);
                dfs(i + 1);
                path.pop_back();
                vis[i] = false;
            }
        }
    }

    // 5
    int countSubstrings(string s)
    {
        int n = s.size(), ret = 0;
        vector<vector<bool>> dp(n, vector<bool>(n));
        for (int i = n - 1; i >= 0; i--)
            for (int j = i; j < n; j++)
            {
                if (s[i] == s[j])
                    dp[i][j] = j - i + 1 > 3 ? dp[i + 1][j - 1] : true;

                if (dp[i][j])
                    ret++;
            }

        return ret;
    }

    // 6
    int massage(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 0)
            return 0;
        vector<int> f(n), g(n);
        f[0] = nums[0];

        for (int i = 1; i < n; i++)
        {
            f[i] = g[i - 1] + nums[i];
            g[i] = max(f[i - 1], g[i - 1]);
        }

        return max(f[n - 1], g[n - 1]);
    }

    // 7
    int lengthOfLIS(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> ret;
        ret.push_back(nums[0]);

        for (int i = 1; i < n; i++)
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

    // 8
    int removeDuplicates(vector<int> &nums)
    {
        int n = nums.size(), slow = 1, fast = 1;
        while (fast < n)
        {
            if (nums[fast - 1] != nums[fast])
                nums[slow++] = nums[fast];
            fast++;
        }
        return slow;
    }
};