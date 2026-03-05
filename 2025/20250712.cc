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
    int ret = 0, aim = 0;
    int findTargetSumWays(vector<int> &nums, int target)
    {
        aim = target;
        dfs(nums, 0, 0);
        return ret;
    }

    void dfs(vector<int> &nums, int pos, int sum)
    {
        if (pos == nums.size())
        {
            if (sum == aim)
                ret++;
            return;
        }

        dfs(nums, pos + 1, sum + nums[pos]);
        dfs(nums, pos + 1, sum - nums[pos]);
    }

    vector<string> ret1;
    string path;
    int left = 0, right = 0, N = 0;
    vector<string> generateParenthesis(int n)
    {
        N = n;
        dfs();
        return ret1;
    }

    void dfs()
    {
        if (right == N)
        {
            ret1.push_back(path);
            return;
        }

        if (left < N)
        {
            path.push_back('(');
            left++;
            dfs();
            path.pop_back();
            left--;
        }

        if (right < left)
        {
            path.push_back(')');
            right++;
            dfs();
            path.pop_back();
            right--;
        }
    }

    int findLengthOfLCIS(vector<int> &nums)
    {
        int ret = 0, n = nums.size();
        for (int i = 0; i < n;)
        {
            int j = i + 1;
            while (j < n && nums[j] > nums[i])
                j++;
            ret = max(ret, j - i);
            i = j;
        }

        return ret;
    }
};