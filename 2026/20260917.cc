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
    int singleNumber(vector<int> &nums)
    {
        int ret = 0;

        for (int i = 0; i < 32; i++)
        {
            int count = 0;
            for (auto n : nums)
                if ((n >> i) & 1)
                    count++;

            if (count % 3 == 1)
                ret |= 1 << i;
        }

        return ret;
    }

    // 2
    class KthLargest
    {
        priority_queue<int, vector<int>, greater<int>> q;
        int _k;

    public:
        KthLargest(int k, vector<int> &nums) : _k(k)
        {

            for (auto n : nums)
            {
                q.push(n);
                if (q.size() > _k)
                    q.pop();
            }
        }

        int add(int val)
        {
            q.push(val);
            if (q.size() > _k)
                q.pop();

            return q.top();
        }
    };

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
        int n = prices.size();
        vector<int> f(n);
        auto g = f, k = f;
        f[0] = -prices[0];

        for (int i = 1; i < n; i++)
        {
            f[i] = max(f[i - 1], g[i - 1] - prices[i]);
            g[i] = max(g[i - 1], k[i - 1]);
            k[i] = f[i - 1] + prices[i];
        }

        return max(g[n - 1], k[n - 1]);
    }

    // 5
    int maxProfit(int k, vector<int> &prices)
    {
        const int INF = 0x3f3f3f;
        int n = prices.size();
        vector<vector<int>> f(n, vector<int>(k + 1, -INF));
        auto g = f;
        f[0][0] = -prices[0];
        g[0][0] = 0;

        for (int i = 1; i < n; i++)
            for (int j = 0; j <= k; j++)
            {
                f[i][j] = max(f[i - 1][j], g[i - 1][j] - prices[i]);
                g[i][j] = g[i - 1][j];
                if (j >= 1)
                    g[i][j] = max(g[i][j], f[i - 1][j - 1] + prices[i]);
            }

        int ret = 0;
        for (int i = 0; i <= k; i++)
            ret = max(ret, g[n - 1][i]);

        return ret;
    }

    // 6
    vector<string> uncommonFromSentences(string s1, string s2)
    {
        unordered_map<string, int> hash;

        auto countWords = [&](string s)
        {
            string word;
            istringstream iss(s);

            while (iss >> word)
                hash[word]++;
        };

        countWords(s1);
        countWords(s2);

        vector<string> ret;
        for (auto [a, b] : hash)
            if (b == 1)
                ret.push_back(a);

        return ret;
    }

    // 7
    class MyStack
    {
    private:
        queue<int> q;

    public:
        MyStack() {}

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

        bool empty() { return q.empty(); }
    };

    // 8
    int getMaxLen(vector<int> &nums)
    {
        int n = nums.size();

        vector<int> f(n + 1);
        auto g = f;

        int ret = INT_MIN;
        for (int i = 1; i <= n; i++)
        {
            if (nums[i - 1] > 0)
            {
                f[i] = f[i - 1] + 1;
                g[i] = g[i - 1] == 0 ? 0 : g[i - 1] + 1;
            }
            else if (nums[i - 1] < 0)
            {
                f[i] = g[i - 1] == 0 ? 0 : g[i - 1] + 1;
                g[i] = f[i - 1] + 1;
            }
            ret = max(ret, f[i]);
        }

        return ret;
    }
};