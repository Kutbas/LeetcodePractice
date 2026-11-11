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

class Solution
{
public:
    // 1
    vector<int> rearrangeBarcodes(vector<int> &barcodes)
    {
        int n = barcodes.size(), maxCount = 0, maxVal = 0;
        unordered_map<int, int> hash;
        for (auto num : barcodes)
        {
            if (++hash[num] > maxCount)
            {
                maxCount = hash[num];
                maxVal = num;
            }
        }

        vector<int> ret(n);
        int index = 0;

        for (int i = 0; i < maxCount; i++)
        {

            ret[index] = maxVal;
            index += 2;
        }

        hash.erase(maxVal);

        for (auto [a, b] : hash)
            for (int i = 0; i < b; i++)
            {
                if (index > n - 1)
                    index = 1;

                ret[index] = a;
                index += 2;
            }

        return ret;
    }

    // 2
    int maxProfit(vector<int> &prices)
    {
        const int INF = 0x3f3f3f;
        int n = prices.size();
        vector<vector<int>> f(n, vector<int>(3, -INF));
        auto g = f;
        f[0][0] = -prices[0];
        g[0][0] = 0;

        int ret = 0;
        for (int i = 1; i < n; i++)
            for (int j = 0; j <= 2; j++)
            {
                f[i][j] = max(f[i - 1][j], g[i - 1][j] - prices[i]);
                g[i][j] = g[i - 1][j];
                if (j >= 1)
                    g[i][j] = max(g[i][j], f[i - 1][j - 1] + prices[i]);
                ret = max(ret, g[i][j]);
            }

        return ret;
    }

    // 3
    bool wordBreak(string s, vector<string> &wordDict)
    {
        int n = s.size();
        unordered_set<string> hash(wordDict.begin(), wordDict.end());
        s = " " + s;
        vector<bool> dp(n + 1);
        dp[0] = true;

        for (int i = 1; i <= n; i++)
            for (int j = i; j >= 1; j--)
            {
                if (dp[j - 1] && hash.count(s.substr(j, i - j + 1)))
                {
                    dp[i] = true;
                    break;
                }
            }

        return dp[n];
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

    // 5
};