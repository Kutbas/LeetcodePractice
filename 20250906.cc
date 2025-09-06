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
    int deleteAndEarn(vector<int> &nums)
    {
        const int N = 10001;
        int arr[N] = {0};
        for (auto x : nums)
            arr[x] += x;

        vector<int> f(N);
        auto g = f;

        for (int i = 1; i < N; i++)
        {
            f[i] = g[i - 1] + arr[i];
            g[i] = max(f[i - 1], g[i - 1]);
        }

        return max(f[N - 1], g[N - 1]);
    }

    // 1
    int ret = 0, aim;
    int findTargetSumWays(vector<int> &nums, int target)
    {
        aim = target;
        dfs(nums, 0, 0);
        return ret;
    }

    void dfs(vector<int> &nums, int pos, int path)
    {
        if (pos == nums.size())
        {
            if (path == aim)
                ret++;
            return;
        }

        dfs(nums, pos + 1, path + nums[pos]);
        dfs(nums, pos + 1, path - nums[pos]);
    }

    // 2
    int m, n;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int memo[201][201];
    int longestIncreasingPath(vector<vector<int>> &matrix)
    {
        m = matrix.size(), n = matrix[0].size();
        int ret = 0;

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                ret = max(ret, Dfs(matrix, i, j));

        return ret;
    }

    int Dfs(vector<vector<int>> &matrix, int i, int j)
    {
        if (memo[i][j])
            return memo[i][j];

        int ret = 1;
        for (int k = 0; k < 4; k++)
        {
            int x = i + dx[k], y = j + dy[k];
            if (x >= 0 && x < m && y >= 0 && y < n && matrix[x][y] > matrix[i][j])
                ret = max(ret, Dfs(matrix, x, y) + 1);
        }

        memo[i][j] = ret;
        return ret;
    }

    // 3
    vector<vector<int>> Ret;
    vector<int> path;
    int aim;
    vector<vector<int>> combinationSum(vector<int> &candidates, int target)
    {
        aim = target;
        dfs(candidates, 0, 0);
        return Ret;
    }

    void dfs(vector<int> &nums, int sum, int pos)
    {
        if (sum > aim)
            return;

        if (sum == aim)
        {
            Ret.push_back(path);
            return;
        }

        for (int i = pos; i < nums.size(); i++)
        {
            path.push_back(nums[i]);
            dfs(nums, sum + nums[i], i);
            path.pop_back();
        }
    }

    // 4
    ListNode *reverseList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *newhead = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;

        return newhead;
    }

    // 5
    int findMaxLength(vector<int> &nums)
    {
        unordered_map<int, int> hash;
        hash[0] = -1;
        int ret = 0, sum = 0;

        for (int i = 0; i < nums.size(); i++)
        {
            sum += nums[i] == 0 ? -1 : 1;

            if (hash.count(sum))
                ret = max(ret, i - hash[sum]);
            else
                hash[sum] = i;
        }

        return ret;
    }

    // 6
    int longestOnes(vector<int> &nums, int k)
    {
        int ret = 0;
        for (int left = 0, right = 0, count = 0; right < nums.size(); right++)
        {
            if (nums[right] == 0)
                count++;
            while (count > k)
                if (nums[left++] == 0)
                    count--;

            ret = max(ret, right - left + 1);
        }
        return ret;
    }
};