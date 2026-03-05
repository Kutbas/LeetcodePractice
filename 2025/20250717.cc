#include <bits/stdc++.h>
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
    string modifyString(string s)
    {
        string ret;
        int n = s.size();
        for (int i = 0; i < n; i++)
        {
            if (s[i] == '?')
            {
                for (char ch = 'a'; ch <= 'z'; ch++)
                {
                    if ((i == 0 || s[i - 1] != ch) && (s[i + 1] != ch || i == n - 1))
                        s[i] = ch;
                }
            }
        }

        return ret;
    }

    string longestPalindrome(string s)
    {
        int n = s.size(), begin = 0, maxlen = 1;
        vector<vector<bool>> dp(n, vector<bool>(n));
        for (int i = 0; i < n; i++)
            dp[i][i] = true;

        for (int i = 0; i < n; i++)
        {
            for (int L = 2; L <= n; L++)
            {
                int j = i + L - 1;
                if (j >= n)
                    break;

                if (s[i] == s[j])
                {
                    if (L == 2)
                        dp[i][j] = true;
                    else
                        dp[i][j] = dp[i + 1][j - 1];
                }

                if (j - i + 1 > maxlen && dp[i][j])
                {
                    begin = i;
                    maxlen = j - i + 1;
                }
            }
        }

        return s.substr(begin, maxlen);
    }

    int findMin(vector<int> &nums)
    {
        int left = 0, right = nums.size() - 1;
        while (left < right)
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] > nums[mid - 1])
                left = mid + 1;
            else
                right = mid;
        }
        return nums[left];
    }

    int subarraysDivByK(vector<int> &nums, int k)
    {
        unordered_map<int, int> hash;
        hash[0] = 1;
        int ret = 0, sum = 0;

        for (auto n : nums)
        {
            sum += n;
            int r = (sum % k + k) % k;
            if (hash.count(r))
                ret += hash[r];
            hash[r]++;
        }

        return ret;
    }

    int singleNumber(vector<int> &nums)
    {
        int ret = 0;
        for (int i = 0; i < 32; i++)
        {
            int count = 0;
            for (auto n : nums)
                if ((n >> i) & 1)
                    count++;

            count %= 3;
            if (count)
                ret |= 1 << i;
        }

        return ret;
    }

    int missingNumber(vector<int> &nums)
    {
        int ret = 0, n = nums.size();
        for (auto n : nums)
            ret ^= n;
        for (int i = 1; i <= n; i++)
            ret ^= i;

        return ret;
    }
};