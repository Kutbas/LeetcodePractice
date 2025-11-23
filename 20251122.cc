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
    int deleteAndEarn(vector<int> &nums)
    {
        const int N = 10001;
        int arr[N] = {0};
        for (int x : nums)
            arr[x] += x;

        vector<int> f(N, 0);
        vector<int> g(N, 0);

        for (int i = 1; i < N; i++)
        {
            f[i] = g[i - 1] + arr[i];
            g[i] = max(f[i - 1], g[i - 1]);
        }

        return max(f[N - 1], g[N - 1]);
    }

    // 2
    int findContentChildren(vector<int> &g, vector<int> &s)
    {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());

        int ret = 0;
        for (int i = 0; i < g.size(); i++)
        {
            int j = 0;
            while (j < s.size() && s[j] < g[i])
                j++;
            if (s[j] >= g[i])
                ret++;
        }

        return ret;
    }

    // 3
    int tribonacci(int n)
    {
        if (n == 0)
            return 0;
        if (n == 1 || n == 2)
            return 1;

        int a = 0, b = 1, c = 1, d = 0;
        for (int i = 3; i <= n; i++)
        {
            d = a + b + c;
            a = b;
            b = c;
            c = d;
        }

        return d;
    }

    // 4
    bool isInterleave(string s1, string s2, string s3)
    {
        int m = s1.size(), n = s2.size();
        if (m + n != s3.size())
            return false;

        s1 = " " + s1;
        s2 = " " + s2;
        s3 = " " + s3;

        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1));
        dp[0][0] = false;

        for (int i = 1; i <= m; i++)
            if (s1[i] == s3[i])
                dp[i][0] = dp[i - 1][0];
            else
                break;

        for (int j = 1; j <= n; j++)
            if (s2[j] == s3[j])
                dp[0][j] = dp[0][j - 1];
            else
                break;

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                bool from_s1 = (s1[i] == s3[i + j] && dp[i - 1][j]);
                bool from_s2 = (s2[j] == s3[i + j] && dp[i][j - 1]);
                dp[i][j] = from_s1 || from_s2;
            }

        return dp[m][n];
    }

    // 5
    int ret = 0;
    int sumNumbers(TreeNode *root)
    {
        dfs(root, 0);
        return ret;
    }

    void dfs(TreeNode *root, int path)
    {
        path = path * 10 + root->val;

        if (root->left == nullptr && root->right == nullptr)
        {
            ret += path;
            return;
        }

        if (root->left)
            dfs(root->left, path);
        if (root->right)
            dfs(root->right, path);
    }

    // 6
    void moveZeroes(vector<int> &nums)
    {
        int n = nums.size();
        for (int dest = -1, cur = 0; cur < n; cur++)
            if (nums[cur])
                swap(nums[++dest], nums[cur]);
    }

    // 7
    int jump(vector<int> &nums)
    {
        int n = nums.size(), cur = 0, far = 0, ret = 0;

        for (int i = 0; i < n - 1; i++)
        {
            far = max(far, i + nums[i]);

            if (i == cur)
            {
                cur = far;
                ret++;

                if (cur >= n - 1)
                    break;
            }
        }

        return ret;
    }
};