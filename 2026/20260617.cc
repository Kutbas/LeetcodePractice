#include <mutex>
#include <vector>
#include <algorithm>
#include <climits>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <queue>
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
    unordered_map<char, int> in;
    unordered_map<char, unordered_set<char>> edges;
    bool check = false;
    string alienOrder(vector<string> &words)
    {
        for (auto &word : words)
            for (auto &ch : word)
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

        for (auto &[a, b] : in)
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
                char a = s1[i], b = s2[i];
                if (!edges.count(a) || !edges[a].count(b))
                {
                    in[b]++;
                    edges[a].insert(b);
                }
                break;
            }
        }

        if (i < s1.size() && i == s2.size())
            check = true;
    }

    // 2
    int longestPalindrome(string s)
    {
        int hash[128] = {0};

        for (char ch : s)
            hash[ch]++;

        int ret = 0;
        for (int x : hash)
            ret += x / 2 * 2;

        return ret < s.size() ? ret + 1 : ret;
    }

    // 4
    int maxTurbulenceSize(vector<int> &arr)
    {
        int n = arr.size(), ret = 1;
        vector<int> f(n, 1);
        auto g = f;

        for (int i = 1; i < n; i++)
        {
            if (arr[i - 1] > arr[i])
                f[i] = g[i - 1] + 1;
            else if (arr[i - 1] < arr[i])
                g[i] = f[i - 1] + 1;
            ret = max(ret, max(f[i], g[i]));
        }

        return ret;
    }

    // 5
    vector<vector<int>> ret;
    vector<vector<int>> levelOrderBottom(TreeNode *root)
    {
        if (root == nullptr)
            return ret;

        queue<TreeNode *> q;
        q.push(root);

        while (q.size())
        {
            vector<int> tmp;
            int sz = q.size();
            while (sz--)
            {
                auto t = q.front();
                q.pop();
                tmp.push_back(t->val);

                if (t->left)
                    q.push(t->left);
                if (t->right)
                    q.push(t->right);
            }

            ret.push_back(tmp);
        }

        reverse(ret.begin(), ret.end());

        return ret;
    }

    // 6
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        int i = 0;
        return _buildTree(preorder, inorder, i, 0, inorder.size() - 1);
    }

    TreeNode *_buildTree(vector<int> &preorder, vector<int> &inorder, int &prev, int inBegin, int inEnd)
    {
        if (inBegin > inEnd)
            return nullptr;

        TreeNode *root = new TreeNode(preorder[prev]);

        int rooti = inBegin;
        while (rooti <= inEnd)
            if (inorder[rooti] == preorder[prev])
                break;
            else
                rooti++;

        prev++;
        root->left = _buildTree(preorder, inorder, prev, inBegin, rooti - 1);
        root->right = _buildTree(preorder, inorder, prev, rooti + 1, inEnd);

        return root;
    }
};

// 3
class DiningPhilosophers
{
public:
    DiningPhilosophers()
    {
    }

    void wantsToEat(int philosopher,
                    function<void()> pickLeftFork,
                    function<void()> pickRightFork,
                    function<void()> eat,
                    function<void()> putLeftFork,
                    function<void()> putRightFork)
    {
        int l = philosopher, r = (philosopher + 1) % 5;
        if (l % 2 == 0)
        {
            lock[l].lock();
            lock[r].lock();
        }
        else
        {
            lock[r].lock();
            lock[l].lock();
        }
        pickLeftFork();
        pickRightFork();
        eat();
        putLeftFork();
        putRightFork();
        lock[l].unlock();
        lock[r].unlock();
    }

private:
    mutex lock[5];
};

// 7
class MinStack
{
private:
    stack<long> st;
    long minVal;

public:
    MinStack()
    {
    }

    void push(int value)
    {
        if (st.empty())
        {
            st.push(0);
            minVal = value;
        }
        else
        {
            long diff = value - minVal;
            if (diff < 0)
                minVal = value;

            st.push(diff);
        }
    }

    void pop()
    {
        long diff = st.top();
        st.pop();

        if (diff < 0)
            minVal = minVal - diff;
    }

    int top()
    {
        long diff = st.top();

        if (diff > 0)
            return minVal + diff;

        return minVal;
    }

    int getMin()
    {
        return minVal;
    }
};