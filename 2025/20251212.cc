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
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        ListNode *ret = new ListNode(0);
        ListNode *prev = ret;
        ListNode *cur1 = l1, *cur2 = l2;
        int t = 0;

        while (cur1 || cur2 || t)
        {
            if (cur1)
            {
                t += cur1->val;
                cur1 = cur1->next;
            }
            if (cur2)
            {
                t += cur2->val;
                cur2 = cur2->next;
            }
            prev->next = new ListNode(t % 10);
            prev = prev->next;
            t /= 10;
        }

        prev = ret->next;
        delete ret;
        return prev;
    }

    // 2
    string optimalDivision(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 1)
            return to_string(nums[0]);
        if (n == 2)
            return to_string(nums[0]) + "/" + to_string(nums[1]);

        string ret = to_string(nums[0]) + "/(" + to_string(nums[1]);
        for (int i = 2; i < n; i++)
            ret += "/" + to_string(nums[i]);
        ret += ")";

        return ret;
    }

    // 3
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

    // 4
    int numDecodings(string s)
    {
        int n = s.size();

        vector<int> dp(n);
        dp[0] = s[0] == '0' ? 0 : 1;
        if (n == 1)
            return dp[0];

        if (s[0] != '0' && s[1] != '0')
            dp[1] += 1;

        int twoDigits = (s[0] - '0') * 10 + (s[1] - '0');
        if (twoDigits >= 10 && twoDigits <= 26)
            dp[1] += 1;

        for (int i = 2; i < n; i++)
        {
            if (s[i] != '0')
                dp[i] += dp[i - 1];

            int twoDigits = (s[i - 1] - '0') * 10 + (s[i] - '0');
            if (twoDigits >= 10 && twoDigits <= 26)
                dp[i] += dp[i - 2];
        }

        return dp[n - 1];
    }

    // 5
    int findNumberOfLIS(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> longestLen(n, 1);
        vector<int> ways(n, 1);
        int globalLongestLen = 1;
        int globalWays = 1;

        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (nums[j] < nums[i])
                {
                    int newlen = longestLen[j] + 1;
                    if (newlen == longestLen[i])
                        ways[i] += ways[j];
                    else if (newlen > longestLen[i])
                    {
                        longestLen[i] = newlen;
                        ways[i] = ways[j];
                    }
                }
            }

            if (longestLen[i] == globalLongestLen)
                globalWays += ways[i];
            else if (longestLen[i] > globalLongestLen)
            {
                globalLongestLen = longestLen[i];
                globalWays = ways[i];
            }
        }

        return globalWays;
    }

    // 6
    int ret = 0, N;
    bool vis[16];
    int countArrangement(int n)
    {
        N = n;
        dfs(1);
        return ret;
    }

    void dfs(int pos)
    {
        if (pos == N + 1)
        {
            ret++;
            return;
        }

        for (int i = 1; i <= N; i++)
        {
            if (!vis[i] && (i % pos == 0 || pos % i == 0))
            {
                vis[i] = true;
                dfs(pos + 1);
                vis[i] = false;
            }
        }
    }

    // 7
    bool evaluateTree(TreeNode *root)
    {
        if (root->left == nullptr && root->right == nullptr)
            return root->val == 0 ? false : true;

        bool left = evaluateTree(root->left);
        bool right = evaluateTree(root->right);

        return root->val == 2 ? (left | right) : (left & right);
    }
};