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
    double myPow(double x, int n)
    {
        long N = n;

        if (N < 0)
        {
            x = 1 / x;
            N = -N;
        }

        return pow(x, N);
    }

    double pow(double x, long n)
    {
        if (n == 0)
            return 1;

        double tmp = pow(x, n / 2);

        return n % 2 == 1 ? tmp * tmp * x : tmp * tmp;
    }

    // 2
    int halveArray(vector<int> &nums)
    {
        priority_queue<double> q;
        double sum = 0, ret = 0;

        for (auto n : nums)
        {
            q.push(n);
            sum += n;
        }

        double aim = sum / 2.0;

        while (sum > aim)
        {
            auto t = q.top() / 2.0;
            q.pop();

            ret++;
            sum -= t;
            q.push(t);
        }

        return ret;
    }

    // 3
    int minCost(vector<vector<int>> &costs)
    {
        int n = costs.size();
        vector<vector<int>> dp(n + 1, vector<int>(3));

        for (int i = 1; i <= n; i++)
        {
            dp[i][0] = min(dp[i - 1][1], dp[i - 1][2]) + costs[i - 1][0];
            dp[i][1] = min(dp[i - 1][0], dp[i - 1][2]) + costs[i - 1][1];
            dp[i][2] = min(dp[i - 1][1], dp[i - 1][0]) + costs[i - 1][2];
        }

        return min(dp[n][0], min(dp[n][1], dp[n][2]));
    }

    // 4
    bool checkPartitioning(string s)
    {
        int n = s.size();
        vector<vector<bool>> isPal(n, vector<bool>(n));

        for (int i = n - 1; i >= 0; i--)
            for (int j = i; j < n; j++)
                if (s[i] == s[j])
                    isPal[i][j] = j - i + 1 > 3 ? isPal[i + 1][j - 1] : true;

        for (int i = 1; i < n - 1; i++)
            for (int j = i; j < n - 1; j++)
                if (isPal[0][i - 1] && isPal[i][j] && isPal[j + 1][n - 1])
                    return true;

        return false;
    }

    // 5
    vector<string> uncommonFromSentences(string s1, string s2)
    {
        unordered_map<string, int> hash;

        auto wordCount = [&](const string &s)
        {
            istringstream iss(s);
            string word;

            while (iss >> word)
                hash[word]++;
        };

        wordCount(s1);
        wordCount(s2);

        vector<string> ret;
        for (auto [a, b] : hash)
            if (b == 1)
                ret.push_back(a);

        return ret;
    }

    // 6
    int removeDuplicates(vector<int> &nums)
    {
        int n = nums.size(), slow = 1, fast = 1;

        while (fast < n)
        {
            if (nums[fast - 1] != nums[fast])
                nums[slow++] = nums[fast];
            fast++;
        }

        return slow;
    }

    // 7
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