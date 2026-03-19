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

    // 2
    int m, n;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
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
            auto [a, b] = q.front();
            q.pop();
            for (int k = 0; k < 4; k++)
            {
                int x = a + dx[k], y = b + dy[k];
                if (x >= 0 && x < m && y >= 0 && y < n && image[x][y] == origin)
                {
                    image[x][y] = color;
                    q.push({x, y});
                }
            }
        }

        return image;
    }

    // 3
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
                dp[i][j] = dp[i][j - 1];

                if (t[i] == s[j])
                    dp[i][j] += dp[i - 1][j - 1];
            }

        return dp[m][n];
    }

    // 5
    int subarraySum(vector<int> &nums, int k)
    {
        int sum = 0, ret = 0;
        unordered_map<int, int> hash;
        hash[0] = 1;

        for (auto n : nums)
        {
            sum += n;
            if (hash.count(sum - k))
                ret += hash[sum - k];
            hash[sum]++;
        }

        return ret;
    }

    // 6
    int ladderLength(string beginWord, string endWord, vector<string> &wordList)
    {
        if (beginWord == endWord)
            return 0;

        unordered_set<string> hash(wordList.begin(), wordList.end());
        unordered_set<string> vis;

        queue<string> q;
        q.push(beginWord);
        vis.insert(beginWord);
        int ret = 1;
        while (q.size())
        {
            ret++;
            int sz = q.size();
            while (sz--)
            {
                auto t = q.front();
                q.pop();
                for (int i = 0; i < t.size(); i++)
                {
                    string tmp = t;
                    for (char ch = 'a'; ch <= 'z'; ch++)
                    {
                        tmp[i] = ch;
                        if (hash.count(tmp) && !vis.count(tmp))
                        {
                            if (tmp == endWord)
                                return ret;

                            q.push(tmp);
                            vis.insert(tmp);
                        }
                    }
                }
            }
        }

        return 0;
    }

    // 6
    bool isMatch(string s, string p)
    {
        int m = s.size(), n = p.size();
        s = " " + s;
        p = " " + p;
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1));
        dp[0][0] = true;

        for (int i = 1; i <= n; i++)
            if (p[i] == '*')
                dp[0][i] = true;
            else
                break;

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                if (p[j] == '*')
                    dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
                else
                    dp[i][j] = (p[j] == '?' || p[j] == s[i]) && dp[i - 1][j - 1];
            }

        return dp[m][n];
    }
};

// 4
int main()
{
    string s;
    int hash[128] = {0};
    cin >> s;

    for (char ch : s)
        ++hash[ch];
    for (char ch : s)
        if (hash[ch] == 1)
        {
            cout << ch << endl;
            return 0;
        }

    cout << -1 << endl;
    return 0;
}