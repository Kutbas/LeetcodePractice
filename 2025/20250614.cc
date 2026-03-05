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
    int widthOfBinaryTree(TreeNode *root)
    {
        vector<pair<TreeNode *, unsigned int>> q;
        q.push_back({root, 1});
        unsigned int ret = 0;

        while (q.size())
        {
            auto [x1, y1] = q[0];
            auto [x2, y2] = q.back();
            ret = max(ret, y2 - y1 + 1);

            vector<pair<TreeNode *, unsigned int>> tmp;
            for (auto [x, y] : q)
            {
                if (x->left)
                    q.push_back({x->left, 2 * y});
                if (x->right)
                    q.push_back({x->right, 2 * y + 1});
            }

            q = tmp;
        }

        return ret;
    }

    bool evaluateTree(TreeNode *root)
    {
        if (root->left == nullptr)
            return root->val == 0 ? false : true;

        bool left = evaluateTree(root->left);
        bool right = evaluateTree(root->right);
        return root->val == 2 ? left | right : left & right;
    }

    string longestPalindrome(string s)
    {
        int begin = -1, maxlen = 1, m = s.size();
        vector<vector<bool>> dp(m, vector<bool>(m));

        for (int i = 0; i < m; i++)
            dp[i][i] = true;

        for (int i = 0; i < m; i++)
        {
            for (int L = 2; L <= m; L++)
            {
                int j = i + L - 1;
                if (j >= m)
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

    string decodeString(string s)
    {
        string ret;
        int k = 0;
        stack<int> nums;
        stack<string> st;

        for (char ch : s)
        {
            if (isdigit(ch))
                k = k * 10 + ch - '0';
            else if (ch == '[')
            {
                st.push(ret);
                ret = "";
                nums.push(k);
                k = 0;
            }
            else if (ch == ']')
            {
                string tmp = st.top();
                st.pop();
                int n = nums.top();
                nums.pop();
                while (n--)
                    tmp += ret;
                ret = tmp;
            }
            else
                ret += ch;
        }

        return ret;
    }

    double myPow(double x, int n)
    {
        long long N = n;
        if (N < 0)
        {
            x = 1 / x;
            N = -N;
        }
        return pow(x, N);
    }

    double pow(double x, int n)
    {
        if (n == 0)
            return 1;

        double tmp = pow(x, n / 2);
        return n % 2 == 0 ? tmp * tmp : tmp * tmp * x;
    }

    int tmp[50010] = {0};
    int reversePairs(vector<int> &nums)
    {
        return mergeSort(nums, 0, nums.size() - 1);
    }

    int mergeSort(vector<int> &nums, int left, int right)
    {
        if (left >= right)
            return 0;

        int mid = left + (right - left) / 2;
        int ret = 0;
        ret += mergeSort(nums, left, mid);
        ret += mergeSort(nums, mid + 1, right);

        int i = 0, cur1 = left, cur2 = mid + 1;
        while (cur1 <= mid && cur2 <= right)
        {
            if (nums[cur1] <= nums[cur2])
                tmp[i++] = nums[cur2++];
            else
            {
                ret += right - cur2 + 1;
                tmp[i++] = nums[cur1++];
            }
        }

        while (cur1 <= mid)
            tmp[i++] = nums[cur1++];
        while (cur2 <= right)
            tmp[i++] = nums[cur2++];

        for (int j = left; j <= right; j++)
            nums[j] = tmp[j - left];

        return ret;
    }

    long prev = LONG_MIN;
    bool isValidBST(TreeNode *root)
    {
        if (root == nullptr)
            return true;

        bool left = isValidBST(root->left);
        if (!left)
            return false;

        bool cur = false;
        if (root->val > prev)
            cur = true;
        if (!cur)
            return false;

        prev = root->val;
        bool right = isValidBST(root->right);
        return left & cur & right;
    }

    int ret, count;
    int kthSmallest(TreeNode *root, int k)
    {
        count = k;
        dfs(root);
        return ret;
    }

    void dfs(TreeNode *root)
    {
        if (root == nullptr || count == 0)
            return;

        dfs(root->left);
        count--;
        if (count == 0)
            ret = root->val;
        dfs(root->right);
    }

    long prev = LONG_MIN;
    bool isValidBST(TreeNode *root)
    {
        if (root == nullptr)
            return true;

        bool left = isValidBST(root->left);
        if (!left)
            return false;

        bool cur = false;
        if (root->val > prev)
            cur = true;
        if (!cur)
            return false;

        prev = root->val;
        bool right = isValidBST(root->right);
        return right;
    }
};