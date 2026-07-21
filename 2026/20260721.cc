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
#include <regex>
#include <map>
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
    int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid)
    {
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        dp[0][1] = 1;

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                if (obstacleGrid[i - 1][j - 1] == 0)
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }

        return dp[m][n];
    }

    // 2
    string addBinary(string a, string b)
    {
        int m = a.size(), n = b.size();
        int cur1 = m - 1, cur2 = n - 1, t = 0;
        string ret;

        while (cur1 >= 0 || cur2 >= 0 || t)
        {
            if (cur1 >= 0)
                t += a[cur1--] - '0';
            if (cur2 >= 0)
                t += b[cur2--] - '0';

            ret += to_string(t % 2);
            t /= 2;
        }

        reverse(ret.begin(), ret.end());

        return ret[0] == '0' ? "0" : ret;
    }

    // 3
    int K, ret = 0;
    int kthSmallest(TreeNode *root, int k)
    {
        K = k;
        dfs(root);
        return ret;
    }

    void dfs(TreeNode *root)
    {
        if (root->left)
            dfs(root->left);

        if (--K == 0)
        {
            ret = root->val;
            return;
        }

        if (root->right)
            dfs(root->right);
    }

    // 4
    vector<string> ret;
    string path;
    vector<string> letterCasePermutation(string s)
    {
        dfs(s, 0);
        return ret;
    }

    void dfs(string &s, int pos)
    {
        if (pos == s.size())
        {
            ret.push_back(path);
            return;
        }

        path.push_back(s[pos]);
        dfs(s, pos + 1);
        path.pop_back();

        if (!isdigit(s[pos]))
        {
            char tmp = change(s[pos]);
            path.push_back(tmp);
            dfs(s, pos + 1);
            path.pop_back();
        }
    }

    char change(char ch)
    {
        return (ch >= 'a' && ch <= 'z') ? toupper(ch) : tolower(ch);
    }

    // 5
    string largestNumber(vector<int> &nums)
    {
        vector<string> strs;
        for (auto num : nums)
            strs.push_back(to_string(num));

        sort(strs.begin(), strs.end(), [](string s1, string s2)
             { return s1 + s2 > s2 + s1; });

        string ret;
        for (auto s : strs)
            ret += s;

        return ret[0] == '0' ? "0" : ret;
    }

    // 6
    int wiggleMaxLength(vector<int> &nums)
    {
        int n = nums.size(), ret = 0, left = 0, right = 0;

        for (int i = 1; i < n; i++)
        {
            right = nums[i] - nums[i - 1];
            if (right == 0)
                continue;
            if (left * right <= 0)
                ret++;
            left = right;
        }

        return ret + 1;
    }

    // 7
    int maxProfit(vector<int> &prices)
    {
        int n = prices.size(), ret = 0;

        for (int left = 0, right = 0; right < n; right++)
        {
            while (right + 1 < n && prices[right + 1] > prices[right])
                right++;

            ret += prices[right] - prices[left];
            left = right + 1;
        }

        return ret;
    }

    // 8
    int maxUncrossedLines(vector<int> &nums1, vector<int> &nums2)
    {
        int m = nums1.size(), n = nums2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                if (nums1[i - 1] == nums2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }

        return dp[m][n];
    }

    // 9
    int longestSubsequence(vector<int> &arr, int difference)
    {
        unordered_map<int, int> hash;
        hash[arr[0]] = 1;

        int ret = 1;
        for (int i = 1; i < arr.size(); i++)
        {
            hash[arr[i]] = hash[arr[i] - difference] + 1;
            ret = max(ret, hash[arr[i]]);
        }

        return ret;
    }

    // 10
    int massage(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 0)
            return 0;

        vector<int> f(n), g(n);
        f[0] = nums[0];

        for (int i = 1; i < n; i++)
        {
            f[i] = g[i - 1] + nums[i];
            g[i] = max(f[i - 1], g[i - 1]);
        }

        return max(f[n - 1], g[n - 1]);
    }
};