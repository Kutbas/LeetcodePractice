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
    vector<int> ret;
    vector<int> preorderTraversal(TreeNode *root)
    {
        if (root == nullptr)
            return ret;

        dfs(root);

        return ret;
    }

    void dfs(TreeNode *root)
    {
        if (root == nullptr)
            return;

        ret.push_back(root->val);
        dfs(root->left);
        dfs(root->right);
    }

    // 2
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
            else if (n == 3)
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
        return ret;
    }

    // 3
    int res = 0, aim;
    int findTargetSumWays(vector<int> &nums, int target)
    {
        aim = target;
        dfs(nums, 0, 0);
        return res;
    }

    void dfs(vector<int> &nums, int sum, int pos)
    {
        if (pos == nums.size())
        {
            if (sum == aim)
                res++;
            return;
        }

        dfs(nums, sum + nums[pos], pos + 1);
        dfs(nums, sum - nums[pos], pos + 1);
    }
};

// 4
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
            if (_capacity == _hash.size())
            {
                auto back = _list.back();
                _hash.erase(back.first);
                _list.pop_back();
            }
            _list.push_front({key, value});
            _hash[key] = _list.begin();
        }
    }

private:
    int _capacity;
    typedef list<pair<int, int>>::iterator LstItor;
    list<pair<int, int>> _list;
    unordered_map<int, LstItor> _hash;
};

// 5
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

    regex re{R"([a-zA-z]+)"};

    sregex_token_iterator begin(s.begin(), s.end(), re, 0);
    sregex_token_iterator end;

    vector<string> words(begin, end);
    map<string, int> hash;
    for (auto &word : words)
    {
        string tmp = change(word);
        hash[word]++;
    }

    for (auto &[a, b] : hash)
        cout << a << ":" << b << endl;

    return 0;
}