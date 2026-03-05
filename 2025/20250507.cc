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
            auto &[x1, y1] = q[0];
            auto &[x2, y2] = q.back();

            ret = max(ret, y2 - y1 + 1);

            vector<pair<TreeNode *, unsigned int>> tmp;
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

    string minWindow(string s, string t)
    {
        int m = t.size(), begin = -1, minlen = INT_MAX;
        int hash1[128] = {0};
        int hash2[128] = {0};

        for (auto ch : t)
            hash1[ch]++;

        for (int left = 0, right = 0, count = 0; right < s.size(); right++)
        {
            char in = s[right];
            if (++hash2[in] <= hash1[in])
                count++;

            while (count == m)
            {
                if (right - left + 1 < minlen)
                {
                    begin = left;
                    minlen = right - left + 1;
                }

                char out = s[left++];
                if (hash2[out]-- <= hash1[out])
                    count--;
            }
        }

        return begin == -1 ? "" : s.substr(begin, minlen);
    }

    int widthOfBinaryTree(TreeNode *root)
    {
        vector<pair<TreeNode *, unsigned int>> q;
        q.push_back({root, 1});

        unsigned int ret = 0;

        while (q.size())
        {
            auto &[x1, y1] = q[0];
            auto &[x2, y2] = q.back();

            ret = max(ret, y2 - y1 + 1);
            vector<pair<TreeNode *, unsigned int>> tmp;
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

    typedef pair<int, int> PIR;
    int m, n;
    int cutOffTree(vector<vector<int>> &f)
    {
        m = f.size(), n = f[0].size();
        vector<PIR> trees;

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (f[i][j] > 1)
                    trees.push_back({i, j});

        sort(trees.begin(), trees.end(), [&](const PIR &p1, const PIR &p2)
             { return f[p1.first][p1.second] < f[p2.first][p2.second]; });

        int ret = 0;
        int bx = 0, by = 0;
        for (auto [a, b] : trees)
        {
            int step = BFS(f, bx, by, a, b);
            if (step == -1)
                return -1;
            ret += step;
            bx = a, by = b;
        }

        return ret;
    }

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int BFS(vector<vector<int>> &f, int bx, int by, int ex, int ey)
    {
        if (bx == ex && by == ey)
            return 0;

        queue<PIR> q;
        bool vis[51][51] = {0};

        q.push({bx, by});
        vis[bx][by] = true;

        int ret = 0;
        while (q.size())
        {
            ret++;
            int sz = q.size();
            while (sz--)
            {
                auto [a, b] = q.front();
                q.pop();

                for (int k = 0; k < 4; k++)
                {
                    int x = a + dx[k], y = b + dy[k];
                    if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && f[x][y])
                    {
                        if (x == ex && y == ey)
                            return ret;
                        q.push({x, y});
                        vis[x][y] = true;
                    }
                }
            }
        }

        return -1;
    }

    bool containsNearbyDuplicate(vector<int> &nums, int k)
    {
        unordered_map<int, int> hash;

        for (int i = 0; i < nums.size(); i++)
        {
            if (hash.count(nums[i]))
                if (i - hash[nums[i]] <= k)
                    return true;
            hash[nums[i]] = i;
        }

        return false;
    }

    void duplicateZeros(vector<int> &arr)
    {
        int dest = -1, cur = 0, n = arr.size();

        while (cur < n)
        {
            if (arr[cur])
                dest++;
            else
                dest += 2;
            if (dest >= n - 1)
                break;
            cur++;
        }

        if (dest == n)
        {
            arr[n - 1] = 0;
            cur--;
            dest -= 2;
        }

        while (cur >= 0)
        {
            if (arr[cur])
                arr[dest--] = arr[cur--];
            else
            {
                arr[dest--] = 0;
                arr[dest--] = 0;
                cur--;
            }
        }
    }

    int widthOfBinaryTree(TreeNode *root)
    {
        vector<pair<TreeNode *, unsigned int>> q;

        unsigned int ret = 0;
        q.push_back({root, 1});

        while (q.size())
        {
            auto &[x1, y1] = q[0];
            auto &[x2, y2] = q.back();

            ret = max(ret, y2 - y1 + 1);
            vector<pair<TreeNode *, unsigned int>> tmp;
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
};