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
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder)
    {
        int i = postorder.size() - 1;
        return _buildTree(inorder, postorder, i, 0, inorder.size() - 1);
    }

    TreeNode *_buildTree(vector<int> &inorder, vector<int> &postorder, int &posti, int inBegin, int inEnd)
    {
        if (inBegin > inEnd)
            return nullptr;

        TreeNode *root = new TreeNode(postorder[posti]);

        int rooti = inBegin;
        while (rooti <= inEnd)
            if (inorder[rooti] == postorder[posti])
                break;
            else
                rooti++;

        --posti;

        root->right = _buildTree(inorder, postorder, posti, rooti + 1, inEnd);
        root->left = _buildTree(inorder, postorder, posti, inBegin, rooti - 1);

        return root;
    }

    // 2
    string modifyString(string s)
    {
        int n = s.size();
        for (int i = 0; i < n; i++)
            if (s[i] == '?')
            {
                for (char ch = 'a'; ch <= 'z'; ch++)
                {
                    if ((i == 0 || s[i - 1] != ch) && (i == n - 1 || s[i + 1] != ch))
                        s[i] = ch;
                }
            }
        return s;
    }

    // 3
    int missingNumber(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());

        int left = 0, right = nums.size() - 1;
        while (left < right)
        {
            int mid = left + (right - left) / 2;
            if (mid == nums[mid])
                left = mid + 1;
            else
                right = mid;
        }

        return left == nums[left] ? left + 1 : left;
    }

    // 4
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

    // 5
    int minCostClimbingStairs(vector<int> &cost)
    {
        int n = cost.size();
        vector<int> dp(n + 1);

        for (int i = 2; i <= n; i++)
        {
            dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
        }

        return dp[n];
    }

    // 6
    int eraseOverlapIntervals(vector<vector<int>> &in)
    {
        sort(in.begin(), in.end());
        int n = in.size(), ret = 0, right = in[0][1];

        for (int i = 1; i < n; i++)
        {
            int a = in[i][0], b = in[i][1];
            if (a < right)
            {
                ret++;
                right = min(b, right);
            }
            else
                right = b;
        }

        return ret;
    }
};