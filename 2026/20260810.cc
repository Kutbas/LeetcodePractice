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
    int maxProfit(vector<int> &prices)
    {
        int n = prices.size(), prev = INT_MAX, ret = 0;

        for (int i = 1; i < n; i++)
        {
            prev = min(prev, prices[i - 1]);
            ret = max(ret, prices[i] - prev);
        }

        return ret;
    }

    // 2
    vector<vector<int>> merge(vector<vector<int>> &intervals)
    {
        sort(intervals.begin(), intervals.end());
        int n = intervals.size(), left = intervals[0][0],
            right = intervals[0][1];
        vector<vector<int>> ret;

        for (int i = 1; i < n; i++)
        {
            int a = intervals[i][0], b = intervals[i][1];
            if (a <= right)
                right = max(right, b);
            else
            {
                ret.push_back({left, right});
                left = a, right = b;
            }
        }

        ret.push_back({left, right});

        return ret;
    }

    // 3
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

    // 4
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

    // 5
    vector<string> uncommonFromSentences(string s1, string s2)
    {
        unordered_map<string, int> hash;

        auto countWords = [&](const string &s)
        {
            istringstream iss(s);
            string word;
            while (iss >> word)
                hash[word]++;
        };

        countWords(s1);
        countWords(s2);

        vector<string> ret;
        for (auto &[a, b] : hash)
            if (b == 1)
                ret.push_back(a);

        return ret;
    }
};