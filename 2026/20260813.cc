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
    int longestPalindrome(string s)
    {
        int hash[128] = {0};

        for (char ch : s)
            hash[ch]++;

        int ret = 0;
        for (int i : hash)
            ret += i / 2 * 2;

        return ret < s.size() ? ret + 1 : ret;
    }

    // 2
    int coinChange(vector<int> &coins, int amount)
    {
        const int INF = 0x3f3f3f;
        int n = coins.size();
        vector<vector<int>> dp(n + 1, vector<int>(amount + 1, INF));

        for (int i = 0; i <= n; i++)
            dp[i][0] = 0;

        for (int i = 1; i <= n; i++)
            for (int j = 0; j <= amount; j++)
            {
                dp[i][j] = dp[i - 1][j];
                if (j >= coins[i - 1])
                    dp[i][j] = min(dp[i][j], dp[i][j - coins[i - 1]] + 1);
            }

        return dp[n][amount] == INF ? -1 : dp[n][amount];
    }

    // 3
    string reverseWords(string s)
    {
        int n = s.size(), i = 0, start = 0;
        for (; i <= n; i++)
            if (i == n || s[i] == ' ')
            {
                reverse(s.begin() + start, s.begin() + i);
                start = i + 1;
            }

        return s;
    }

    // 4
    class MyStack
    {
    private:
        queue<int> q;

    public:
        MyStack()
        {
        }

        void push(int x)
        {
            int n = q.size();
            q.push(x);

            for (int i = 0; i < n; i++)
            {
                q.push(q.front());
                q.pop();
            }
        }

        int pop()
        {
            int r = q.front();
            q.pop();
            return r;
        }

        int top()
        {
            int r = q.front();
            return r;
        }

        bool empty()
        {
            return q.empty();
        }
    };
};