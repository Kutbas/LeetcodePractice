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
    int findMin(vector<int> &nums)
    {
        int n = nums.size(), left = 0, right = n - 1;

        while (left < right)
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] > nums[n - 1])
                left = mid + 1;
            else
                right = mid;
        }

        return nums[left];
    }

    // 3
    TreeNode *pruneTree(TreeNode *root)
    {

        if (root->left)
            root->left = pruneTree(root->left);
        if (root->right)
            root->right = pruneTree(root->right);

        if (root->left == nullptr && root->right == nullptr && root->val == 0)
            return nullptr;

        return root;
    }

    // 4
    int eraseOverlapIntervals(vector<vector<int>> &intervals)
    {
        sort(intervals.begin(), intervals.end());

        int n = intervals.size(), ret = 0, right = intervals[0][1];
        for (int i = 1; i < n; i++)
        {
            int a = intervals[i][0], b = intervals[i][1];
            if (a < right)
            {
                ret++;
                right = min(right, b);
            }
            else
                right = b;
        }

        return ret;
    }

    // 5
    int maxProfit(vector<int> &prices, int fee)
    {
        int n = prices.size();
        vector<int> f(n), g(n);
        f[0] = -prices[0];

        for (int i = 1; i < n; i++)
        {
            f[i] = max(f[i - 1], g[i - 1] - prices[i]);
            g[i] = max(g[i - 1], f[i - 1] + prices[i] - fee);
        }

        return g[n - 1];
    }

    // 6
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
                for (int j = 1; j < n; j++)
                    if (isPal[j][i])
                        dp[i] = min(dp[j - 1] + 1, dp[i]);
            }
        }

        return dp[n - 1];
    }

    // 7
    int longestPalindromeSubseq(string s)
    {
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n));

        for (int i = n - 1; i >= 0; i--)
            for (int j = i; j < n; j++)
            {
                if (s[i] == s[j])
                    dp[i][j] = i == j ? 1 : dp[i + 1][j - 1] + 2;
                else
                    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
            }

        return dp[0][n - 1];
    }
};

// 2
int main()
{
    int n, m;
    cin >> n >> m;

    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> arr[i];

    vector<long long> dp(n + 1);
    for (int i = 1; i <= n; i++)
        dp[i] = dp[i - 1] + arr[i];

    int l, r;
    while (m--)
    {
        cin >> l >> r;
        cout << dp[r] - dp[l - 1] << endl;
    }

    return 0;
}

// 8
const int N = 1010;
int n, v;
int V[N], W[N];
int dp[N][N];

int main()
{
    cin >> n >> v;
    for (int i = 1; i <= n; i++)
        cin >> V[i] >> W[i];

    memset(dp, 0, sizeof dp);
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