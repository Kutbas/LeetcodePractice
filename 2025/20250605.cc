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
    bool validateStackSequences(vector<int> &pushed, vector<int> &popped)
    {
        int i = 0, n = popped.size();
        stack<int> st;

        for (auto n : pushed)
        {
            st.push(n);
            while (st.size() && st.top() == popped[i])
            {
                st.pop();
                i++;
            }
        }

        return i == n;
    }

    typedef pair<string, int> PSI;

    struct cmp
    {
        bool operator()(const PSI *p1, const PSI *p2)
        {
            if (p1->second == p2->second)
                return p1->first > p2->first;
            return p1->second < p2->second;
        }
    };

    vector<string> topKFrequent(vector<string> &words, int k)
    {
        vector<string> ret;
        unordered_map<string, int> hash;
        for (auto word : words)
            hash[word]++;

        priority_queue<PSI, vector<PSI>, cmp> q;
        for (auto [a, b] : hash)
            q.push({a, b});

        while (k--)
        {
            auto [a, b] = q.top();
            q.pop();
            ret.push_back(a);
        }

        return ret;
    }

    int minOperations(vector<int> &nums, int x)
    {
        int sum = 0;
        for (auto n : nums)
            sum += n;
        int target = sum - x;

        int ret = INT_MIN;

        for (int left = 0, right = 0, tmp = 0; right < nums.size(); right++)
        {
            tmp += nums[right];
            while (tmp > target)
                tmp -= nums[left++];
            if (tmp == target)
                ret = max(ret, right - left + 1);
        }

        return ret == INT_MIN ? -1 : nums.size() - ret;
    }

    string removeDuplicates(string s)
    {
        string ret;
        for (char ch : s)
        {
            if (ret.size() && ch == ret.back())
                ret.pop_back();
            else
                ret += ch;
        }
        return ret;
    }
};

class LRUCache
{
public:
    LRUCache(int capacity)
        : _capacity(capacity)
    {
    }

    int get(int key)
    {
        auto ret = _hash.find(key);
        if (ret != _hash.end())
        {
            LtItor it = ret->second;
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
            LtItor it = ret->second;
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
    typedef list<pair<int, int>>::iterator LtItor;
    list<pair<int, int>> _list;
    unordered_map<int, LtItor> _hash;
    int _capacity;
};