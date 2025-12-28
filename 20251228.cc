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
    int calculateMinimumHP(vector<vector<int>> &dungeon)
    {
        int m = dungeon.size(), n = dungeon[0].size();

        vector<vector<int>> dp(m + 1, vector<int>(n + 1, INT_MAX));
        dp[m][n - 1] = dp[m - 1][n] = 1;

        for (int i = m - 1; i >= 0; i--)
            for (int j = n - 1; j >= 0; j--)
            {
                int req = min(dp[i + 1][j], dp[i][j + 1]);

                dp[i][j] = req - dungeon[i][j];

                dp[i][j] = max(dp[i][j], 1);
            }

        return dp[0][0];
    }

    // 2
    int profitableSchemes(int n, int m, vector<int> &group,
                          vector<int> &profit)
    {
        const int MOD = 1e9 + 7;
        int len = group.size();

        vector<vector<vector<int>>> dp(
            len + 1, vector<vector<int>>(n + 1, vector<int>(m + 1)));
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

    // 3
    bool validateStackSequences(vector<int> &pushed, vector<int> &popped)
    {
        int n = pushed.size(), i = 0;
        stack<int> st;

        for (auto n : pushed)
        {
            st.push(n);
            while (st.size() && st.top() == popped[i])
            {
                st.pop();
                i++;
            }
        }

        return i == n;
    }

    // 4
    int subarraySum(vector<int> &nums, int k)
    {
        int sum = 0, ret = 0;
        unordered_map<int, int> hash;
        hash[0] = 1;

        for (auto n : nums)
        {
            sum += n;
            if (hash.count(sum - k))
                ret += hash[sum - k];
            hash[sum]++;
        }

        return ret;
    }

    // 5
    int findSubstringInWraproundString(string s)
    {
        int n = s.size();

        vector<int> dp(n, 1);
        for (int i = 1; i < n; i++)
            if (s[i - 1] + 1 == s[i] || (s[i - 1] == 'z' && s[i] == 'a'))
                dp[i] += dp[i - 1];

        int hash[26] = {0};
        for (int i = 0; i < s.size(); i++)
        {
            int index = s[i] - 'a';
            hash[index] = max(hash[index], dp[i]);
        }

        int sum = 0;
        for (int i = 0; i < 26; i++)
            sum += hash[i];

        return sum;
    }

    // 6
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost)
    {
        int n = gas.size();

        for (int i = 0; i < n; i++)
        {
            int ret = 0, step = 0;
            for (; step < n; step++)
            {
                int index = (i + step) % n;
                ret += gas[index] - cost[index];
                if (ret < 0)
                    break;
            }

            if (ret >= 0)
                return i;

            i = i + step;
        }

        return -1;
    }

    // 7
    int maxEnvelopes(vector<vector<int>> &e)
    {
        int n = e.size();
        sort(e.begin(), e.end(), [&](const vector<int> &v1, const vector<int> &v2)
             { return v1[0] != v2[0] ? v1[0] < v2[0] : v1[1] > v2[1]; });

        vector<int> ret;
        ret.push_back(e[0][1]);

        for (int i = 1; i < n; i++)
        {
            if (e[i][1] > ret.back())
                ret.push_back(e[i][1]);
            else
            {
                int left = 0, right = ret.size() - 1;
                while (left < right)
                {
                    int mid = left + (right - left) / 2;
                    if (e[i][1] > ret[mid])
                        left = mid + 1;
                    else
                        right = mid;
                }
                ret[left] = e[i][1];
            }
        }

        return ret.size();
    }
};