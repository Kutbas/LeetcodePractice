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
    vector<string> sortPeople(vector<string> &names, vector<int> &heights)
    {
        int n = names.size();
        vector<int> index(n);
        for (int i = 0; i < n; i++)
            index[i] = i;

        sort(index.begin(), index.end(), [&](const int i, const int j)
             { return heights[i] > heights[j]; });

        vector<string> ret;
        for (auto i : index)
            ret.push_back(names[i]);

        return ret;
    }

    // 2
    bool isMatch(string s, string p)
    {
        int m = s.size(), n = p.size();
        s = " " + s;
        p = " " + p;
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1));
        dp[0][0] = true;

        for (int i = 2; i <= n; i += 2)
            if (p[i] == '*')
                dp[0][i] = true;
            else
                break;

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                if (p[j] == '*')
                {
                    bool case1 = dp[i][j - 2];
                    bool case2 = (p[j - 1] == '.' || p[j - 1] == s[i]) && dp[i - 1][j];
                    dp[i][j] = case1 || case2;
                }
                else
                    dp[i][j] = (p[j] == '.' || p[j] == s[i]) && dp[i - 1][j - 1];
            }
        return dp[m][n];
    }

    // 3
    int tribonacci(int n)
    {
        if (n == 0)
            return 0;
        if (n == 1 || n == 2)
            return 1;

        int a = 0, b = 1, c = 1, d;
        while (n-- != 2)
        {
            d = a + b + c;
            a = b, b = c, c = d;
        }

        return c;
    }

    // 4
    int numDistinct(string s, string t)
    {
        int m = t.size(), n = s.size();
        s = " " + s;
        t = " " + t;
        vector<vector<double>> dp(m + 1, vector<double>(n + 1));

        for (int i = 0; i <= n; i++)
            dp[0][i] = 1;

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                dp[i][j] = dp[i][j - 1];

                if (t[i] == s[j])
                    dp[i][j] += dp[i - 1][j - 1];
            }

        return dp[m][n];
    }

    // 5
    int maxEnvelopes(vector<vector<int>> &e)
    {
        int n = e.size();
        sort(e.begin(), e.end(), [&](const vector<int> &v1, const vector<int> &v2)
             { return v1[0] != v2[0] ? v1[0] < v2[0] : v1[1] > v2[1]; });

        vector<int> ret;
        ret.push_back(e[0][1]);
        for (int i = 1; i < n; i++)
        {
            if (e[i][1] > ret.back())
                ret.push_back(e[i][1]);
            else
            {
                int left = 0, right = ret.size() - 1;
                while (left < right)
                {
                    int mid = left + (right - left) / 2;
                    if (e[i][1] > ret[mid])
                        left = mid + 1;
                    else
                        right = mid;
                }
                ret[left] = e[i][1];
            }
        }

        return ret.size();
    }

    // 6
    int findLength(vector<int> &nums1, vector<int> &nums2)
    {
        int m = nums1.size(), n = nums2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        int ret = 0;

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                if (nums1[i - 1] == nums2[j - 1])
                {
                    dp[i][j] = dp[i - 1][j - 1] + 1;

                    ret = max(ret, dp[i][j]);
                }

        return ret;
    }
};

// 7
string s;

string change(string s)
{
    if (s[0] >= 'A' && s[0] <= 'Z') // 明确判断大写（你原逻辑写反了符号）
        s[0] = tolower(s[0]);       // 关键：接收返回值，修改原字符
    return s;
}

int main()
{
    getline(cin, s);
    regex re{R"([a-zA-Z]+)"};

    sregex_token_iterator it(s.begin(), s.end(), re, 0);
    sregex_token_iterator end;

    vector<string> words(it, end);
    map<string, int> hash;
    for (auto &word : words)
    {
        string tmp = change(word);
        hash[tmp]++;
    }

    for (auto &[a, b] : hash)
        cout << a << ":" << b << endl;

    return 0;
}