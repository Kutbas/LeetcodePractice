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
    int waysToStep(int n)
    {
        if (n < 3)
            return n;

        const int MOD = 1e9 + 7;
        int dp1 = 1, dp2 = 2, dp3 = 4, dp4 = 0;

        while (n-- != 3)
        {
            dp4 = ((dp1 + dp2) % MOD + dp3) % MOD;
            dp1 = dp2, dp2 = dp3, dp3 = dp4;
        }

        return dp3;
    }

    // 3
    vector<vector<string>> groupAnagrams(vector<string> &strs)
    {
        unordered_map<string, vector<string>> hash;
        for (auto str : strs)
        {
            string tmp = str;
            sort(tmp.begin(), tmp.end());
            hash[tmp].push_back(str);
        }

        vector<vector<string>> ret;
        for (auto &[a, b] : hash)
        {
            ret.push_back(b);
        }

        return ret;
    }

    // 4
    int N, left = 0, right = 0;
    vector<string> ret;
    string path;
    vector<string> generateParenthesis(int n)
    {
        N = n;
        dfs();
        return ret;
    }

    void dfs()
    {
        if (right == N)
        {
            ret.push_back(path);
            return;
        }

        if (left < N)
        {
            path.push_back('(');
            left++;
            dfs();
            left--;
            path.pop_back();
        }

        if (right < left)
        {
            path.push_back(')');
            right++;
            dfs();
            right--;
            path.pop_back();
        }
    }

    // 5
    int findLongestChain(vector<vector<int>> &pairs)
    {
        sort(pairs.begin(), pairs.end());
        int n = pairs.size(), ret = 1;
        vector<int> dp(n, 1);

        for (int i = 1; i < n; i++)
            for (int j = 0; j < i; j++)
            {
                int a = pairs[j][1], b = pairs[i][0];
                if (a < b)
                    dp[i] = max(dp[i], dp[j] + 1);
                ret = max(dp[i], ret);
            }

        return ret;
    }

    // 6
    vector<TreeNode *> TreeList;

    void Inorder(TreeNode *root)
    {
        if (root == nullptr)
            return;

        Inorder(root->left);
        TreeList.push_back(root);
        Inorder(root->right);
    }

    TreeNode *Convert(TreeNode *pRootOfTree)
    {
        if (pRootOfTree == nullptr)
            return nullptr;

        Inorder(pRootOfTree);

        for (int i = 1; i < TreeList.size(); i++)
        {
            TreeList[i]->left = TreeList[i - 1];
            TreeList[i - 1]->right = TreeList[i];
        }

        return TreeList[0];
    }
};