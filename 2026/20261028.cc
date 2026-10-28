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
#include <regex>
#include <map>
#include <set>
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
    vector<int> productExceptSelf(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> f(n + 1);
        auto g = f;
        f[0] = g[n - 1] = 1;

        for (int i = 1; i <= n; i++)
            f[i] = f[i - 1] * nums[i - 1];
        for (int i = n - 2; i >= 0; i--)
            g[i] = g[i + 1] * nums[i + 1];

        vector<int> ret(n);
        for (int i = 0; i < n; i++)
            ret[i] = f[i] * g[i];

        return ret;
    }

    // 2
    int waysToStep(int n)
    {
        if (n < 3)
            return n;

        const int MOD = 1e9 + 7;
        int a = 1, b = 2, c = 4;

        while (n-- != 3)
        {
            int d = (((a + b) % MOD) + c) % MOD;
            a = b, b = c, c = d;
        }

        return c;
    }

    // 3
    class LRUCache
    {
    public:
        LRUCache(int capacity) : _capacity(capacity)
        {
        }

        int get(int key)
        {
            auto ret = _hash.find(key);
            if (ret != _hash.end())
            {
                auto it = ret->second;
                _list.splice(_list.begin(), _list, it);
                return it->second;
            }
            return -1;
        }

        void put(int key, int value)
        {
            auto ret = _hash.find(key);
            if (ret != _hash.end())
            {
                auto it = ret->second;
                it->second = value;
                _list.splice(_list.begin(), _list, it);
            }
            else
            {
                if (_hash.size() == _capacity)
                {
                    pair<int, int> back = _list.back();
                    _hash.erase(back.first);
                    _list.pop_back();
                }
                _list.push_front({key, value});
                _hash[key] = _list.begin();
            }
        }

    private:
        typedef list<pair<int, int>>::iterator LstItor;
        int _capacity;
        list<pair<int, int>> _list;
        unordered_map<int, LstItor> _hash;
    };

    // 4
    int ret = 0;
    int sumNumbers(TreeNode *root)
    {
        dfs(root, 0);
        return ret;
    }

    void dfs(TreeNode *root, int sum)
    {
        sum = sum * 10 + root->val;

        if (root->left == nullptr && root->right == nullptr)
        {
            ret += sum;
            return;
        }

        if (root->left)
            dfs(root->left, sum);
        if (root->right)
            dfs(root->right, sum);
    }

    // 5
    int findContentChildren(vector<int> &g, vector<int> &s)
    {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());

        int m = g.size(), n = s.size(), ret = 0;
        for (int i = 0, j = 0; i < m && j < n; i++, j++)
        {
            while (j < n && s[j] < g[i])
                j++;

            if (j < n)
                ret++;
        }

        return ret;
    }

    // 6
    int integerReplacement(int n)
    {
        int ret = 0;

        while (n != 1)
        {
            if (n % 2 == 0)
            {
                n /= 2;
                ret++;
            }
            else
            {
                if (n == 3)
                {
                    n = 1;
                    ret += 2;
                }
                else if (n % 4 == 1)
                {
                    n /= 2;
                    ret += 2;
                }
                else
                {
                    n = n / 2 + 1;
                    ret += 2;
                }
            }
        }

        return ret;
    }

    // 7
    int findSubstringInWraproundString(string s)
    {
        int n = s.size();
        vector<int> dp(n, 1);

        for (int i = 1; i < n; i++)
            if ((s[i - 1] == 'z' && s[i] == 'a') || s[i - 1] + 1 == s[i])
                dp[i] += dp[i - 1];

        int hash[26] = {0};
        for (int i = 0; i < n; i++)
        {
            int index = s[i] - 'a';
            hash[index] = max(hash[index], dp[i]);
        }

        int ret = 0;
        for (auto i : hash)
            ret += i;

        return ret;
    }

    // 8
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
};