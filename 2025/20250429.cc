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
    bool isPalindrome(string s)
    {
        string tmp;
        for (auto ch : s)
            if (isalnum(ch))
                tmp += tolower(ch);

        for (int i = 0, j = tmp.size() - 1; i <= j; i++, j--)
            if (tmp[i] != tmp[j])
                return false;
        return true;
    }

    int triangleNumber(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        int ret = 0;

        for (int i = nums.size() - 1; i >= 2; i--)
        {
            int left = 0, right = i - 1;
            while (left < right)
            {
                if (nums[left] + nums[right] > nums[i])
                {
                    ret += right - left;
                    right--;
                }
                else
                    left++;
            }
        }

        return ret;
    }

    vector<int> largestValues(TreeNode *root)
    {
        vector<int> ret;
        if (root == nullptr)
            return ret;

        queue<TreeNode *> q;
        q.push(root);

        while (q.size())
        {
            int sz = q.size();
            int tmp = INT_MIN;
            while (sz--)
            {
                auto t = q.front();
                q.pop();
                tmp = max(tmp, t->val);

                if (t->left)
                    q.push(t->left);
                if (t->right)
                    q.push(t->right);
            }
            ret.push_back(tmp);
        }

        return ret;
    }

    unordered_map<char, unordered_set<char>> edges;
    unordered_map<char, int> in;
    bool check;
    string alienOrder(vector<string> &words)
    {
        for (auto &s : words)
            for (auto ch : s)
                in[ch] = 0;

        int n = words.size();
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
            {
                add(words[i], words[j]);
                if (check)
                    return "";
            }

        queue<char> q;
        for (auto &[a, b] : in)
            if (b == 0)
                q.push(a);

        string ret;
        while (q.size())
        {
            char t = q.front();
            q.pop();

            ret += t;
            for (char ch : edges[t])
            {
                if (--in[ch] == 0)
                    q.push(ch);
            }
        }

        for (auto &[a, b] : in)
            if (b != 0)
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
                char a = s1[i], b = s2[i];
                if (!edges.count(a) || !edges[a].count(b))
                {
                    edges[a].insert(b);
                    in[b]++;
                }
                break;
            }
        }

        if (i == s2.size() && i < s1.size())
            check = true;
    }

    vector<int> twoSum(vector<int> &nums, int target)
    {
        unordered_map<int, int> hash;
        hash[0] = 1;

        for (int i = 0; i < nums.size(); i++)
        {
            int x = target - nums[i];
            if (hash.count(x))
                return {i, hash[x]};
            hash[x] = i;
        }

        return {-1, -1};
    }

    string countAndSay(int n)
    {
        string ret = "1";
        for (int i = 1; i < n; i++)
        {
            string tmp;
            int len = ret.size();
            for (int left = 0, right = 0; right < len;)
            {
                while (right < len && ret[left] == ret[right])
                    right++;
                tmp += to_string(right - left) + ret[left];
                left = right;
            }
            ret = tmp;
        }

        return ret;
    }

    int waysToStep(int n)
    {
        int base = 1000000007, dp1 = 1, dp2 = 2, dp3 = 4, tmp2, tmp3;
        if (n < 3)
            return n;

        while (n-- != 3)
        {
            tmp3 = dp3, tmp2 = dp2;
            dp3 = ((dp3 + dp2) % base + dp1) % base;
            dp2 = tmp3, dp1 = tmp2;
        }

        return dp3;
    }

    int tmp[50010];
    int reversePairs(vector<int> &nums)
    {
        return mergesort(nums, 0, nums.size() - 1);
    }

    int mergesort(vector<int> &nums, int left, int right)
    {
        if (left >= right)
            return 0;

        int mid = left + (right - left) / 2, ret = 0;
        ret += mergesort(nums, left, mid);
        ret += mergesort(nums, mid + 1, right);

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

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    bool vis[201][201];
    int m, n;
    void solve(vector<vector<char>> &board)
    {
        m = board.size(), n = board[0].size();

        for (int i = 0; i < m; i++)
        {
            if (board[i][0] == 'O')
                bfs(board, i, 0);
            if (board[i][n - 1] == 'O')
                bfs(board, i, n - 1);
        }

        for (int j = 0; j < n; j++)
        {
            if (board[0][j] == 'O')
                bfs(board, 0, j);
            if (board[m - 1][j] == 'O')
                bfs(board, m - 1, j);
        }

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (board[i][j] == 'O')
                    board[i][j] = 'X';
                else if (board[i][j] == '.')
                    board[i][j] = 'O';
            }
    }

    void bfs(vector<vector<char>> &board, int i, int j)
    {
        queue<pair<int, int>> q;
        q.push({i, j});

        board[i][j] = '.';
        vis[i][j] = true;

        while (q.size())
        {
            auto [a, b] = q.front();
            q.pop();

            for (int k = 0; k < 4; k++)
            {
                int x = a + dx[k], y = b + dy[k];
                if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && board[x][y] == 'O')
                {
                    q.push({x, y});
                    board[x][y] = '.';
                    vis[x][y] = true;
                }
            }
        }
    }

    unordered_map<char, unordered_set<char>> edges;
    unordered_map<char, int> in;
    bool check;
    string alienOrder(vector<string> &words)
    {
        for (auto &s : words)
            for (auto ch : s)
                in[ch] = 0;

        int n = words.size();
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
            {
                add(words[i], words[j]);
                if (check)
                    return "";
            }

        string ret;
        queue<char> q;

        for (auto &[a, b] : in)
            if (b == 0)
                q.push(a);

        while (q.size())
        {
            int sz = q.size();

            while (sz--)
            {
                auto t = q.front();
                q.pop();
                ret += t;

                for (auto a : edges[t])
                    if (--in[a] == 0)
                        q.push(a);
            }
        }

        for (auto &[a, b] : in)
            if (b != 0)
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
                char a = s1[i], b = s2[i];
                if (!edges.count(a) || !edges[a].count(b))
                {
                    edges[a].insert(b);
                    in[b]++;
                }
                break;
            }
        }

        if (i == s2.size() && i < s1.size())
            check = true;
        return;
    }

    unordered_map<char, unordered_set<char>> edges;
    unordered_map<char, int> in;
    bool check;
    string alienOrder(vector<string> &words)
    {
        for (auto &s : words)
            for (auto ch : s)
                in[ch] = 0;

        int n = words.size();
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
            {
                add(words[i], words[j]);
                if (check)
                    return "";
            }

        string ret;
        queue<char> q;
        for (auto &[a, b] : in)
            if (b == 0)
                q.push(a);

        while (q.size())
        {
            int sz = q.size();
            while (sz--)
            {
                auto t = q.front();
                q.pop();
                ret += t;

                for (auto a : edges[t])
                    if (--in[a] == 0)
                        q.push(a);
            }
        }

        for (auto &[a, b] : in)
            if (b != 0)
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
                int a = s1[i], b = s2[i];
                if (!edges.count(a) || !edges[a].count(b))
                {
                    edges[a].insert(b);
                    in[b]++;
                }
                break;
            }
        }

        if (i == s2.size() && i < s1.size())
            check = true;
    }
};