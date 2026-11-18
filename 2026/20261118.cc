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
    int subarraysDivByK(vector<int> &nums, int k)
    {
        int n = nums.size(), sum = 0, ret = 0;
        unordered_map<int, int> hash;
        hash[0] = 1;

        for (auto num : nums)
        {
            sum += num;
            int r = ((sum % k) + k) % k;

            if (hash.count(r))
                ret += hash[r];
            hash[r]++;
        }

        return ret;
    }

    // 2
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
                    dp[i][j][k] += dp[i - 1][j][k];
                    if (j >= group[i - 1])
                    {
                        int remain = max(0, k - profit[i - 1]);
                        dp[i][j][k] += dp[i - 1][j - group[i - 1]][remain];
                    }

                    dp[i][j][k] %= MOD;
                }

        return dp[len][n][m];
    }

    // 3
    int myAtoi(string s)
    {
        int n = s.size(), sign = 1, i = 0;

        while (s[i] == ' ')
            i++;

        if (s[i] == '+' || s[i] == '-')
        {
            if (s[i] == '-')
                sign = -1;
            i++;
        }

        int ret = 0;
        while (i < n)
        {

            if (!isdigit(s[i]))
            {
                break;
            }

            // ret>(INT_MAX-(s[i]-'0'))/10
            if (ret > (INT_MAX - (s[i] - '0')) / 10)
                return sign == 1 ? INT_MAX : INT_MIN;

            ret = ret * 10 + (s[i++] - '0');
        }

        return ret * sign;
    }
};