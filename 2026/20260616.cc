#include <mutex>
#include <vector>
#include <algorithm>
#include <climits>
#include <list>
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
    int minOperations(vector<int> &nums, int x)
    {
        int sum = 0, n = nums.size();
        for (auto n : nums)
            sum += n;

        int aim = sum - x;
        if (aim < 0)
            return -1;

        int ret = INT_MIN;
        for (int left = 0, right = 0, tmp = 0; right < n; right++)
        {
            tmp += nums[right];
            while (tmp > aim)
                tmp -= nums[left++];
            if (tmp == aim)
                ret = max(ret, right - left + 1);
        }

        return ret == INT_MIN ? -1 : nums.size() - ret;
    }

    // 3
    vector<vector<int>> ret;
    vector<int> path;
    bool vis[7] = {0};
    vector<vector<int>> permute(vector<int> &nums)
    {
        dfs(nums);
        return ret;
    }

    void dfs(vector<int> &nums)
    {
        if (path.size() == nums.size())
        {
            ret.push_back(path);
            return;
        }

        for (int i = 0; i < nums.size(); i++)
        {
            if (!vis[i])
            {
                path.push_back(nums[i]);
                vis[i] = true;
                dfs(nums);
                vis[i] = false;
                path.pop_back();
            }
        }
    }

    // 4
    int lastStoneWeightII(vector<int> &stones)
    {
        int n = stones.size(), sum = 0;
        for (auto s : stones)
            sum += s;

        int m = sum / 2;
        vector<vector<int>> dp(n + 1, vector<int>(m + 1));
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
            {
                dp[i][j] = dp[i - 1][j];
                if (j >= stones[i - 1])
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - stones[i - 1]] + stones[i - 1]);
            }

        return sum - 2 * dp[n][m];
    }

    // 5
    string reverseWords(string s)
    {
        int n = s.size(), start = 0;
        for (int i = 0; i <= n; i++)
            if (s[i] == ' ' || i == n)
            {
                reverse(s.begin() + start, s.begin() + i);
                start = i + 1;
            }

        return s;
    }

    // 6
    int firstUniqChar(string s)
    {
        int hash[128] = {0};
        for (char ch : s)
            ++hash[ch];

        for (int i = 0; i < s.size(); i++)
            if (hash[s[i]] == 1)
                return i;

        return -1;
    }

    // 7
    string ret;
    string tree2str(TreeNode *root)
    {
        dfs(root);
        return ret;
    }

    void dfs(TreeNode *root)
    {
        if (root == nullptr)
            return;

        ret += to_string(root->val);

        if (root->left || root->right)
        {
            ret += '(';
            dfs(root->left);
            ret += ')';
        }

        if (root->right)
        {
            ret += '(';
            dfs(root->right);
            ret += ')';
        }
    }
};

// 2
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