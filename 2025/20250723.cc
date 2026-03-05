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
    string decodeString(string s)
    {
        stack<string> st;
        stack<int> nums;
        string ret;
        int k = 0;

        for (char ch : s)
        {
            if (isdigit(ch))
                k = k * 10 + ch - '0';
            else if (ch == '[')
            {
                st.push(ret);
                ret = "";
                nums.push(k);
                k = 0;
            }
            else if (ch == ']')
            {
                string tmp = st.top();
                st.pop();
                int n = nums.top();
                nums.pop();
                while (n--)
                    tmp += ret;
                ret = tmp;
            }
            else
                ret += ch;
        }

        return st.top();
    }

    TreeNode *pruneTree(TreeNode *root)
    {
        if (root == nullptr)
            return nullptr;

        TreeNode *left = pruneTree(root->left);
        TreeNode *right = pruneTree(root->right);

        if (left == nullptr && right == nullptr && root->val == 0)
            return nullptr;

        return root;
    }

    vector<int> missingTwo(vector<int> &nums)
    {
        int n = nums.size(), xorsum = 0;
        for (auto n : nums)
            xorsum ^= n;
        for (int i = 1; i <= n + 2; i++)
            xorsum ^= i;

        int lsb = xorsum == INT_MIN ? xorsum : xorsum & (-xorsum);
        int x = 0, y = 0;

        for (auto n : nums)
        {
            if (n & lsb)
                x ^= n;
            else
                y ^= n;
        }
        for (int i = 1; i <= n + 2; i++)
        {
            if (i & lsb)
                x ^= i;
            else
                y ^= i;
        }
        return {x, y};
    }

    unordered_map<char, unordered_set<char>> hash;
    unordered_map<char, int> in;
    bool check = false;
    string alienOrder(vector<string> &words)
    {
        for (auto word : words)
            for (auto ch : word)
                in[ch]++;

        int n = words.size();
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
            {
                add(words[i], words[j]);
                if (check)
                    return "";
            }

        queue<char> q;
        string ret;

        for (auto [a, b] : in)
            if (b == 0)
                q.push(a);

        while (q.size())
        {
            auto t = q.front();
            q.pop();
            ret += t;

            for (auto a : hash[t])
                if (--in[a] == 0)
                    q.push(a);
        }

        for (auto [a, b] : in)
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
                char a = s1[i], b = s2[i]; // a->b
                if (!hash.count(a) || !hash[a].count(b))
                {
                    hash[a].insert(b);
                    in[b]++;
                }
                break;
            }
        }

        // abc ab
        if (i < s1.size() && i == s2.size())
            check = true;
    }

    typedef pair<string, int> PSI;

    struct cmp
    {
        bool operator()(const PSI &p1, const PSI &p2)
        {
            if (p1.second == p2.second)
                return p1.first > p2.first;
            return p1.second < p2.second;
        }
    };

    vector<string> topKFrequent(vector<string> &words, int k)
    {
        unordered_map<string, int> hash;
        for (auto word : words)
            hash[word]++;

        vector<string> ret;
        priority_queue<PSI, vector<PSI>, cmp> q;
        for (auto &pair : hash)
            q.push(pair);

        while (k--)
        {
            auto [a, b] = q.top();
            q.pop();
            ret.push_back(a);
        }

        return ret;
    }

    vector<vector<string>> ret;
    vector<string> path;
    int N;
    bool checkCol[10], checkDig1[20], checkDig2[20];
    vector<vector<string>> solveNQueens(int n)
    {
        N = n;
        path.resize(n);
        for (int i = 0; i < n; i++)
            path[i].append(n, '.');

        dfs(0);

        return ret;
    }

    void dfs(int row)
    {
        if (row == N)
        {
            ret.push_back(path);
            return;
        }

        for (int col = 0; col < N; col++)
        {
            if (!checkCol[col] && !checkDig1[row - col + N] && !checkDig2[row + col])
            {
                path[row][col] = 'Q';
                checkCol[col] = checkDig1[row - col + N] = checkDig2[row + col] = true;
                dfs(row + 1);
                path[row][col] = '.';
                checkCol[col] = checkDig1[row - col + N] = checkDig2[row + col] = false;
            }
        }
    }
};