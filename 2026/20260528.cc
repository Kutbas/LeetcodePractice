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
    int longestOnes(vector<int> &nums, int k)
    {
        int n = nums.size(), ret = 0;

        for (int left = 0, right = 0, count = 0; right < n; right++)
        {
            if (nums[right] == 0)
                count++;
            while (count > k)
                if (nums[left++] == 0)
                    count--;
            ret = max(ret, right - left + 1);
        }

        return ret;
    }

    // 2
    int waysToStep(int n)
    {
        if (n < 3)
            return n;

        const int MOD = 1e9 + 7;
        int dp1 = 1, dp2 = 2, dp3 = 4, dp4 = 0;

        while (n-- != 3)
        {
            dp4 = ((dp1 + dp2) % MOD + dp3) % MOD;
            dp1 = dp2, dp2 = dp3, dp3 = dp4;
        }

        return dp3;
    }

    // 3
    vector<vector<string>> groupAnagrams(vector<string> &strs)
    {
        unordered_map<string, vector<string>> hash;
        for (auto str : strs)
        {
            string tmp = str;
            sort(tmp.begin(), tmp.end());
            hash[tmp].push_back(str);
        }

        vector<vector<string>> ret;
        for (auto &[a, b] : hash)
        {
            ret.push_back(b);
        }

        return ret;
    }

    // 4
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
            path.push_back('(');
            left++;
            dfs();
            left--;
            path.pop_back();
        }

        if (right < left)
        {
            path.push_back(')');
            right++;
            dfs();
            right--;
            path.pop_back();
        }
    }

    // 5
    int findLongestChain(vector<vector<int>> &pairs)
    {
        sort(pairs.begin(), pairs.end());
        int n = pairs.size(), ret = 1;
        vector<int> dp(n, 1);

        for (int i = 1; i < n; i++)
            for (int j = 0; j < i; j++)
            {
                int a = pairs[j][1], b = pairs[i][0];
                if (a < b)
                    dp[i] = max(dp[i], dp[j] + 1);
                ret = max(dp[i], ret);
            }

        return ret;
    }

    // 6
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

    // 7
    string convert(string s, int numRows)
    {
        if (numRows == 1)
            return s;

        string ret;
        int d = 2 * numRows - 2, n = s.size();

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

    // 8
    string removeDuplicates(string s)
    {
        string ret;

        for (char ch : s)
        {
            if (ret.size() && ch == ret.back())
                ret.pop_back();
            else
                ret += ch;
        }

        return ret;
    }

    // 9
    int maxProfit(vector<int> &prices)
    {
        const int INF = 0x3f3f3f;
        int n = prices.size(), ret = 0;
        vector<vector<int>> f(n, vector<int>(3, -INF));
        auto g = f;

        f[0][0] = -prices[0];
        g[0][0] = 0;

        for (int i = 1; i < n; i++)
            for (int j = 0; j < 3; j++)
            {
                f[i][j] = max(f[i - 1][j], g[i - 1][j] - prices[i]);
                g[i][j] = g[i - 1][j];

                if (j >= 1)
                    g[i][j] = max(g[i][j], f[i - 1][j - 1] + prices[i]);
            }

        for (int i = 0; i < 3; i++)
            ret = max(ret, g[n - 1][i]);

        return ret;
    }

    // 10
    int maxSubArray(vector<int> &nums)
    {
        int n = nums.size(), ret = INT_MIN;
        vector<int> dp(n + 1);

        for (int i = 1; i <= n; i++)
        {
            dp[i] = max(dp[i - 1] + nums[i - 1], nums[i - 1]);
            ret = max(dp[i], ret);
        }

        return ret;
    }

    // 11
    vector<int> rearrangeBarcodes(vector<int> &b)
    {
        // 1. 统计每个数字出现的次数，并找到出现次数最多的数字
        unordered_map<int, int> hash; // 数字 -> 频数
        int maxVal = 0, maxCount = 0; // 最多出现的数字及其次数

        for (auto x : b)
        {
            // 频数+1，同时判断是否成为新的最大值
            if (maxCount < ++hash[x])
            {
                maxCount = hash[x];
                maxVal = x;
            }
        }

        // 2. 先把出现次数最多的数字，放在所有偶数索引位置上（0, 2, 4...）
        int n = b.size(), index = 0; // index 表示当前填充位置
        vector<int> ret(n);          // 结果数组

        for (int i = 0; i < maxCount; i++)
        {
            ret[index] = maxVal; // 填入出现最多的数字
            index += 2;          // 跳过一个位置（间隔放置）
        }

        // 3. 处理剩下的数字
        hash.erase(maxVal); // 该数字已填完，从哈希表移除
        for (auto &[x, y] : hash)
        { // x: 数字, y: 出现次数
            for (int i = 0; i < y; i++)
            {
                // 如果偶数位填满了（index 超出范围），
                // 就转到奇数位开头（索引 1）继续填
                if (index >= n)
                    index = 1;

                ret[index] = x; // 填入当前数字
                index += 2;     // 跳到下一个同奇偶位置
            }
        }

        return ret;
    }
};