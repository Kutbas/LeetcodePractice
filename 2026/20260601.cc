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
    // 2
    int maxProfit(vector<int> &prices)
    {
        int n = prices.size(), ret = 0;
        for (int left = 0, right = 0; right < n; right++)
        {
            while (right + 1 < n && prices[right + 1] > prices[right])
                right++;
            ret += prices[right] - prices[left];
            left = right + 1;
        }

        return ret;
    }

    // 3
    vector<int> advantageCount(vector<int> &nums1, vector<int> &nums2)
    {
        sort(nums1.begin(), nums1.end());

        int n = nums1.size();
        vector<int> index2(n);
        for (int i = 0; i < n; i++)
            index2[i] = i;

        sort(index2.begin(), index2.end(), [&](const int i, const int j)
             { return nums2[i] < nums2[j]; });

        vector<int> ret(n);
        int left = 0, right = n - 1;
        for (auto n : nums1)
        {
            if (n > nums2[index2[left]])
                ret[index2[left++]] = n;
            else
                ret[index2[right--]] = n;
        }

        return ret;
    }

    // 4
    int findLongestChain(vector<vector<int>> &pairs)
    {
        sort(pairs.begin(), pairs.end());

        int n = pairs.size(), ret = 1;
        vector<int> dp(n, 1);

        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < i; j++)
            {
                int a = pairs[j][1], b = pairs[i][0];
                if (a < b)
                    dp[i] = max(dp[i], dp[j] + 1);
            }
            ret = max(ret, dp[i]);
        }

        return ret;
    }

    // 5
    int longestSubsequence(vector<int> &arr, int difference)
    {
        unordered_map<int, int> hash;
        hash[arr[0]] = 1;
        int ret = 1, n = arr.size();

        for (int i = 1; i < n; i++)
        {
            hash[arr[i]] = hash[arr[i] - difference] + 1;
            ret = max(ret, hash[arr[i]]);
        }

        return ret;
    }

    // 6
    bool wordBreak(string s, vector<string> &wordDict)
    {
        unordered_set<string> hash(wordDict.begin(), wordDict.end());

        int n = s.size();
        s = " " + s;

        vector<bool> dp(n + 1);
        dp[0] = true;

        for (int i = 1; i <= n; i++)
            for (int j = i; j >= 1; j--)
            {
                if (dp[j - 1] && hash.count(s.substr(j, i - j + 1)))
                {
                    dp[i] = true;
                    break;
                }
            }

        return dp[n];
    }
};

class LRUCache
{
public:
    // 1
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
    unordered_map<int, LstItor> _hash;
    list<pair<int, int>> _list;
};