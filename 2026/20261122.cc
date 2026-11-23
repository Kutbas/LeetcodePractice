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
    int getSum(int a, int b)
    {
        while (b)
        {
            int xorsum = a ^ b;
            int carry = (a & b) << 1;
            a = xorsum;
            b = carry;
        }

        return a;
    }

    // 2
    string decodeString(string s)
    {
        // int n=s.size();
        stack<string> strs;
        stack<int> nums;
        int n = 0;
        string ret;

        for (char ch : s)
        {
            if (isdigit(ch))
                n = n * 10 + (ch - '0');
            else if (ch == '[')
            {
                strs.push(ret);
                ret = "";
                nums.push(n);
                n = 0;
            }
            else if (ch == ']')
            {
                string tmp = strs.top();
                strs.pop();
                int k = nums.top();
                nums.pop();
                while (k--)
                    tmp += ret;

                ret = tmp;
            }
            else
                ret += ch;
        }

        return ret;
    }

    // 3
    unordered_map<char, int> in;
    unordered_map<char, unordered_set<char>> edges;
    bool check;
    string alienOrder(vector<string> &words)
    {
        int n = words.size();
        for (auto &word : words)
            for (char ch : word)
                in[ch] = 0;

        for (int i = 1; i < n; i++)
            for (int j = 0; j < i; j++)
            {
                add(words[j], words[i]);

                if (check)
                    return "";
            }

        queue<char> q;
        for (auto [a, b] : in)
            if (b == 0)
                q.push(a);

        string ret;
        while (q.size())
        {
            auto a = q.front();
            q.pop();
            ret += a;

            for (auto t : edges[a])
                if (--in[t] == 0)
                    q.push(t);
        }

        for (auto [a, b] : in)
            if (b)
                return "";

        return ret;
    }

    void add(const string &s1, const string &s2)
    {
        int i = 0, n = min(s1.size(), s2.size());

        for (; i < n; i++)
        {
            if (s1[i] != s2[i])
            {
                char a = s1[i], b = s2[i];
                // a->b;
                if (!edges.count(a) || !edges[a].count(b))
                {
                    edges[a].insert(b);
                    in[b]++;
                }
                break;
            }
        }

        // abc ab
        if (i < s1.size() && i == s2.size())
            check = true;
    }

    // 4
    int minimumDeleteSum(string s1, string s2)
    {
        int m = s1.size(), n = s2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                if (s1[i - 1] == s2[j - 1])
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + s1[i - 1]);
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }

        int sum = 0;
        for (char ch : s1)
            sum += ch;
        for (char ch : s2)
            sum += ch;

        return sum - 2 * dp[m][n];
    }

    // 5
    // ThreadPool

    // 6
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

    // 7
    vector<int> intersection(vector<int> &nums1, vector<int> &nums2)
    {
        int hash[1001] = {0};

        for (auto n : nums1)
            if (hash[n] == 0)
                hash[n]++;

        vector<int> ret;
        for (auto n : nums2)
            if (hash[n]-- > 0)
                ret.push_back(n);

        return ret;
    }

    // 8
    // Softmax
};