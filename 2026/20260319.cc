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

    // 2
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

    // 3
    int numDecodings(string s)
    {
        int n = s.size();
        vector<double> dp(n);

        dp[0] = s[0] == '0' ? 0 : 1;
        if (n == 1)
            return dp[0];

        if (s[0] != '0' && s[1] != '0')
            dp[1] += 1;
        int twoDigits = (s[0] - '0') * 10 + (s[1] - '0');
        if (twoDigits >= 10 && twoDigits <= 26)
            dp[1] += 1;

        for (int i = 2; i < n; i++)
        {
            if (s[i] != '0')
                dp[i] += dp[i - 1];

            int twoDigits = (s[i - 1] - '0') * 10 + (s[i] - '0');
            if (twoDigits >= 10 && twoDigits <= 26)
                dp[i] += dp[i - 2];
        }

        return dp[n - 1];
    }

    // 4
    int findLength(vector<int> &nums1, vector<int> &nums2)
    {
        int m = nums1.size(), n = nums2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));

        int ret = 0;
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                if (nums1[i - 1] == nums2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                ret = max(ret, dp[i][j]);
            }

        return ret;
    }

    // 5
    bool isMatch(string s, string p)
    {
        int m = s.size(), n = p.size();
        s = " " + s;
        p = " " + p;
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1));
        dp[0][0] = true;

        for (int i = 1; i <= n; i++)
            if (p[i] == '*')
                dp[0][i] = true;
            else
                break;

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                if (p[j] == '*')
                    dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
                else
                    dp[i][j] = (p[j] == '?' || p[j] == s[i]) && dp[i - 1][j - 1];
            }

        return dp[m][n];
    }

    // 6
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder)
    {
        // 从后序遍历的最后一个元素开始
        int i = postorder.size() - 1;

        return _buildTree(inorder, postorder, i, 0, inorder.size() - 1);
    }

    TreeNode *_buildTree(vector<int> &inorder, vector<int> &postorder,
                         int &posti, int inBegin, int inEnd)
    {
        // 如果这里没有节点构造二叉树了，就结束
        if (inBegin > inEnd)
            return nullptr;

        // 选择 posti 位置的元素作为当前子树根节点
        TreeNode *root = new TreeNode(postorder[posti]);

        int rooti = inBegin;
        while (rooti <= inEnd)
            if (inorder[rooti] == postorder[posti])
                break;
            else
                rooti++;

        posti--;
        // 先构建右子树，再构建左子树
        root->right = _buildTree(inorder, postorder, posti, rooti + 1, inEnd);
        root->left = _buildTree(inorder, postorder, posti, inBegin, rooti - 1);
        return root;
    }
};
