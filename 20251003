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
    int findNumberOfLIS(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> len(n, 1), count(n, 1);

        int retlen = 1, retcount = 1;
        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (nums[j] < nums[i])
                {
                    if (len[j] + 1 == len[i])
                        count[i] += count[j];
                    else if (len[j] + 1 > len[i])
                    {
                        len[i] = len[j] + 1;
                        count[i] = count[j];
                    }
                }
            }
            if (retlen == len[i])
                retcount += count[i];
            else if (retlen < len[i])
                retlen = len[i], retcount = count[i];
        }

        return retcount;
    }

    int findLongestChain(vector<vector<int>> &pairs)
    {
        sort(pairs.begin(), pairs.end());
        int n = pairs.size();

        vector<int> dp(n, 1);
        int ret = 1;
        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (pairs[j][1] < pairs[i][0])
                    dp[i] = max(dp[j] + 1, dp[i]);
            }
            ret = max(ret, dp[i]);
        }

        return ret;
    }

    // 1
    bool evaluateTree(TreeNode *root)
    {
        if (root->left == nullptr && root->right == nullptr)
            return root->val == 1 ? true : false;

        bool left = evaluateTree(root->left);
        bool right = evaluateTree(root->right);

        return root->val == 2 ? left | right : left & right;
    }

    // 2
    int memo[201][201];
    int getMoneyAmount(int n)
    {
        return dfs(1, n);
    }

    int dfs(int left, int right)
    {
        if (left >= right)
            return 0;

        if (memo[left][right])
            return memo[left][right];

        int ret = INT_MAX;
        for (int head = left; head <= right; head++)
        {
            int x = dfs(left, head - 1);
            int y = dfs(head + 1, right);

            ret = min(ret, head + max(x, y));
        }

        memo[left][right] = ret;
        return ret;
    }

    // 3
    vector<string> ret;
    string path;
    vector<string> letterCasePermutation(string s)
    {
        dfs(s, 0);
        return ret;
    }

    void dfs(string &s, int pos)
    {
        if (pos == s.size())
        {
            ret.push_back(path);
            return;
        }

        char ch = s[pos];
        path.push_back(ch);
        dfs(s, pos + 1);
        path.pop_back();

        if (!isdigit(ch))
        {
            char tmp = change(ch);
            path.push_back(tmp);
            dfs(s, pos + 1);
            path.pop_back();
        }
    }

    char change(char ch)
    {
        if (ch >= 'a' && ch <= 'z')
            ch -= 32;
        else
            ch += 32;
        return ch;
    }

    // 4
    string longestCommonPrefix(vector<string> &strs)
    {
        for (int i = 0; i < strs[0].size(); i++)
            for (int j = 1; j < strs.size(); j++)
                if (i == strs[j].size() || strs[0][i] != strs[j][i])
                    return strs[0].substr(0, i);
        return strs[0];
    }

    // 5
    vector<vector<int>> Ret;
    vector<int> Path;
    bool vis[7];
    vector<vector<int>> permute(vector<int> &nums)
    {
        DFS(nums, 0);
        return Ret;
    }

    void DFS(vector<int> &nums, int pos)
    {
        if (Path.size() == nums.size())
        {
            Ret.push_back(Path);
            return;
        }

        for (int i = 0; i < nums.size(); i++)
        {
            if (!vis[i])
            {
                vis[i] = true;
                Path.push_back(nums[i]);
                DFS(nums, pos + 1);
                Path.pop_back();
                vis[i] = false;
            }
        }
    }

    // 6
    int cnt, res = 0;
    int kthSmallest(TreeNode *root, int k)
    {
        cnt = k;
        dfs(root);
        return res;
    }

    void dfs(TreeNode *root)
    {
        if (root->left)
            dfs(root->left);

        if (--cnt == 0)
        {
            res = root->val;
            return;
        }

        if (root->right)
            dfs(root->right);
    }

    // 7
    string hash[10] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    vector<string> Res;
    string tmp;
    vector<string> letterCombinations(string digits)
    {
        if (digits.empty())
            return Res;

        DFS(digits, 0);
        return Res;
    }

    void DFS(string &digits, int pos)
    {
        if (pos == digits.size())
        {
            Res.push_back(tmp);
            return;
        }

        for (char ch : hash[digits[pos] - '0'])
        {
            tmp.push_back(ch);
            DFS(digits, pos + 1);
            tmp.pop_back();
        }
    }
};