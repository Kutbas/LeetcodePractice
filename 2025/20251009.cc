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
    int longestPalindromeSubseq(string s)
    {
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n));

        for (int i = n - 1; i >= 0; i--)
        {
            dp[i][i] = 1;
            for (int j = i + 1; j < n; j++)
            {
                if (s[i] == s[j])
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                else
                    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
            }
        }

        return dp[0][n - 1];
    }

    int minInsertions(string s)
    {
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n));

        for (int i = n - 1; i >= 0; i--)
            for (int j = i + 1; j < n; j++)
                if (s[i] == s[j])
                    dp[i][j] = dp[i + 1][j - 1];
                else
                    dp[i][j] = min(dp[i + 1][j], dp[i][j - 1]) + 1;

        return dp[0][n-1];
    }

    // 1
    int findLengthOfLCIS(vector<int> &nums)
    {
        int n = nums.size();

        int ret = 0;
        for (int i = 0; i < n; i++)
        {
            int j = i;
            while (j + 1 < n && nums[j + 1] > nums[j])
                j++;
            ret = max(ret, j - i);
        }

        return ret + 1;
    }

    // 2
    vector<int> advantageCount(vector<int> &nums1, vector<int> &nums2)
    {
        int n = nums1.size();
        sort(nums1.begin(), nums1.end());

        vector<int> index2(n);
        for (int i = 0; i < n; i++)
            index2[i] = i;

        sort(index2.begin(), index2.end(), [&](int i, int j)
             { return nums2[i] < nums2[j]; });

        vector<int> ret(n);
        int left = 0, right = n - 1;
        for (auto n : nums1)
        {
            if (n > nums2[index2[left]])
                ret[index2[left++]] = n;
            else
                ret[index2[right--]] = n;
        }

        return ret;
    }

    // 3
    int jump(vector<int> &nums)
    {
        int n = nums.size(), left = 0, right = 0, maxPos = 0, ret = 0;

        while (left <= right)
        {
            if (maxPos >= n - 1)
                return ret;

            for (int i = left; i <= right; i++)
                maxPos = max(maxPos, nums[i] + i);

            left = right + 1;
            right = maxPos;
            ret++;
        }

        return -1;
    }

    // 4
    TreeNode *pruneTree(TreeNode *root)
    {
        if (root == nullptr)
            return nullptr;

        root->left = pruneTree(root->left);

        if (root->left == nullptr && root->right == nullptr && root->val == 0)
            return nullptr;

        root->right = pruneTree(root->right);

        return root;
    }

    // 5
    int lengthOfLIS(vector<int> &nums)
    {
        vector<int> ret;
        ret.push_back(nums[0]);

        for (int i = 1; i < nums.size(); i++)
        {
            if (nums[i] > ret.back())
                ret.push_back(nums[i]);
            else
            {
                int left = 0, right = ret.size() - 1;
                while (left < right)
                {
                    int mid = left + (right - left) / 2;
                    if (ret[mid] < nums[i])
                        left = mid + 1;
                    else
                        right = mid;
                }
                ret[left] = nums[i];
            }
        }

        return ret.size();
    }

    // 6
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
};