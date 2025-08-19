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
    vector<vector<int>> merge(vector<vector<int>> &intervals)
    {
        // 先按照左端点排序
        sort(intervals.begin(), intervals.end());

        // 合并区间
        int left = intervals[0][0], right = intervals[0][1];
        vector<vector<int>> ret;

        for (int i = 1; i < intervals.size(); i++)
        {
            int a = intervals[i][0], b = intervals[i][1];
            // 有重叠部分
            if (a <= right)
                // 求并集
                right = max(right, b);
            else
            {
                ret.push_back({left, right});
                left = a;
                right = b;
            }
        }

        // 添加最后一个区间
        ret.push_back({left, right});
        return ret;
    }

    // 1
    int N, ret = 0;
    bool vis[16];
    int countArrangement(int n)
    {
        N = n;
        dfs(1);
        return ret;
    }

    void dfs(int pos)
    {
        if (pos == N + 1)
        {
            ret++;
            return;
        }

        for (int i = pos; i <= N; i++)
        {
            if (!vis[i] && (i % pos == 0 || pos % i == 0))
            {
                vis[i] = true;
                dfs(i);
                vis[i] = false;
            }
        }
    }

    // 2
    int subarraySum(vector<int> &nums, int k)
    {
        unordered_map<int, int> hash;
        hash[0] = 1;

        int sum = 0, ret = 0;
        for (auto n : nums)
        {
            sum += n;
            if (hash.count(sum - k))
                ret += hash[sum - k];
            hash[sum]++;
        }

        return ret;
    }

    // 3
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
            return;
        }

        dfs(from, to, buffer, n - 1);
        to.push_back(from.back());
        from.pop_back();
        dfs(buffer, from, to, n - 1);
    }

    // 4
    int aim, res = 0, sum = 0;
    int findTargetSumWays(vector<int> &nums, int sum, int target)
    {
        aim = target;
        dfs(nums, 0, 0);
        return res;
    }

    void dfs(vector<int> &nums, int sum, int pos)
    {
        if (pos == nums.size())
        {
            if (sum == aim)
                res++;
            return;
        }

        dfs(nums, sum + nums[pos], pos + 1);
        dfs(nums, sum - nums[pos], pos + 1);
    }

    // 5
    int memo[101][101];
    int uniquePaths(int m, int n)
    {
        return dfs(m, n);
    }

    int dfs(int left, int right)
    {
        if (memo[left][right])
            return memo[left][right];

        if (left == 0 || right == 0)
        {
            memo[left][right] = 1;
            return 1;
        }

        int ret = dfs(left - 1, right) + dfs(left, right - 1);
        memo[left][right] = ret;
        return ret;
    }

    // 6
    int findContentChildren(vector<int> &g, vector<int> &s)
    {
        sort(s.begin(), s.end());
        sort(g.begin(), g.end());

        int ret = 0, m = g.size(), n = s.size();

        for (int i = 0, j = 0; i < m && j < n; i++, j++)
        {
            while (j < n && s[j] < g[i])
                j++;
            if (j < n)
                ret++;
        }

        return ret;
    }
};