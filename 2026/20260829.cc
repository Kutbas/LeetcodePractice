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
    unordered_map<char, unordered_set<char>> hash;
    unordered_map<char, int> in;
    bool check = false;
    string alienOrder(vector<string> &words)
    {
        int n = words.size();
        for (auto word : words)
            for (auto ch : word)
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

            for (auto a : hash[t])
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
        int n = min(s1.size(), s2.size()), i = 0;

        for (; i < n; i++)
        {
            if (s1[i] != s2[i])
            {
                char a = s1[i], b = s2[i]; // a->b
                if (!hash.count(a) || !hash[a].count(b))
                {
                    in[b]++;
                    hash[a].insert(b);
                }
                break;
            }
        }

        // abc ab
        if (i < s1.size() && i == s2.size())
            check = true;
    }

    // 2
    int longestPalindrome(string s)
    {
        int n = s.size();
        int hash[128] = {0};
        for (char ch : s)
            hash[ch]++;

        int ret = 0;
        for (auto i : hash)
            ret += i / 2 * 2;

        return ret < n ? ret + 1 : ret;
    }

    // 3
    int firstUniqChar(string s)
    {
        int n = s.size();
        int hash[128] = {0};

        for (char ch : s)
            hash[ch]++;

        for (int i = 0; i < n; i++)
            if (hash[s[i]] == 1)
                return i;

        return -1;
    }

    // 4
    class MyQueue
    {
    private:
        stack<int> in, out;

        void in2out()
        {
            while (in.size())
            {
                out.push(in.top());
                in.pop();
            }
        }

    public:
        MyQueue()
        {
        }

        void push(int x)
        {
            in.push(x);
        }

        int pop()
        {
            if (out.empty())
                in2out();

            int r = out.top();
            out.pop();
            return r;
        }

        int peek()
        {
            if (out.empty())
                in2out();

            int r = out.top();
            return r;
        }

        bool empty()
        {
            return in.empty() && out.empty();
        }
    };

    // 5
    vector<int> ret;
    vector<int> inorderTraversal(TreeNode *root)
    {
        if (root == nullptr)
            return ret;

        Inorder(root);

        return ret;
    }

    void Inorder(TreeNode *root)
    {
        if (root == nullptr)
            return;

        Inorder(root->left);
        ret.push_back(root->val);
        Inorder(root->right);
    }
};