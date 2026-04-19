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
    string longestCommonPrefix(vector<string> &strs)
    {
        for (int i = 0; i < strs[0].size(); i++)
            for (int j = 1; j < strs.size(); j++)
                if (i == strs[j].size() || strs[0][i] != strs[j][i])
                    return strs[0].substr(0, i);
        return strs[0];
    }

    // 2
    ListNode *reverseList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *newhead = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;

        return newhead;
    }

    // 3
    int brokenCalc(int startValue, int target)
    {
        int count = 0;
        while (target > startValue)
        {
            if (target % 2 == 0)
                target /= 2;
            else
                target++;
            count++;
        }
        return startValue - target + count;
    }

    // 4
    vector<int> twoSum(vector<int> &price, int target)
    {
        unordered_map<int, int> hash;
        for (int i = 0; i < price.size(); i++)
        {
            int x = target - price[i];
            if (hash.count(x))
                return {price[i], price[hash[x]]};
            hash[price[i]] = i;
        }
        return {-1, -1};
    }

    // 5
    string decodeString(string s)
    {
        stack<int> nums;
        int num = 0;
        stack<string> st;
        string ret;

        for (char ch : s)
        {
            if (isdigit(ch))
                num = num * 10 + (ch - '0');
            else if (ch == '[')
            {
                nums.push(num);
                num = 0;
                st.push(ret);
                ret = "";
            }
            else if (ch == ']')
            {
                int k = nums.top();
                nums.pop();
                string tmp = st.top();
                st.pop();
                while (k--)
                    tmp += ret;
                ret = tmp;
            }
            else
                ret += ch;
        }
        return ret;
    }

    // 6
    bool isInterleave(string s1, string s2, string s3)
    {
        int m = s1.size(), n = s2.size();
        if (m + n != s3.size())
            return false;

        s1 = " " + s1;
        s2 = " " + s2;
        s3 = " " + s3;
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1));
        dp[0][0] = true;
        for (int i = 1; i <= m; i++)
            if (s1[i] == s3[i])
                dp[i][0] = true;
            else
                break;

        for (int i = 1; i <= n; i++)
            if (s2[i] == s3[i])
                dp[0][i] = true;
            else
                break;

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                bool from_s1 = s1[i] == s3[i + j] && dp[i - 1][j];
                bool from_s2 = s2[j] == s3[i + j] && dp[i][j - 1];
                dp[i][j] = from_s1 || from_s2;
            }

        return dp[m][n];
    }

    // 7
    int findNumberOfLIS(vector<int> &nums)
    {
        int n = nums.size();
        int globalLongestLen = 1;
        int globalWays = 1;
        vector<int> longestLen(n, 1);
        vector<int> ways(n, 1);

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
            if (globalLongestLen == longestLen[i])
                globalWays += ways[i];
            if (globalLongestLen < longestLen[i])
            {
                globalLongestLen = longestLen[i];
                globalWays = ways[i];
            }
        }

        return globalWays;
    }

    // 8
    vector<TreeNode *> TreeList;

    void Inorder(TreeNode *root)
    {
        if (root == nullptr)
            return;

        Inorder(root->left);
        TreeList.push_back(root);
        Inorder(root->right);
    }

    TreeNode *Convert(TreeNode *pRootOfTree)
    {
        if (pRootOfTree == nullptr)
            return nullptr;

        Inorder(pRootOfTree);

        for (int i = 1; i < TreeList.size(); i++)
        {
            TreeList[i]->left = TreeList[i - 1];
            TreeList[i - 1]->right = TreeList[i];
        }

        return TreeList[0];
    }
};