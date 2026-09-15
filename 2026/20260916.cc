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
    int getSum(int a, int b)
    {
        while (b)
        {
            int x = a ^ b;
            int carry = (a & b) << 1;
            a = x;
            b = carry;
        }

        return a;
    }

    // 2
    int wiggleMaxLength(vector<int> &nums)
    {
        int n = nums.size(), left = 0, right = 0, ret = 0;

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

    // 3
    int maxProfit(vector<int> &prices)
    {
        int n = prices.size(), ret = 0, prev = INT_MAX;

        for (int i = 1; i < n; i++)
        {
            prev = min(prev, prices[i - 1]);
            ret = max(ret, prices[i] - prev);
        }

        return ret;
    }

    // 4
    int minFallingPathSum(vector<vector<int>> &matrix)
    {
        const int INF = 0x3f3f3f;
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 2, INF));

        for (int i = 0; i < n + 2; i++)
            dp[0][i] = 0;

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                dp[i][j] = min(dp[i - 1][j], min(dp[i - 1][j - 1], dp[i - 1][j + 1])) + matrix[i - 1][j - 1];
            }

        int ret = INF;
        for (int i = 1; i <= n; i++)
            ret = min(ret, dp[m][i]);

        return ret;
    }

    // 5
    int minCost(vector<vector<int>> &costs)
    {
        int n = costs.size();
        vector<vector<int>> dp(n + 1, vector<int>(3));

        for (int i = 1; i <= n; i++)
        {
            dp[i][0] = min(dp[i - 1][1], dp[i - 1][2]) + costs[i - 1][0];
            dp[i][1] = min(dp[i - 1][0], dp[i - 1][2]) + costs[i - 1][1];
            dp[i][2] = min(dp[i - 1][1], dp[i - 1][0]) + costs[i - 1][2];
        }

        return min(dp[n][0], min(dp[n][1], dp[n][2]));
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
                for (int j = 1; j <= i; j++)
                {
                    if (isPal[j][i])
                        dp[i] = min(dp[i], dp[j - 1] + 1);
                }
            }
        }

        return dp[n - 1];
    }

    // 7
    int minimumDeleteSum(string s1, string s2)
    {
        int m = s1.size(), n = s2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                if (s1[i - 1] == s2[j - 1])
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + s1[i - 1]);
            }

        int sum = 0;
        for (char ch : s1)
            sum += ch;
        for (char ch : s2)
            sum += ch;

        return sum - 2 * dp[m][n];
    }

    // 8
    class MinStack
    {
    private:
        long minElem;
        stack<long> diff;

    public:
        MinStack()
        {
        }

        void push(int value)
        {
            if (diff.empty())
            {
                diff.push(0);
                minElem = value;
            }
            else
            {
                long newdiff = value - minElem;

                if (newdiff < 0)
                    minElem = value;

                diff.push(newdiff);
            }
        }

        void pop()
        {
            long top = diff.top();
            diff.pop();

            if (top < 0)
                minElem = minElem - top;
        }

        int top()
        {
            long top = diff.top();

            if (top > 0)
                return minElem + top;

            return minElem;
        }

        int getMin()
        {
            return minElem;
        }
    };

    // 9
    bool GetPath(TreeNode *root, TreeNode *x, stack<TreeNode *> &st)
    {
        if (root == nullptr)
            return false;

        st.push(root);

        if (root == x)
            return true;

        if (GetPath(root->left, x, st))
            return true;
        if (GetPath(root->right, x, st))
            return true;

        st.pop();

        return false;
    }

    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        stack<TreeNode *> pPath, qPath;

        GetPath(root, p, pPath);
        GetPath(root, q, qPath);

        while (pPath.size() != qPath.size())
        {
            if (pPath.size() > qPath.size())
                pPath.pop();
            else
                qPath.pop();
        }

        while (qPath.top() != pPath.top())
            qPath.pop(), pPath.pop();

        return pPath.top();
    }
};