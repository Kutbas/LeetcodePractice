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
    ListNode *reverseKGroup(ListNode *head, int k)
    {
        int n = 0;
        ListNode *cur = head;
        while (cur)
        {
            n++;
            cur = cur->next;
        }

        n /= k;
        ListNode *newhead = new ListNode(0);
        ListNode *prev = newhead;
        cur = head;

        for (int i = 0; i < n; i++)
        {
            ListNode *tmp = cur;
            for (int j = 0; j < k; j++)
            {
                ListNode *next = cur->next;
                cur->next = prev->next;
                prev->next = cur;
                cur = next;
            }

            prev = tmp;
        }

        prev->next = cur;
        prev = newhead->next;
        delete newhead;
        return prev;
    }

    vector<vector<int>> ret;
    vector<int> path;
    int N, K;
    vector<vector<int>> combine(int n, int k)
    {
        N = n, K = k;
        dfs(1);
        return ret;
    }

    void dfs(int pos)
    {
        if (path.size() == K)
        {
            ret.push_back(path);
            return;
        }

        for (int i = pos; i <= N; i++)
        {
            path.push_back(i);
            dfs(i + 1);
            path.pop_back();
        }
    }

    int totalFruit(vector<int> &fruits)
    {
        unordered_map<int, int> hash;
        int ret = INT_MIN;

        for (int left = 0, right = 0; right < fruits.size(); right++)
        {
            ++hash[fruits[right]];
            while (hash.size() > 2)
            {
                if (--hash[fruits[left]] == 0)
                    hash.erase(fruits[left]);
                left++;
            }
            ret = max(ret, right - left + 1);
        }

        return ret;
    }

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    typedef pair<int, int> PIR;
    int m, n;
    int cutOffTree(vector<vector<int>> &forest)
    {
        m = forest.size(), n = forest[0].size();
        vector<PIR> trees;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (forest[i][j] > 1)
                    trees.push_back({i, j});

        sort(trees.begin(), trees.end(), [&](const PIR &p1, const PIR &p2)
             { return forest[p1.first][p1.second] < forest[p2.first][p2.second]; });

        int ret = 0, bx = 0, by = 0;
        for (auto [a, b] : trees)
        {
            int step = DFS(forest, bx, by, a, b);
            if (step == -1)
                return -1;
            ret += step;
            bx = a, by = b;
        }

        return ret;
    }

    int DFS(vector<vector<int>> &forest, int bx, int by, int ex, int ey)
    {
        if (bx == ex && by == ey)
            return 0;

        bool vis[51][51] = {0};
        queue<PIR> q;
        q.push({bx, by});
        vis[bx][by] = true;
        int ret = 0;

        while (q.size())
        {
            ret++;
            int sz = q.size();
            while (sz--)
            {
                auto [a, b] = q.front();
                q.pop();
                for (int k = 0; k < 4; k++)
                {
                    int x = a + dx[k], y = b + dy[k];
                    if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && forest[x][y])
                    {
                        if (x == ex && y == ey)
                            return ret;
                        q.push({x, y});
                        vis[x][y] = true;
                    }
                }
            }
        }

        return -1;
    }

    int prev;
    bool isValidBST(TreeNode *root)
    {
        if (root->left == nullptr && root->right == nullptr)
        {
            prev = root->val;
            return true;
        }

        bool left = isValidBST(root->left);
        if (!left)
            return false;

        bool cur = false;
        if (prev < root->val)
            cur = true;
        if (!cur)
            return false;

        prev = root->val;
        bool right = isValidBST(root->right);
        return right;
    }

    vector<vector<int>> ret;
    vector<int> path;
    bool check[9];
    vector<vector<int>> permuteUnique(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        dfs2(nums, 0);
        return ret;
    }

    void dfs2(vector<int> &nums, int pos)
    {
        if (pos == nums.size())
        {
            ret.push_back(path);
            return;
        }

        for (int i = 0; i < nums.size(); i++)
        {
            if (check[i] || (i > 0 && nums[i] == nums[i - 1] && !check[i - 1]))
                continue;

            path.push_back(nums[i]);
            check[i] = true;
            dfs2(nums, i + 1);
            path.pop_back();
            check[i] = false;
        }
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