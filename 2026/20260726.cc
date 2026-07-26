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
#include <regex>
#include <map>
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
    bool checkPartitioning(string s)
    {
        int n = s.size();
        vector<vector<bool>> dp(n, vector<bool>(n));

        for (int i = n - 1; i >= 0; i--)
            for (int j = i; j < n; j++)
                if (s[i] == s[j])
                    dp[i][j] = j - i + 1 > 3 ? dp[i + 1][j - 1] : true;

        for (int i = 1; i < n - 1; i++)
            for (int j = i; j < n - 1; j++)
                if (dp[0][i - 1] && dp[i][j] && dp[j + 1][n - 1])
                    return true;

        return false;
    }

    // 2
    int longestPalindromeSubseq(string s)
    {
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n));

        for (int i = n - 1; i >= 0; i--)
            for (int j = i; j < n; j++)
            {
                if (s[i] == s[j])
                    dp[i][j] = i == j ? 1 : dp[i + 1][j - 1] + 2;
                else
                    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
            }

        return dp[0][n - 1];
    }

    // 3
    int deleteAndEarn(vector<int> &nums)
    {
        const int N = 10001;
        int arr[N] = {0};
        for (auto n : nums)
            arr[n] += n;

        vector<int> f(N), g(N);
        for (int i = 1; i < N; i++)
        {
            f[i] = g[i - 1] + arr[i];
            g[i] = max(f[i - 1], g[i - 1]);
        }

        return max(f[N - 1], g[N - 1]);
    }

    // 4
    int FindGreatestSumOfSubArray(vector<int> &array)
    {
        int n = array.size(), ret = INT_MIN;
        vector<int> dp(n + 1);

        for (int i = 1; i <= n; i++)
        {
            dp[i] = max(dp[i - 1] + array[i - 1], array[i - 1]);
            ret = max(ret, dp[i]);
        }

        return ret;
    }

    // 5
    vector<vector<int>> levelOrderBottom(TreeNode *root)
    {
        vector<vector<int>> ret;
        if (root == nullptr)
            return ret;

        queue<TreeNode *> q;
        q.push(root);
        while (q.size())
        {
            int sz = q.size();
            vector<int> tmp;
            while (sz--)
            {
                auto t = q.front();
                q.pop();
                tmp.push_back(t->val);

                if (t->left)
                    q.push(t->left);
                if (t->right)
                    q.push(t->right);
            }

            ret.push_back(tmp);
        }

        reverse(ret.begin(), ret.end());

        return ret;
    }

    // 6
    bool isPalindrome(string s)
    {
        string tmp;
        for (char ch : s)
            if (isalnum(ch))
                tmp += tolower(ch);

        int left = 0, right = tmp.size() - 1;
        while (left <= right)
        {
            if (tmp[left] == tmp[right])
                left++, right--;
            else
                return false;
        }

        return true;
    }

    // 8
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        int i = 0;
        return _buildTree(preorder, inorder, i, 0, inorder.size() - 1);
    }

    TreeNode *_buildTree(vector<int> &preorder, vector<int> &inorder, int &prev, int inBegin, int inEnd)
    {
        if (inBegin > inEnd)
            return nullptr;

        TreeNode *root = new TreeNode(preorder[prev]);

        int rooti = inBegin;
        while (rooti <= inEnd)
            if (inorder[rooti] == preorder[prev])
                break;
            else
                rooti++;

        ++prev;
        root->left = _buildTree(preorder, inorder, prev, inBegin, rooti - 1);
        root->right = _buildTree(preorder, inorder, prev, rooti + 1, inEnd);

        return root;
    }

    // 9
    string reverseWords(string s)
    {
        int n = s.size(), start = 0;

        for (int i = 0; i <= n; i++)
        {
            if (s[i] == ' ' || i == n)
            {
                reverse(s.begin() + start, s.begin() + i);
                start = i + 1;
            }
        }

        return s;
    }
};

// 7
class MinStack
{
private:
    stack<long> st;
    long minVal;

public:
    MinStack()
    {
    }

    void push(int value)
    {
        if (st.empty())
        {
            minVal = value;
            st.push(0);
        }
        else
        {
            long diff = value - minVal;
            if (diff < 0)
                minVal = value;

            st.push(diff);
        }
    }

    void pop()
    {
        long diff = st.top();
        st.pop();
        if (diff < 0)
            minVal = minVal - diff;
    }

    int top()
    {
        long diff = st.top();

        if (diff > 0)
            return minVal + diff;

        return minVal;
    }

    int getMin()
    {
        return minVal;
    }
};