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
    vector<vector<int>> generate(int numRows)
    {
        vector<vector<int>> ret(numRows);

        for (int i = 0; i < numRows; i++)
        {
            ret[i].resize(i + 1);
            ret[i][0] = ret[i][i] = 1;
            for (int j = 1; j < i; j++)
                ret[i][j] = ret[i - 1][j] + ret[i - 1][j - 1];
        }

        return ret;
    }

    // 2
    int findContentChildren(vector<int> &g, vector<int> &s)
    {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());

        int m = g.size(), n = s.size(), ret = 0;
        for (int i = 0, j = 0; i < m && j < n; i++, j++)
        {
            while (j < n && s[j] < g[i])
                j++;

            if (j < n)
                ret++;
        }

        return ret;
    }

    // 3
    int maxSumDivThree(vector<int> &nums)
    {
        const int INF = 0x3f3f3f;
        int n = nums.size(), sum = 0;
        int x1 = INF, x2 = INF;
        int y1 = INF, y2 = INF;

        for (auto num : nums)
        {
            sum += num;

            if (num % 3 == 1)
            {
                if (num < x1)
                    x2 = x1, x1 = num;
                else if (num < x2)
                    x2 = num;
            }
            else if (num % 3 == 2)
            {
                if (num < y1)
                    y2 = y1, y1 = num;
                else if (num < y2)
                    y2 = num;
            }
        }

        if (sum % 3 == 0)
            return sum;

        return sum % 3 == 1 ? max(sum - x1, sum - y1 - y2)
                            : max(sum - y1, sum - x1 - x2);
    }

    // 4
    int minCut(string s)
    {
        int n = s.size();
        vector<vector<bool>> isPal(n, vector<bool>(n));
        for (int i = n - 1; i >= 0; i--)
            for (int j = i; j < n; j++)
                if (s[i] == s[j])
                    isPal[i][j] = j - i + 1 > 3 ? isPal[i + 1][j - 1] : true;

        vector<int> dp(n, INT_MAX);
        for (int i = 0; i < n; i++)
        {
            if (isPal[0][i])
                dp[i] = 0;
            else
            {
                for (int j = 1; j <= i; j++)
                    if (isPal[j][i])
                        dp[i] = min(dp[i], dp[j - 1] + 1);
            }
        }

        return dp[n - 1];
    }

    // 5
    bool canPartition(vector<int> &nums)
    {
        int n = nums.size(), sum = 0;
        for (auto num : nums)
            sum += num;

        if (sum % 2)
            return false;

        int aim = sum / 2;
        vector<vector<bool>> dp(n + 1, vector<bool>(aim + 1));

        for (int i = 0; i <= n; i++)
            dp[i][0] = true;

        for (int i = 1; i <= n; i++)
            for (int j = 0; j <= aim; j++)
            {
                dp[i][j] = dp[i - 1][j];
                if (j >= nums[i - 1])
                    dp[i][j] = dp[i][j] || dp[i - 1][j - nums[i - 1]];
            }

        return dp[n][aim];
    }

    // 6
    int numDistinct(string s, string t)
    {
        int m = t.size(), n = s.size();
        vector<vector<double>> dp(m + 1, vector<double>(n + 1));
        s = " " + s;
        t = " " + t;

        for (int i = 0; i <= n; i++)
            dp[0][i] = 1;

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                dp[i][j] += dp[i][j - 1];
                if (t[i] == s[j])
                    dp[i][j] += dp[i - 1][j - 1];
            }

        return dp[m][n];
    }

    // 8
    class MyQueue
    {
    private:
        stack<int> in, out;

        void in2out()
        {
            while (in.size())
            {
                out.push(in.top());
                in.pop();
            }
        }

    public:
        MyQueue()
        {
        }

        void push(int x)
        {
            in.push(x);
        }

        int pop()
        {
            if (out.empty())
                in2out();

            int r = out.top();
            out.pop();
            return r;
        }

        int peek()
        {
            if (out.empty())
                in2out();
            int r = out.top();
            return r;
        }

        bool empty()
        {
            return in.empty() && out.empty();
        }
    };

    // 9
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        int i = 0;
        return _buildTree(preorder, inorder, i, 0, inorder.size() - 1);
    }

    TreeNode *_buildTree(vector<int> &preorder, vector<int> &inorder, int &previ, int inBegin, int inEnd)
    {
        if (inBegin > inEnd)
            return nullptr;

        TreeNode *root = new TreeNode(preorder[previ]);
        int rooti = inBegin;
        while (rooti <= inEnd)
            if (inorder[rooti] == preorder[previ])
                break;
            else
                rooti++;

        previ++;
        root->left = _buildTree(preorder, inorder, previ, inBegin, rooti - 1);
        root->right = _buildTree(preorder, inorder, previ, rooti + 1, inEnd);

        return root;
    }

    // 10
    int lenLongestFibSubseq(vector<int> &arr)
    {
        int n = arr.size();
        unordered_map<int, int> hash;

        for (int i = 0; i < n; i++)
            hash[arr[i]] = i;

        int ret = 2;
        vector<vector<int>> dp(n, vector<int>(n, 2));
        for (int j = 2; j < n; j++)
            for (int i = 1; i < j; i++)
            {
                int a = arr[j] - arr[i];
                if (a < arr[i] && hash.count(a))
                    dp[i][j] = dp[hash[a]][i] + 1;
                ret = max(ret, dp[i][j]);
            }

        return ret < 3 ? 0 : ret;
    }
};

// 7
int main()
{
    string s;
    while (cin >> s)
        ;
    cout << s.size() << endl;

    return 0;
}