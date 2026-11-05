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
#include <regex>
#include <map>
#include <set>
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
    int longestOnes(vector<int> &nums, int k)
    {
        int n = nums.size(), ret = 0;

        for (int left = 0, right = 0, count = 0; right < n; right++)
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

    // 2
    int findLengthOfLCIS(vector<int> &nums)
    {
        int n = nums.size(), ret = 0;

        for (int left = 0, right = 0; right < n; right++)
        {
            while (right + 1 < n && nums[right + 1] > nums[right])
                right++;
            ret = max(ret, right - left + 1);
            left = right + 1;
        }

        return ret;
    }

    // 3
    int findLongestChain(vector<vector<int>> &pairs)
    {
        sort(pairs.begin(), pairs.end());
        int n = pairs.size(), left = pairs[0][0], right = pairs[0][1];
        vector<int> dp(n, 1);

        int ret = 1;

        for (int i = 1; i < n; i++)
            for (int j = 0; j < i; j++)
            {
                if (pairs[j][1] < pairs[i][0])
                {
                    dp[i] = max(dp[i], dp[j] + 1);
                    ret = max(ret, dp[i]);
                }
            }

        return ret;
    }

    // 4
    int lenLongestFibSubseq(vector<int> &arr)
    {
        int n = arr.size();
        unordered_map<int, int> hash;
        for (int i = 0; i < n; i++)
            hash[arr[i]] = i;

        int ret = 2;
        vector<vector<int>> dp(n, vector<int>(n, 2));
        for (int j = 2; j < n; j++)
            for (int i = 1; i < j; i++)
            {
                int a = arr[j] - arr[i];
                if (a < arr[i] && hash.count(a))
                    dp[i][j] = dp[hash[a]][i] + 1;
                ret = max(ret, dp[i][j]);
            }

        return ret < 3 ? 0 : ret;
    }

    // 5
    bool canPartition(vector<int> &nums)
    {
        int n = nums.size(), sum = 0;
        for (auto num : nums)
            sum += num;

        if (sum % 2)
            return false;

        int aim = sum / 2;
        vector<vector<bool>> dp(n + 1, vector<bool>(aim + 1));

        for (int i = 0; i <= n; i++)
            dp[i][0] = true;

        for (int i = 1; i <= n; i++)
            for (int j = 0; j <= aim; j++)
            {
                dp[i][j] = dp[i - 1][j];
                if (j >= nums[i - 1])
                    dp[i][j] = dp[i][j] || dp[i - 1][j - nums[i - 1]];
            }

        return dp[n][aim];
    }

    // 6
    string ret;
    string tree2str(TreeNode *root)
    {
        dfs(root);
        return ret;
    }

    void dfs(TreeNode *root)
    {
        if (root == nullptr)
            return;

        ret += to_string(root->val);

        if (root->left || root->right)
        {
            ret += '(';
            dfs(root->left);
            ret += ')';
        }

        if (root->right)
        {
            ret += '(';
            dfs(root->right);
            ret += ')';
        }
    }
};