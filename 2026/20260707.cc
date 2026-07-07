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
    int search(vector<int> &nums, int target)
    {
        int left = 0, right = nums.size() - 1;

        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] < target)
                left = mid + 1;
            else if (nums[mid] > target)
                right = mid - 1;
            else
                return mid;
        }

        return -1;
    }

    // 2
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

    // 3
    int maxTurbulenceSize(vector<int> &arr)
    {
        int n = arr.size(), ret = 1;
        vector<int> f(n, 1), g(n, 1);

        for (int i = 1; i < n; i++)
        {
            if (arr[i] > arr[i - 1])
                f[i] = g[i - 1] + 1;
            else if (arr[i] < arr[i - 1])
                g[i] = f[i - 1] + 1;

            ret = max(ret, max(f[i], g[i]));
        }

        return ret;
    }

    // 4
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

    // 5
    vector<int> ret;
    vector<int> preorderTraversal(TreeNode *root)
    {
        dfs(root);
        return ret;
    }

    void dfs(TreeNode *root)
    {
        if (root == nullptr)
            return;

        ret.push_back(root->val);

        dfs(root->left);
        dfs(root->right);
    }

    // 6
    string reverseWords(string s)
    {
        int n = s.size(), begin = 0;

        for (int i = 0; i <= n; i++)
            if (s[i] == ' ' || i == n)
            {
                reverse(s.begin() + begin, s.begin() + i);
                begin = i + 1;
            }

        return s;
    }

    // 8
    vector<TreeNode *> TreeLists;

    void Inorder(TreeNode *root)
    {
        if (root == nullptr)
            return;

        Inorder(root->left);
        TreeLists.push_back(root);
        Inorder(root->right);
    }

    TreeNode *Convert(TreeNode *pRootOfTree)
    {
        if (pRootOfTree == nullptr)
            return nullptr;

        Inorder(pRootOfTree);

        for (int i = 1; i < TreeLists.size(); i++)
        {
            TreeLists[i]->left = TreeLists[i - 1];
            TreeLists[i - 1]->right = TreeLists[i];
        }

        return TreeLists[0];
    }

    // 9
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
            st.push(0);
            minVal = value;
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
        long top = st.top();
        st.pop();

        if (top < 0)
            minVal = minVal - top;
    }

    int top()
    {
        long top = st.top();

        if (top > 0)
            return minVal + top;
        return minVal;
    }

    int getMin()
    {
        return minVal;
    }
};
