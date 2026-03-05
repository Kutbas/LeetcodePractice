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
    int lastStoneWeightII(vector<int> &stones)
    {
        int n = stones.size(), sum = 0;
        for (auto n : stones)
            sum += n;

        int m = sum / 2;
        vector<vector<int>> dp(n + 1, vector<int>(m + 1));
        for (int i = 1; i <= n; i++)
            for (int j = 0; j <= m; j++)
            {
                dp[i][j] = dp[i - 1][j];

                if (j >= stones[i - 1])
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - stones[i - 1]] + stones[i - 1]);
            }

        return sum - 2 * dp[n][m];
    }

    // 2
    int halveArray(vector<int> &nums)
    {
        priority_queue<double> q;
        double sum = 0;

        for (auto n : nums)
        {
            q.push(n);
            sum += n;
        }

        double aim = sum / 2.0;
        int ret = 0;
        while (sum > aim)
        {
            double t = q.top() / 2.0;
            q.pop();
            sum -= t;
            q.push(t);
            ret++;
        }

        return ret;
    }

    // 3
    int profitableSchemes(int n, int m, vector<int> &group, vector<int> &profit)
    {
        const int MOD = 1e9 + 7;
        int len = group.size();

        vector<vector<vector<int>>> dp(len + 1, vector<vector<int>>(n + 1, vector<int>(m + 1)));
        for (int i = 0; i <= n; i++)
            dp[0][i][0] = 1;

        for (int i = 1; i <= len; i++)
            for (int j = 0; j <= n; j++)
                for (int k = 0; k <= m; k++)
                {
                    dp[i][j][k] = dp[i - 1][j][k];

                    if (j >= group[i - 1])
                    {
                        int remain = max(0, k - profit[i - 1]);

                        dp[i][j][k] += dp[i - 1][j - group[i - 1]][remain];
                    }

                    dp[i][j][k] %= MOD;
                }

        return dp[len][n][m];
    }

    // 4
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
    {
        if (l1 == nullptr)
            return l2;
        if (l2 == nullptr)
            return l1;

        if (l1->val < l2->val)
        {
            l1->next = mergeTwoLists(l1->next, l2);
            return l1;
        }
        else
        {
            l2->next = mergeTwoLists(l1, l2->next);
            return l2;
        }
    }
};