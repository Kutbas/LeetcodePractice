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
    int largestSumAfterKNegations(vector<int> &nums, int k)
    {
        int n = nums.size(), count = 0, minElem = INT_MAX;
        for (auto num : nums)
        {
            if (num < 0)
                count++;
            minElem = min(minElem, abs(num));
        }

        int sum = 0;
        if (count > k)
        {
            sort(nums.begin(), nums.end());
            for (int i = 0; i < k; i++)
                sum += -nums[i];
            for (int i = k; i < n; i++)
                sum += nums[i];
        }
        else
        {
            for (auto num : nums)
                sum += abs(num);

            if ((k - count) % 2 != 0)
                sum -= 2 * minElem;
        }

        return sum;
    }

    // 2
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder)
    {
        int i = postorder.size() - 1;
        return _buildTree(inorder, postorder, i, 0, inorder.size() - 1);
    }

    TreeNode *_buildTree(vector<int> &inorder, vector<int> &postorder,
                         int &posti, int inBegin, int inEnd)
    {
        if (inBegin > inEnd)
            return nullptr;

        TreeNode *root = new TreeNode(postorder[posti]);

        int rooti = inBegin;
        while (rooti <= inEnd)
            if (inorder[rooti] == postorder[posti])
                break;
            else
                rooti++;

        posti--;
        root->right = _buildTree(inorder, postorder, posti, rooti + 1, inEnd);
        root->left = _buildTree(inorder, postorder, posti, inBegin, rooti - 1);

        return root;
    }

    // 3
    string tree2str(TreeNode *root)
    {
        if (root == nullptr)
            return "";

        string ret = to_string(root->val);

        if (root->left || root->right)
        {
            ret += '(';
            ret += tree2str(root->left);
            ret += ')';
        }

        if (root->right)
        {
            ret += '(';
            ret += tree2str(root->right);
            ret += ')';
        }

        return ret;
    }

    // 4
    int deleteAndEarn(vector<int> &nums)
    {
        const int N = 10001;
        int arr[N] = {0};
        for (auto n : nums)
            arr[n] += n;

        vector<int> f(N), g(N);
        for (int i = 1; i < N; i++)
        {
            g[i] = max(g[i - 1], f[i - 1]);
            f[i] = g[i - 1] + arr[i];
        }

        return max(f[N - 1], g[N - 1]);
    }

    // 5
    int massage(vector<int> &nums)
    {
        // sort(nums.begin(),nums.end());
        int n = nums.size();
        if (n == 0)
            return 0;
        vector<int> f(n), g(n);
        f[0] = nums[0];

        for (int i = 1; i < n; i++)
        {
            f[i] = g[i - 1] + nums[i];
            g[i] = max(f[i - 1], g[i - 1]);
        }

        return max(f[n - 1], g[n - 1]);
    }

    // 6
    unordered_map<char, unordered_set<char>> edges;
    unordered_map<char, int> in;
    bool check = false;
    string alienOrder(vector<string> &words)
    {
        int n = words.size();
        for (auto &word : words)
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
        for (auto &[a, b] : in)
            if (!b)
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

    void add(string &s1, string &s2)
    {
        int n = min(s1.size(), s2.size());
        int i = 0;

        for (; i < n; i++)
        {
            if (s1[i] != s2[i])
            {
                char a = s1[i], b = s2[i]; // a->b
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
    }
};