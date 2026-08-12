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
    void sortColors(vector<int> &nums)
    {
        int n = nums.size(), i = 0, left = -1, right = n;
        while (i < right)
        {
            if (nums[i] < 1)
                swap(nums[i++], nums[++left]);
            else if (nums[i] == 1)
                i++;
            else
                swap(nums[i], nums[--right]);
        }
    }

    // 2
    int minFallingPathSum(vector<vector<int>> &matrix)
    {
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 2, INT_MAX));

        for (int i = 0; i < n + 2; i++)
            dp[0][i] = 0;

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                dp[i][j] = min(dp[i - 1][j], min(dp[i - 1][j - 1], dp[i - 1][j + 1])) + matrix[i - 1][j - 1];

        int ret = INT_MAX;
        for (int i = 1; i <= n; i++)
            ret = min(ret, dp[m][i]);

        return ret;
    }

    // 3
    int numDistinct(string s, string t)
    {
        int m = t.size(), n = s.size();
        vector<vector<double>> dp(m + 1, vector<double>(n + 1));
        s = " " + s, t = " " + t;

        for (int i = 0; i <= n; i++)
            dp[0][i] = 1;

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                dp[i][j] += dp[i][j - 1];
                if (t[i] == s[j])
                    dp[i][j] += dp[i - 1][j - 1];
            }

        return dp[m][n];
    }

    // 4
    vector<string> uncommonFromSentences(string s1, string s2)
    {
        unordered_map<string, int> hash;

        auto countWords = [&](const string s)
        {
            istringstream iss(s);
            string word;

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

    // 5
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
};