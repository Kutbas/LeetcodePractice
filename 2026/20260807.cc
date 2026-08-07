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
    vector<int> findSubstring(string s, vector<string> &words)
    {
        int m = s.size(), n = words.size(), len = words[0].size();
        vector<int> ret;
        unordered_map<string, int> hash1;

        for (auto &word : words)
            hash1[word]++;

        for (int i = 0; i < len; i++)
        {
            unordered_map<string, int> hash2;

            for (int left = i, right = i, count = 0; right + len <= m;
                 right += len)
            {
                string in = s.substr(right, len);
                if (hash1.count(in) && ++hash2[in] <= hash1[in])
                    count++;

                while (right - left + 1 > len * n)
                {
                    string out = s.substr(left, len);
                    if (hash1.count(out) && hash2[out]-- <= hash1[out])
                        count--;
                    left += len;
                }

                if (count == n)
                    ret.push_back(left);
            }
        }

        return ret;
    }

    // 2
    int minCut(string s)
    {
        int n = s.size();
        vector<vector<bool>> isPal(n, vector<bool>(n));

        for (int i = n - 1; i >= 0; i--)
            for (int j = i; j < n; j++)
                if (s[i] == s[j])
                    isPal[i][j] = j - i + 1 > 3 ? isPal[i + 1][j - 1] : true;

        vector<int> dp(n, INT_MAX);
        for (int i = 0; i < n; i++)
        {
            if (isPal[0][i])
                dp[i] = 0;
            else
            {
                for (int j = 1; j <= i; j++)
                {
                    if (isPal[j][i])
                    {
                        dp[i] = min(dp[i], dp[j - 1] + 1);
                    }
                }
            }
        }

        return dp[n - 1];
    }

    // 3
    int coinChange(vector<int> &coins, int amount)
    {
        const int INF = 0x3f3f3f;
        int n = coins.size();

        vector<vector<int>> dp(n + 1, vector<int>(amount + 1, INF));
        dp[0][0] = 0;

        for (int i = 1; i <= n; i++)
            for (int j = 0; j <= amount; j++)
            {
                dp[i][j] = dp[i - 1][j];
                if (j >= coins[i - 1])
                    dp[i][j] = min(dp[i][j], dp[i][j - coins[i - 1]] + 1);
            }

        return dp[n][amount] == INF ? -1 : dp[n][amount];
    }

    // 4

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