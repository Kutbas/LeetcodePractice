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
    vector<vector<int>> ret;
    vector<int> path;
    bool vis[9];
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
            if (vis[i] || (i != 0 && nums[i] == nums[i - 1] && !vis[i - 1]))
                continue;
            vis[i] = true;
            path.push_back(nums[i]);
            dfs(nums, pos + 1);
            path.pop_back();
            vis[i] = false;
        }
    }

    // 2
    int findSubstringInWraproundString(string s)
    {
        int n = s.size();

        vector<int> dp(n, 1);
        for (int i = 1; i < n; i++)
            if (s[i - 1] + 1 == s[i] || (s[i - 1] == 'z' && s[i] == 'a'))
                dp[i] += dp[i - 1];

        int hash[26] = {0};
        for (int i = 0; i < n; i++)
        {
            int index = s[i] - 'a';
            hash[index] = max(hash[index], dp[i]);
        }

        int sum = 0;
        for (int i = 0; i < 26; i++)
            sum += hash[i];

        return sum;
    }

    // 3
    int memo[201][201];
    int getMoneyAmount(int n) { return dfs(1, n); }
    int dfs(int m, int n)
    {
        if (m >= n)
            return 0;

        if (memo[m][n])
            return memo[m][n];

        int ret = INT_MAX;
        for (int head = m; head <= n; head++)
        {
            int tmp1 = dfs(m, head - 1);
            int tmp2 = dfs(head + 1, n);

            ret = min(ret, head + max(tmp1, tmp2));
        }

        memo[m][n] = ret;
        return ret;
    }

    // 4
    bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
    {
        vector<vector<int>> edges(numCourses);
        vector<int> in(numCourses);
        for (auto &e : prerequisites)
        {
            int a = e[0], b = e[1]; // b->a;
            edges[b].push_back(a);
            in[a]++;
        }

        queue<int> q;
        for (int i = 0; i < numCourses; i++)
            if (in[i] == 0)
                q.push(i);
        while (q.size())
        {
            auto t = q.front();
            q.pop();

            for (auto a : edges[t])
                if (--in[a] == 0)
                    q.push(a);
        }

        for (int i = 0; i < numCourses; i++)
            if (in[i])
                return false;
        return true;
    }

    // 5
    int minCostClimbingStairs(vector<int> &cost)
    {
        int n = cost.size();
        vector<int> dp(n + 1);

        for (int i = 2; i <= n; i++)
            dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);

        return dp[n];
    }

    // 6
    string longestCommonPrefix(vector<string> &strs)
    {
        for (int i = 0; i < strs[0].size(); i++)
            for (int j = 1; j < strs.size(); j++)
                if (i == strs[j].size() || strs[0][i] != strs[j][i])
                    return strs[0].substr(0, i);
        return strs[0];
    }

    // 7
    int maxEnvelopes(vector<vector<int>> &e)
    {
        int n = e.size();
        sort(e.begin(), e.end(), [&](const vector<int> &v1, const vector<int> &v2)
             { return v1[0] != v2[0] ? v1[0] < v2[0] : v1[1] > v2[1]; });

        vector<int> ret;
        ret.push_back(e[0][1]);
        for (int i = 1; i < n; i++)
        {
            if (e[i][1] > ret.back())
                ret.push_back(e[i][1]);
            else
            {
                int left = 0, right = ret.size() - 1;
                while (left < right)
                {
                    int mid = left + (right - left) / 2;
                    if (e[i][1] > ret[mid])
                        left = mid + 1;
                    else
                        right = mid;
                }
                ret[left] = e[i][1];
            }
        }

        return ret.size();
    }
};