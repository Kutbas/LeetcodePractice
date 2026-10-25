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
            int x = a ^ b;
            int carry = (a & b) << 1;
            a = x;
            b = carry;
        }
        return a;
    }

    // 2
    class MedianFinder
    {
    private:
        priority_queue<int> left;
        priority_queue<int, vector<int>, greater<int>> right;

    public:
        MedianFinder()
        {
        }

        void addNum(int num)
        {
            if (left.size() == right.size())
            {
                if (left.empty() || num < left.top())
                    left.push(num);
                else
                {
                    right.push(num);
                    left.push(right.top());
                    right.pop();
                }
            }
            else
            {
                if (num >= left.top())
                    right.push(num);
                else
                {
                    left.push(num);
                    right.push(left.top());
                    left.pop();
                }
            }
        }

        double findMedian()
        {
            return left.size() > right.size() ? left.top() : (left.top() + right.top()) / 2.0;
        }
    };

    // 3
    bool lemonadeChange(vector<int> &bills)
    {
        int n = bills.size();

        int hash[20] = {0};
        for (auto n : bills)
        {
            if (n == 5)
                hash[5]++;
            else if (n == 10)
            {
                if (!hash[5])
                    return false;
                hash[5]--, hash[10]++;
            }
            else
            {
                if (hash[5] && hash[10])
                    hash[5]--, hash[10]--;
                else if (hash[5] >= 3)
                    hash[5] -= 3;
                else
                    return false;
            }
        }

        return true;
    }

    // 4
    int findContentChildren(vector<int> &g, vector<int> &s)
    {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());

        int m = g.size(), n = s.size(), ret = 0;
        for (int i = 0, j = 0; i < m && j < n; i++, j++)
        {
            while (j < n && s[j] < g[i])
                j++;

            // if(j==n)
            //     break;

            if (j < n)
                ret++;
        }

        return ret;
    }

    // 5
    string reorganizeString(string s)
    {
        int n = s.size(), maxCount = 0;
        char maxChar = '/0';
        unordered_map<char, int> hash;

        for (char ch : s)
            if (++hash[ch] > maxCount)
            {
                maxChar = ch;
                maxCount = hash[ch];
            }

        string ret;
        ret.append(n, '.');
        int index = 0;
        for (int i = 0; i < maxCount; i++)
        {
            if (index > n - 1)
                return "";

            ret[index] = maxChar;
            index += 2;
        }

        hash.erase(maxChar);

        for (auto [a, b] : hash)
            for (int i = 0; i < b; i++)
            {
                if (index >= n)
                    index = 1;

                ret[index] = a;
                index += 2;
            }

        for (char ch : ret)
            if (ch == '.')
                return "";

        return ret;
    }

    // 6
    vector<vector<int>> merge(vector<vector<int>> &intervals)
    {
        sort(intervals.begin(), intervals.end());
        int n = intervals.size(), left = intervals[0][0], right = intervals[0][1];
        vector<vector<int>> ret;

        for (int i = 1; i < n; i++)
        {
            int a = intervals[i][0], b = intervals[i][1];

            if (right >= a)
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

    // 7
    int eraseOverlapIntervals(vector<vector<int>> &intervals)
    {
        sort(intervals.begin(), intervals.end());

        int n = intervals.size(), right = intervals[0][1], ret = 0;
        for (int i = 1; i < n; i++)
        {
            int a = intervals[i][0], b = intervals[i][1];

            if (right > a)
            {
                ret++;
                right = min(right, b);
            }
            else
                right = b;
        }

        return ret;
    }

    // 8
    class Singleton
    {
    public:
        static Singleton &getInstance()
        {
            static Singleton instance;
            return instance;
        }

        Singleton(const Singleton &) = delete;
        Singleton &operator=(const Singleton &) = delete;

        void doSomething()
        {
            cout << "check!" << endl;
        }

    private:
        Singleton() = default;
        ~Singleton() = default;
    };

    // 9
    int findSubstringInWraproundString(string s)
    {
        int n = s.size();

        vector<int> dp(n + 1, 1);
        // s=" "+s;

        for (int i = 1; i <= n; i++)
            if ((s[i - 1] == 'z' && s[i] == 'a') || s[i - 1] + 1 == s[i])
                dp[i] += dp[i - 1];

        int hash[26] = {0};
        for (int i = 0; i < n; i++)
        {
            int index = s[i] - 'a';
            hash[index] = max(hash[index], dp[i]);
        }

        int ret = 0;
        for (auto i : hash)
            ret += i;

        return ret;
    }

    // 10
    int lenLongestFibSubseq(vector<int> &arr)
    {
        int n = arr.size();
        unordered_map<int, int> hash;

        for (int i = 0; i < n; i++)
            hash[arr[i]] = i;

        int ret = 2;
        vector<vector<int>> dp(n, vector<int>(n, 2));

        for (int j = 2; j < n; j++)
            for (int i = 1; i < j; i++)
            {
                int a = arr[j] - arr[i];

                if (a < arr[i] && hash.count(a))
                    dp[i][j] = dp[hash[a]][i] + 1;
                ret = max(ret, dp[i][j]);
            }

        return ret < 3 ? 0 : ret;
    }
};