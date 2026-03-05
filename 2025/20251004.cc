#include <bits/stdc++.h>
#include <mutex>
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
    int longestSubsequence(vector<int> &arr, int difference)
    {
        unordered_map<int, int> hash;
        hash[arr[0]] = 1;

        int ret = 1;
        for (int i = 1; i < arr.size(); i++)
        {
            hash[arr[i]] = hash[arr[i] - difference] + 1;
            ret = max(ret, hash[arr[i]]);
        }

        return ret;
    }

    int lenLongestFibSubseq(vector<int> &arr)
    {
        int n = arr.size();

        unordered_map<int, int> hash;
        for (int i = 0; i < n; i++)
            hash[arr[i]] = i;

        int ret = 2;
        vector<vector<int>> dp(n, vector<int>(n, 2));
        for (int j = 2; j < n; j++) // 固定最后一个位置
        {
            for (int i = 1; i < j; i++) // 固定倒数第二个位置
            {
                int a = arr[j] - arr[i];
                if (hash.count(a) && a < arr[i])
                    dp[i][j] = dp[hash[a]][i] + 1;
                ret = max(ret, dp[i][j]);
            }
        }
        return ret < 3 ? 0 : ret;
    }

    // 1
    bool increasingTriplet(vector<int> &nums)
    {
        int a = nums[0], b = INT_MAX;
        for (int i = 1; i < nums.size(); i++)
        {
            if (nums[i] > b)
                return true;
            else if (nums[i] > a)
                b = nums[i];
            else
                a = nums[i];
        }
        return false;
    }

    // 2
    int lengthOfLIS(vector<int> &nums)
    {
        vector<int> ret;
        ret.push_back(nums[0]);

        for (int i = 1; i < nums.size(); i++)
        {
            if (nums[i] > ret.back())
                ret.push_back(nums[i]);
            else
            {
                int left = 0, right = ret.size() - 1;
                while (left < right)
                {
                    int mid = left + (right - left) / 2;
                    if (nums[i] > ret[mid])
                        left = mid + 1;
                    else
                        right = mid;
                }
                ret[left] = nums[i];
            }
        }

        return ret.size();
    }

    // 3
    int maxProfit(vector<int> &prices)
    {
        int ret = 0, n = prices.size();

        for (int i = 0; i < n; i++)
        {
            int j = i;
            while (j + 1 < n && prices[j + 1] > prices[j])
                j++;

            ret += prices[j] - prices[i];
            i = j;
        }

        return ret;
    }

    // 4
    int wiggleMaxLength(vector<int> &nums)
    {
        int n = nums.size();
        if (n < 2)
            return n;

        int ret = 0, left = 0;
        for (int i = 0; i < n - 1; i++)
        {
            int right = nums[i + 1] - nums[i];
            if (right == 0)
                continue;
            if (right * left <= 0)
                ret++;
            left = right;
        }

        return ret + 1;
    }

    // 5
    string longestPalindrome(string s)
    {
        int n = s.size();
        vector<vector<bool>> dp(n, vector<bool>(n));

        for (int i = 0; i < n; i++)
            dp[i][i] = true;

        int begin = 0, maxlen = 1;
        for (int i = 0; i < n; i++)
        {
            for (int L = 2; L <= n; L++)
            {
                int j = i + L - 1;
                if (j >= n)
                    break;

                if (s[i] != s[j])
                    dp[i][j] = false;
                else
                {
                    if (L == 2)
                        dp[i][j] = true;
                    else
                        dp[i][j] = dp[i + 1][j - 1];
                }

                if (dp[i][j] && j - i + 1 > maxlen)
                {
                    begin = i;
                    maxlen = j - i + 1;
                }
            }
        }

        return s.substr(begin, maxlen);
    }

    // 6
    vector<string> ret;
    string path;
    int left = 0, right = 0;
    vector<string> generateParenthesis(int n)
    {
        dfs(n);
        return ret;
    }

    void dfs(int n)
    {
        if (right == n)
        {
            ret.push_back(path);
            return;
        }

        if (left < n)
        {
            path.push_back('(');
            left++;
            dfs(n);
            left--;
            path.pop_back();
        }

        if (right < left)
        {
            path.push_back(')');
            right++;
            dfs(n);
            right--;
            path.pop_back();
        }
    }
};