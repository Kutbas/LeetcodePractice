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
    int numDistinct(string s, string t)
    {
        int m = t.size(), n = s.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));

        for (int j = 0; j <= n; j++)
            dp[0][j] = 1;
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                dp[i][j] += dp[i][j - 1];
                if (s[i - 1] == t[j - 1])
                    dp[i][j] += dp[i - 1][j - 1];
            }

        return dp[m][n];
    }

    bool isMatch(string s, string p)
    {
        int m = s.size(), n = p.size();
        s = " " + s, p = " " + p;
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1));

        dp[0][0] = true;
        for (int j = 1; j <= 1; j++)
            if (p[j] == '*')
                dp[0][j] = true;
            else
                break;

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                if (p[j] == '*')
                    dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
                else
                    dp[i][j] = (p[j] == '?' || s[i] == p[j]) && dp[i - 1][j - 1];

        return dp[m][n];
    }

    // 1
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    vector<vector<int>> updateMatrix(vector<vector<int>> &mat)
    {
        m = mat.size(), n = mat[0].size();
        vector<vector<int>> ret(m, vector<int>(n, -1));

        queue<pair<int, int>> q;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (mat[i][j])
                {
                    q.push({i, j});
                    ret[i][j] = 0;
                }

        while (q.size())
        {
            int sz = q.size();
            while (sz--)
            {
                auto [a, b] = q.front();
                q.pop();
                for (int k = 0; k < 4; k++)
                {
                    int x = a + dx[k], y = b + dy[k];
                    if (x >= 0 && x < m && y >= 0 && y < n && ret[x][y] == -1)
                    {
                        ret[x][y] = ret[a][b] + 1;
                        q.push({x, y});
                    }
                }
            }
        }
        return ret;
    }

    // 2
    unordered_map<char, unordered_set<char>> edges;
    unordered_map<char, int> in;
    bool check = false;
    string alienOrder(vector<string> &words)
    {
        int n = words.size();

        for (auto word : words)
            for (char ch : word)
                in[ch] = 0;

        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
            {
                add(words[i], words[j]);
                if (check)
                    return "";
            }

        queue<char> q;
        for (auto [a, b] : in)
            if (b == 0)
                q.push(a);

        string ret;
        while (q.size())
        {
            auto t = q.front();
            q.pop();
            ret += t;

            for (auto a : edges[t])
                if (--in[a] == 0)
                    q.push(a);
        }

        for (auto [a, b] : in)
            if (b)
                return "";
        return ret;
    }

    void add(const string &s1, const string &s2)
    {
        int n = min(s1.size(), s2.size());

        int i = 0;
        for (; i < n; i++)
        {
            if (s1[i] != s2[i])
            {
                char a = s1[i], b = s2[i]; // wrt wrf t->f a->b
                if (!edges.count(a) || !edges[a].count(b))
                {
                    edges[a].insert(b);
                    in[b]++;
                }
                break;
            }
        }

        // abc ab
        if (i == s2.size() && i < s1.size())
            check = true;

        return;
    }

    // 3
    string optimalDivision(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 1)
            return to_string(nums[0]);
        if (n == 2)
            return to_string(nums[0]) + '/' + to_string(nums[1]);

        string ret = to_string(nums[0]) + "/(" + to_string(nums[1]);
        for (int i = 1; i < n; i++)
            ret += '/' + to_string(nums[i]);
        ret += ')';

        return ret;
    }

    // 4
    int wiggleMaxLength(vector<int> &nums)
    {
        int n = nums.size(), ret = 0, left = 0;

        for (int i = 0; i < n - 1; i++)
        {
            int right = nums[i + 1] - nums[i];
            if (right == 0)
                continue;
            if (left * right <= 0)
                ret++;
            left = right;
        }

        return ret + 1;
    }

    // 5
    bool increasingTriplet(vector<int> &nums)
    {
        int a = nums[0], b = INT_MAX;
        for (int i = 1; i < nums.size(); i++)
        {
            if (nums[i] > b)
                return true;
            else if (nums[i] > a)
                b = nums[i];
            else
                a = nums[i];
        }

        return false;
    }

    // 6
    string longestCommonPrefix(vector<string> &strs)
    {
        for (int i = 0; i < strs[0].size(); i++)
            for (int j = 1; j < strs.size(); j++)
                if (i == strs[j].size() || strs[0][i] != strs[j][i])
                    return strs[0].substr(0, i);
        return strs[0];
    }

    // 7
    int maxProfit(vector<int> &prices)
    {
        int n = prices.size(), ret = 0;
        for (int i = 0; i < n; i++)
        {
            int j = i;
            while (j + 1 < n && prices[j + 1] > prices[j])
                j++;
            ret += prices[j] - prices[i];
            i = j;
        }
        return ret;
    }
};