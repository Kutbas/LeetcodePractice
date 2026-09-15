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
    int mySqrt(int x)
    {
        long long left = 0, right = x;

        while (left < right)
        {
            long long mid = left + (right - left + 1) / 2;
            if (mid * mid <= x)
                left = mid;
            else
                right = mid - 1;
        }

        return left;
    }

    // 2
    string removeDuplicates(string s)
    {
        string ret = "";

        for (int i = 0; i < s.size();)
        {

            if (ret.size() && s[i] == ret.back())
            {
                ret.pop_back();
                i++;
            }
            else
                ret += s[i++];
        }

        return ret;
    }

    // 3
    int monotoneIncreasingDigits(int n)
    {
        string s = to_string(n);

        int i = 0, m = s.size();
        while (i + 1 < m && s[i] <= s[i + 1])
            i++;

        if (i + 1 == m)
            return n;

        while (i - 1 >= 0 && s[i] == s[i - 1])
            i--;

        s[i]--;
        for (int j = i + 1; j < m; j++)
            s[j] = '9';

        return stoi(s);
    }

    // 4
    int maxProfit(vector<int> &prices)
    {
        const int INF = 0x3f3f3f;
        int n = prices.size();
        vector<vector<int>> f(n, vector<int>(3, -INF));
        auto g = f;

        f[0][0] = -prices[0];
        g[0][0] = 0;

        for (int i = 1; i < n; i++)
            for (int j = 0; j < 3; j++)
            {
                f[i][j] = max(f[i - 1][j], g[i - 1][j] - prices[i]);
                g[i][j] = g[i - 1][j];
                if (j >= 1)
                    g[i][j] = max(g[i][j], f[i - 1][j - 1] + prices[i]);
            }

        return max(g[n - 1][0], max(g[n - 1][1], g[n - 1][2]));
    }

    // 5
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
                    {
                        dp[i] = min(dp[i], dp[j - 1] + 1);
                        // break;
                    }
                }
            }
        }

        return dp[n - 1];
    }

    // 6
    class MyQueue
    {
    private:
        stack<int> in, out;

        void in2out()
        {
            while (in.size())
            {
                out.push(in.top());
                in.pop();
            }
        }

    public:
        MyQueue() {}

        void push(int x) { in.push(x); }

        int pop()
        {
            if (out.empty())
                in2out();

            int r = out.top();
            out.pop();

            return r;
        }

        int peek()
        {
            if (out.empty())
                in2out();
            int r = out.top();
            return r;
        }

        bool empty() { return in.empty() && out.empty(); }
    };
};