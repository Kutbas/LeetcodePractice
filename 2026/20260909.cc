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
    string convert(string s, int numRows)
    {
        if (numRows == 1)
            return s;

        int n = s.size(), d = 2 * numRows - 2;
        string ret;
        for (int i = 0; i < n; i += d)
            ret += s[i];
        for (int k = 1; k < numRows - 1; k++)
            for (int i = k, j = d - k; i < n || j < n; i += d, j += d)
            {
                if (i < n)
                    ret += s[i];
                if (j < n)
                    ret += s[j];
            }
        for (int i = numRows - 1; i < n; i += d)
            ret += s[i];

        return ret;
    }

    // 2
    int N, left = 0, right = 0;
    vector<string> ret;
    string path;
    vector<string> generateParenthesis(int n)
    {
        N = n;
        dfs();
        return ret;
    }

    void dfs()
    {
        if (right == N)
        {
            ret.push_back(path);
            return;
        }

        if (left < N)
        {
            path += '(';
            left++;
            dfs();
            left--;
            path.pop_back();
        }

        if (right < left)
        {
            path += ')';
            right++;
            dfs();
            right--;
            path.pop_back();
        }
    }

    // 3
    int deleteAndEarn(vector<int> &nums)
    {
        const int N = 10001;
        int arr[N] = {0};
        for (auto n : nums)
            arr[n] += n;

        vector<int> f(N);
        auto g = f;

        for (int i = 1; i < N; i++)
        {
            f[i] = g[i - 1] + arr[i];
            g[i] = max(f[i - 1], g[i - 1]);
        }

        return max(f[N - 1], g[N - 1]);
    }

    // 4
    int maxProfit(int k, vector<int> &prices)
    {
        const int INF = 0x3f3f3f;
        int n = prices.size(), ret = 0;
        k = min(k, n / 2);
        vector<vector<int>> f(n, vector<int>(k + 1, -INF));
        auto g = f;

        f[0][0] = -prices[0];
        g[0][0] = 0;

        for (int i = 1; i < n; i++)
            for (int j = 0; j <= k; j++)
            {
                f[i][j] = max(f[i - 1][j], g[i - 1][j] - prices[i]);
                g[i][j] = g[i - 1][j];
                if (j >= 1)
                    g[i][j] = max(g[i][j], f[i - 1][j - 1] + prices[i]);
                ret = max(ret, g[i][j]);
            }

        return ret;
    }

    // 5
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
};

class Solution
{
public:
    // GetPath：就像是在走迷宫找人，记录从起点（根节点）到终点（节点 x）的路径
    // path 像是一个“历史记录本”（栈），走过的路就记下来，是个输出型参数
    bool GetPath(TreeNode *root, TreeNode *x, stack<TreeNode *> &path)
    {
        // 1. 如果走到死胡同（空节点），说明这条路不对，返回 false
        if (root == nullptr)
            return false;

        // 2. 只要走到一个节点，不管三七二十一，先把它记在“记录本”里（入栈）
        path.push(root);

        // 3. 如果当前节点刚好就是我们要找的终点！太棒了，直接返回 true，告诉上一层“找到了”
        if (root == x)
            return true;

        // 4. 如果当前节点不是终点，那就先去它的左子树找找看
        // 如果左边找到了（返回 true 了），那就一路把 true 往回传，不用再去右边了
        if (GetPath(root->left, x, path))
            return true;

        // 5. 如果左边没找到，那就再去右子树找找看
        // 如果右边找到了，同样一路把 true 往回传
        if (GetPath(root->right, x, path))
            return true;

        // 6. 如果左边右边都没找到，说明这个节点根本不在去往终点的正确路线上！
        // 既然走错路了，就把这个节点从“记录本”里划掉（出栈），然后返回 false 告诉上一层“这条路不通”
        path.pop();
        return false;
    }

    // lowestCommonAncestor：寻找 p 和 q 的最近公共祖先
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        // 准备两个记事本（栈），分别记录找 p 和找 q 的路径
        stack<TreeNode *> pPath, qPath;

        // 分别派出两支队伍，找出从根节点到 p，以及从根节点到 q 的路径
        GetPath(root, p, pPath);
        GetPath(root, q, qPath);

        // 此时，栈里的存放顺序是从根节点（栈底）到目标节点（栈顶）
        // 为了从后往前找“分岔口”，我们要先让这两条路处于同一个“起跑线”（让栈的高度一样）
        while (pPath.size() != qPath.size())
        {
            // 谁的路径长，谁就先往回退一步（出栈），直到两个路径一样长
            if (pPath.size() > qPath.size())
                pPath.pop();
            else
                qPath.pop();
        }

        // 走到这里，两条路径一样长了。两人一起一步步往回退（出栈）
        // 只要当前所在节点不一样，就继续往上层退
        while (pPath.top() != qPath.top())
        {
            pPath.pop();
            qPath.pop();
        }

        // 循环结束时，意味着 pPath.top() == qPath.top()，两人在某个路口相遇了！
        // 这个相遇的路口，就是它们最近的公共祖先。
        return pPath.top();
    }
};
