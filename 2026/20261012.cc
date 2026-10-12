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
    string minWindow(string s, string t)
    {
        int begin = -1, minlen = INT_MAX;
        int m = t.size(), n = s.size();
        unordered_map<char, int> hash1, hash2;
        for (char ch : t)
            hash1[ch]++;

        for (int left = 0, right = 0, count = 0; right < n; right++)
        {
            char in = s[right];
            if (++hash2[in] <= hash1[in])
                count++;
            while (count == m)
            {
                if (right - left + 1 < minlen)
                {
                    begin = left;
                    minlen = right - left + 1;
                }
                char out = s[left++];
                if (hash2[out]-- <= hash1[out])
                    count--;
            }
        }
        return begin == -1 ? "" : s.substr(begin, minlen);
    }

    // 2
    vector<vector<int>> ret;
    vector<int> path;
    vector<vector<int>> subsets(vector<int> &nums)
    {
        dfs(nums, 0);
        return ret;
    }

    void dfs(vector<int> &nums, int pos)
    {
        ret.push_back(path);

        if (pos == nums.size())
            return;

        for (int i = pos; i < nums.size(); i++)
        {
            path.push_back(nums[i]);
            dfs(nums, i + 1);
            path.pop_back();
        }
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
    class MinStack
    {
    private:
        long minElem;
        stack<long> st;

    public:
        MinStack()
        {
        }

        void push(int value)
        {
            if (st.empty())
            {
                st.push(0);
                minElem = value;
            }
            else
            {
                long diff = value - minElem;
                st.push(diff);

                if (diff < 0)
                    minElem = value;
            }
        }

        void pop()
        {
            long t = st.top();
            st.pop();

            if (t < 0)
                minElem = minElem - t;
        }

        int top()
        {
            long t = st.top();

            if (t > 0)
                return minElem + t;
            return minElem;
        }

        int getMin()
        {
            return minElem;
        }
    };
};