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
    vector<int> singleNumber(vector<int> &nums)
    {
        int xorsum = 0;
        for (auto n : nums)
            xorsum ^= n;

        int lsb = xorsum == INT_MIN ? xorsum : (xorsum & -xorsum);
        int x = 0, y = 0;

        for (auto n : nums)
        {
            if (n & lsb)
                x ^= n;
            else
                y ^= n;
        }

        return {x, y};
    }

    // 2
    int calculate(string s)
    {
        int n = s.size();
        char op = '+';

        vector<int> nums;

        for (int i = 0; i < n;)
        {
            if (s[i] == ' ')
            {
                i++;
                continue;
            }
            else if (isdigit(s[i]))
            {
                int num = 0;
                while (isdigit(s[i]) && i < n)
                {
                    num = num * 10 + (s[i] - '0');
                    i++;
                }

                if (op == '+')
                    nums.push_back(num);
                else if (op == '-')
                    nums.push_back(-num);
                else if (op == '*')
                    nums.back() *= num;
                else
                    nums.back() /= num;
            }
            else
                op = s[i++];
        }

        int sum = 0;
        for (auto n : nums)
            sum += n;

        return sum;
    }

    // 3
    unordered_map<char, int> in;
    unordered_map<char, unordered_set<char>> edges;
    bool check = false;
    string alienOrder(vector<string> &words)
    {
        for (auto &word : words)
            for (auto &ch : word)
                in[ch] = 0;

        int n = words.size();
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
            {
                add(words[i], words[j]);

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
            auto t = q.front();
            q.pop();
            ret += t;

            for (auto a : edges[t])
                if (--in[a] == 0)
                    q.push(a);
        }

        for (auto &[a, b] : in)
            if (b)
                return "";

        return ret;
    }

    void add(const string &s1, const string &s2)
    {
        int n = min(s1.size(), s2.size()), i = 0;

        for (; i < n; i++)
        {
            if (s1[i] != s2[i])
            {
                char a = s1[i], b = s2[i]; // a->b
                if (!edges.count(a) || !edges[a].count(b))
                {
                    in[b]++;
                    edges[a].insert(b);
                }

                break;
            }
        }

        if (i < s1.size() && i == s2.size())
            check = true;
    }

    // 4
    int deleteAndEarn(vector<int> &nums)
    {
        const int N = 10001;
        int arr[N] = {0};

        for (auto n : nums)
            arr[n] += n;

        vector<int> f(N), g(N);
        for (int i = 1; i < N; i++)
        {
            f[i] = g[i - 1] + arr[i];
            g[i] = max(f[i - 1], g[i - 1]);
        }

        return max(f[N - 1], g[N - 1]);
    }

    // 5
    bool wordBreak(string s, vector<string> &wordDict)
    {
        unordered_set<string> hash(wordDict.begin(), wordDict.end());
        int n = s.size();

        vector<bool> dp(n + 1);
        dp[0] = true;
        s = " " + s;

        for (int i = 1; i <= n; i++)
            for (int j = i; j >= 1; j--)
            {
                if (dp[j - 1] && hash.count(s.substr(j, i - j + 1)))
                    dp[i] = true;
                // break;
            }

        return dp[n];
    }

    // 6
    int longestPalindromeSubseq(string s)
    {
        int n = s.size();

        // s=" "+s;
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

    // 7
    vector<int> intersection(vector<int> &nums1, vector<int> &nums2)
    {
        int hash[1001] = {0};
        vector<int> ret;

        for (auto n : nums1)
            if (hash[n] == 0)
                ++hash[n];
        for (auto n : nums2)
            if (--hash[n] == 0)
                ret.push_back(n);

        return ret;
    }
};