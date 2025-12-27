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
    // 1
    int findSubstringInWraproundString(string s)
    {
        int n = s.size();

        vector<int> dp(n, 1);
        for (int i = 1; i < n; i++)
            if (s[i - 1] + 1 == s[i] || (s[i - 1] == 'z' && s[i] == 'a'))
                dp[i] += dp[i - 1];

        int hash[26] = {0};
        for (int i = 0; i < n; i++)
        {
            int index = s[i] - 'a';
            hash[index] = max(hash[index], dp[i]);
        }

        int sum = 0;
        for (int i = 0; i < 26; i++)
            sum += hash[i];

        return sum;
    }

    // 2
    int minNumberOfFrogs(string croakOfFrogs)
    {
        string s = "croak";
        int n = s.size();
        unordered_map<char, int> hash;

        for (int i = 0; i < n; i++)
            hash[s[i]] = i;

        vector<int> count(n);
        for (char ch : croakOfFrogs)
        {
            if (ch == 'c')
            {
                if (count[n - 1])
                    count[n - 1]--;
                count[0]++;
            }
            else
            {
                int i = hash[ch];
                if (count[i - 1] == 0)
                    return -1;

                count[i - 1]--;
                count[i]++;
            }
        }

        for (int i = 0; i < n - 1; i++)
            if (count[i])
                return -1;
        return count[n - 1];
    }

    // 3
    int maxArea(vector<int> &height)
    {
        int ret = 0, n = height.size();
        int left = 0, right = n - 1;

        while (left < right)
        {
            int v = (right - left) * min(height[left], height[right]);
            ret = max(ret, v);

            if (height[left] < height[right])
                left++;
            else
                right--;
        }

        return ret;
    }
};