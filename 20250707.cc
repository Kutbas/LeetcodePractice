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
    bool lemonadeChange(vector<int> &bills)
    {
        int hash[128];
        for (auto x : bills)
        {
            if (x == 5)
                hash[5]++;
            else if (x == 10)
            {
                if (!hash[5])
                    return false;
                hash[5]--;
                hash[10]++;
            }
            else
            {
                if (hash[5] && hash[10])
                    hash[5]--, hash[10]--;
                else if (hash[5] >= 3)
                    hash[5] -= 3;
                else
                    return false;
            }
        }
        return true;
    }

    int halveArray(vector<int> &nums)
    {
        priority_queue<double> q;
        double sum = 0.0;

        for (int x : nums)
        {
            q.push(x);
            sum += x;
        }

        sum /= 2.0;

        int count = 0;
        while (sum > 0)
        {
            double t = q.top() / 2.0;
            q.pop();
            q.push(t);

            sum -= t;
            count++;
        }
        return count;
    }

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    bool vis[51][51];
    int maxAreaOfIsland(vector<vector<int>> &grid)
    {
        m = grid.size(), n = grid[0].size();
        int ret = 0;
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                if (grid[i][j] && !vis[i][j])
                    ret = max(ret, dfs(grid, i, j));

        return ret;
    }

    int dfs(vector<vector<int>> &grid, int i, int j)
    {
        queue<pair<int, int>> q;
        q.push({i, j});
        vis[i][j] = true;
        int ret = 1;

        while (q.size())
        {
            auto [a, b] = q.front();
            q.pop();
            for (int k = 0; k < 4; k++)
            {
                int x = a + dx[k], y = b + dy[k];
                if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && grid[x][y])
                {
                    q.push({x, y});
                    vis[x][y] = true;
                    ++ret;
                }
            }
        }

        return ret;
    }

    int halveArray(vector<int> &nums)
    {
        priority_queue<double> q;
        double sum = 0.0;
        for (auto n : nums)
        {
            q.push(n);
            sum += n;
        }

        sum /= 2.0;
        int ret = 0;
        while (sum > 0)
        {
            double t = q.top() / 2.0;
            q.pop();
            q.push(t);

            sum -= t;
            ret++;
        }

        return ret;
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
        for (auto &word : words)
            hash[word]++;

        priority_queue<PSI, vector<PSI>, cmp> q;
        for (auto &pair : hash)
            q.push(pair);

        vector<string> ret;

        while (k--)
        {
            auto [a, b] = q.top();
            q.pop();
            ret.push_back(a);
        }

        return ret;
    }

    int searchInsert(vector<int> &nums, int target)
    {
        int left = 0, right = nums.size() - 1;
        while (left < right)
        {
            int mid = left + (right - left + 1) / 2;
            if (nums[mid] <= target)
                left = mid;
            else
                right = mid - 1;
        }

        return nums[left] < target ? left + 1 : left;
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
            if (_hash.size() == _capacity)
            {
                pair<int, int> back = _list.back();
                _list.pop_back();
                _hash.erase(back.first);
            }
            _list.push_front({key, value});
            _hash[key] = _list.begin();
        }
    }

private:
    typedef list<pair<int, int>>::iterator LtItor;
    int _capacity;
    list<pair<int, int>> _list;
    unordered_map<int, LtItor> _hash;
};