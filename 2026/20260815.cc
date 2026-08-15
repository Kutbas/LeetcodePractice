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
    int brokenCalc(int startValue, int target)
    {
        int ret = 0;
        while (target > startValue)
        {
            if (target % 2 == 0)
                target /= 2;
            else
                target++;
            ret++;
        }

        return ret + startValue - target;
    }

    // 2
    int minimumDeleteSum(string s1, string s2)
    {
        int m = s1.size(), n = s2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                if (s1[i - 1] == s2[j - 1])
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + s1[i - 1]);
            }

        int sum = 0;
        for (char ch : s1)
            sum += ch;
        for (char ch : s2)
            sum += ch;

        return sum - 2 * dp[m][n];
    }

    // 3
    int removeDuplicates(vector<int> &nums)
    {
        int n = nums.size(), slow = 1, fast = 1;

        while (fast < n)
        {
            if (nums[fast] != nums[fast - 1])
                nums[slow++] = nums[fast];
            fast++;
        }

        return slow;
    }

    // 4
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

    // 5
    vector<string> uncommonFromSentences(string s1, string s2)
    {
        unordered_map<string, int> hash;

        auto countWords = [&](const string &s)
        {
            istringstream is(s);
            string word;
            while (is >> word)
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
};