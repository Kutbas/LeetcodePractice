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

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution
{
public:
    // 1
    int cnt, ret = 0;
    int kthSmallest(TreeNode *root, int k)
    {
        cnt = k;
        dfs(root);
        return ret;
    }

    void dfs(TreeNode *root)
    {
        if (root == nullptr)
            return;

        dfs(root->left);

        if (--cnt == 0)
        {
            ret = root->val;
            return;
        }

        dfs(root->right);
    }

    // 2
    int getMaxLen(vector<int> &nums)
    {
        int n = nums.size(), ret = 0;
        vector<int> f(n + 1);
        auto g = f;

        for (int i = 1; i <= n; i++)
        {
            if (nums[i - 1] > 0)
            {
                f[i] = f[i - 1] + 1;
                g[i] = g[i - 1] == 0 ? 0 : g[i - 1] + 1;
            }
            else if (nums[i - 1] < 0)
            {
                f[i] = g[i - 1] == 0 ? 0 : g[i - 1] + 1;
                g[i] = f[i - 1] + 1;
            }
            ret = max(ret, f[i]);
        }

        return ret;
    }

    // 3
    int findSubstringInWraproundString(string s)
    {
        int n = s.size();

        vector<int> dp(n, 1);

        for (int i = 1; i < n; i++)
            if ((s[i - 1] == 'z' && s[i] == 'a') || s[i - 1] + 1 == s[i])
                dp[i] += dp[i - 1];

        int hash[26] = {0};
        for (int i = 0; i < n; i++)
        {
            int index = s[i] - 'a';
            hash[index] = max(hash[index], dp[i]);
        }

        int ret = 0;
        for (auto i : hash)
            ret += i;

        return ret;
    }

    // 4
    int minInsertions(string s)
    {
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n));

        for (int i = n - 1; i >= 0; i--)
            for (int j = i + 1; j < n; j++)
            {
                if (s[i] == s[j])
                    dp[i][j] = dp[i + 1][j - 1];
                else
                    dp[i][j] = min(dp[i + 1][j], dp[i][j - 1]) + 1;
            }

        return dp[0][n - 1];
    }

    // 6
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
};

// 5
const int N = 1010;
int n, v;
int V[N], W[N];
int dp[N][N];

int main()
{
    cin >> n >> v;
    for (int i = 1; i <= n; i++)
        cin >> V[i] >> W[i];

    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= v; j++)
        {
            dp[i][j] = dp[i - 1][j];
            if (j >= V[i])
                dp[i][j] = max(dp[i][j], dp[i][j - V[i]] + W[i]);
        }

    cout << dp[n][v] << endl;

    memset(dp, 0, sizeof dp);

    for (int i = 1; i <= v; i++)
        dp[0][i] = -1;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= v; j++)
        {
            dp[i][j] = dp[i - 1][j];
            if (j >= V[i] && dp[i][j - V[i]] != -1)
                dp[i][j] = max(dp[i][j], dp[i][j - V[i]] + W[i]);
        }

    cout << (dp[n][v] == -1 ? 0 : dp[n][v]) << endl;

    return 0;
}