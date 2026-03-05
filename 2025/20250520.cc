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
    bool check;
    unordered_map<char, unordered_set<char>> edges;
    unordered_map<char, int> in;
    string alienOrder(vector<string> &words)
    {
        for (auto &word : words)
            for (char ch : word)
                in[ch] = 0;

        for (int i = 0; i < words.size(); i++)
            for (int j = i + 1; j < words.size(); j++)
            {
                add(words[i], words[j]);
                if (check)
                    return "";
            }

        string ret;
        queue<char> q;
        for (auto [a, b] : in)
            if (b == 0)
                q.push(a);

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

    void add(string &s1, string &s2)
    {
        int n = min(s1.size(), s2.size());
        int i = 0;

        for (; i < n; i++)
        {
            if (s1[i] != s2[i])
            {
                char a = s1[i], b = s2[i]; // s1:wrt  s2:wrf  t->f  a->b
                if (!edges.count(a) || !edges[a].count(b))
                {
                    edges[a].insert(b);
                    in[b]++;
                }
                break;
            }
        }

        // s1:abc;s2:ab
        if (i < s1.size() && i == s2.size())
            check = true;
    }

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int color)
    {
        m = image.size(), n = image[0].size();
        int origin = image[sr][sc];
        if (origin == color)
            return image;

        queue<pair<int, int>> q;
        q.push({sr, sc});
        image[sr][sc] = color;

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
                    if (x >= 0 && x < m && y >= 0 && y < n && image[x][y] == origin)
                    {
                        q.push({x, y});
                        image[x][y] = color;
                    }
                }
            }
        }

        return image;
    }

    string longestPalindrome(string s)
    {
        int n = s.size();
        vector<vector<bool>> dp(n, vector<bool>(n));

        for (int i = 0; i < n; i++)
            dp[i][i] = true;

        int begin = 0, maxlen = 1;
        for (int L = 2; L <= n; L++)
        {
            for (int i = 0; i < n; i++)
            {
                int j = i + L - 1;
                if (j >= n)
                    break;

                if (s[i] != s[j])
                    continue;
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

    int findPeakElement(vector<int> &nums)
    {
        int left = 0, right = nums.size() - 1;
        while (left < right)
        {
            int mid = left + (right - left + 1) / 2;
            if (nums[mid] >= nums[mid - 1])
                left = mid;
            else
                right = mid - 1;
        }
        return left;
    }

    int waysToStep(int n)
    {
        int base = 1000000007, dp1 = 1, dp2 = 2, dp3 = 4;
        if (n < 3)
            return n;

        while (n-- != 3)
        {
            int tmp2 = dp2, tmp3 = dp3;
            dp3 = ((dp1 + dp2) % base + dp3) % base;
            dp2 = tmp3;
            dp1 = tmp2;
        }

        return dp3;
    }
};