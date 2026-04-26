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
    bool isMatch(string s, string p)
    {
        int m = s.size(), n = p.size();
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1));
        s = " " + s, p = " " + p;

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

    // 2
    int massage(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 0)
            return 0;

        vector<int> f(n + 1), g(n + 1);
        for (int i = 1; i <= n; i++)
        {
            f[i] = g[i - 1] + nums[i - 1];
            g[i] = max(f[i - 1], g[i - 1]);
        }

        return max(f[n], g[n]);
    }

    // 3
    int K;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    bool vis[101][101] = {0};
    int wardrobeFinishing(int m, int n, int cnt)
    {
        K = cnt;

        int ret = 1;
        queue<pair<int, int>> q;
        q.push({0, 0});
        vis[0][0] = true;

        while (q.size())
        {
            auto [a, b] = q.front();
            q.pop();
            for (int k = 0; k < 4; k++)
            {
                int x = a + dx[k], y = b + dy[k];
                if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && Check(x, y))
                {
                    ret++;
                    q.push({x, y});
                    vis[x][y] = true;
                }
            }
        }

        return ret;
    }

    bool Check(int i, int j)
    {
        int tmp = 0;
        while (i)
        {
            tmp += i % 10;
            i /= 10;
        }
        while (j)
        {
            tmp += j % 10;
            j /= 10;
        }

        return tmp <= K;
    }

    // 4
    ListNode *reverseList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *newhead = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;

        return newhead;
    }

    // 5
    int widthOfBinaryTree(TreeNode *root)
    {
        typedef pair<TreeNode *, unsigned int> PTI;
        unsigned int ret = 0;
        vector<PTI> q;
        q.push_back({root, 1});

        while (q.size())
        {
            vector<PTI> tmp;

            auto &[x1, y1] = q[0];
            auto &[x2, y2] = q.back();
            ret = max(ret, y2 - y1 + 1);

            for (auto &[x, y] : q)
            {
                if (x->left)
                    tmp.push_back({x->left, 2 * y});
                if (x->right)
                    tmp.push_back({x->right, 2 * y + 1});
            }

            q = tmp;
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
    int m, n;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int ret = 0, step = 0;
    bool vis[21][21] = {0};
    int uniquePathsIII(vector<vector<int>> &grid)
    {
        m = grid.size(), n = grid[0].size();
        int bx, by;

        step += 2;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == 0)
                    step++;
                else if (grid[i][j] == 1)
                    bx = i, by = j;
            }
        vis[bx][by] = true;
        dfs(grid, bx, by, 1);

        return ret;
    }

    void dfs(vector<vector<int>> &grid, int i, int j, int count)
    {
        if (grid[i][j] == 2)
        {
            if (count == step)
                ret++;
            return;
        }

        for (int k = 0; k < 4; k++)
        {
            int x = i + dx[k], y = j + dy[k];
            if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && grid[x][y] != -1)
            {
                vis[x][y] = true;
                dfs(grid, x, y, count + 1);
                vis[x][y] = false;
            }
        }
    }
};

// 8
string s;

string change(string &s)
{
    if (s[0] >= 'A' && s[0] <= 'Z')
        s[0] = tolower(s[0]);
    return s;
}

int main()
{
    getline(cin, s);

    regex re{R"([a-zA-Z]+)"};
    sregex_token_iterator begin(s.begin(), s.end(), re, 0);
    sregex_token_iterator end;

    vector<string> words(begin, end);
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
