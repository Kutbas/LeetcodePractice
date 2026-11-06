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
    vector<int> smallestK(vector<int> &arr, int k)
    {
        srand(time(nullptr));
        quickSort(arr, 0, arr.size() - 1, k);
        return {arr.begin(), arr.begin() + k};
    }

    int getRandom(vector<int> &nums, int left, int right)
    {
        int r = rand();
        return nums[r % (right - left + 1) + left];
    }

    void quickSort(vector<int> &nums, int l, int r, int k)
    {
        if (l >= r)
            return;

        int i = l, left = l - 1, right = r + 1;
        int key = getRandom(nums, l, r);
        while (i < right)
        {
            if (nums[i] < key)
                swap(nums[i++], nums[++left]);
            else if (nums[i] == key)
                i++;
            else
                swap(nums[i], nums[--right]);
        }

        int lRange = left - l + 1, mRange = (right - 1) - (left + 1) + 1;
        if (lRange >= k)
            quickSort(nums, l, left, k);
        else if (lRange + mRange >= k)
            return;
        else
            quickSort(nums, right, r, k - lRange - mRange);
    }

    // 2
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

    // 3
    int maxProfit(vector<int> &prices)
    {
        const int INF = 0x3f3f3f;
        int n = prices.size();

        vector<int> f(n, -INF);
        auto g = f, c = f;
        g[0] = c[0] = 0;
        f[0] = -prices[0];

        for (int i = 1; i < n; i++)
        {
            f[i] = max(f[i - 1], g[i - 1] - prices[i]);
            g[i] = max(g[i - 1], c[i - 1]);
            c[i] = f[i - 1] + prices[i];
        }

        return max(g[n - 1], c[n - 1]);
    }

    // 4
    typedef pair<int, int> PII;

    struct cmp
    {
        bool operator()(const PII &a, const PII &b)
        {
            return a.second > b.second;
        }
    };

    int networkDelayTime(vector<vector<int>> &times, int n, int k)
    {
        const int INF = 0x3f3f3f;
        vector<vector<PII>> graph(n + 1);
        for (auto &t : times)
            graph[t[0]].push_back({t[1], t[2]});

        vector<int> dist(n + 1, INF);
        dist[k] = 0;

        priority_queue<PII, vector<PII>, cmp> q;
        q.push({k, 0});

        while (q.size())
        {
            auto [u, d] = q.top();
            q.pop();

            if (dist[u] > d)
                continue;

            for (auto [v, w] : graph[u])
            {
                if (dist[u] + w < dist[v])
                {
                    dist[v] = dist[u] + w;
                    q.push({v, dist[v]});
                }
            }
        }

        int ret = 0;
        for (int i = 1; i <= n; i++)
            ret = max(ret, dist[i]);

        return ret == INF ? -1 : ret;
    }

    // 5
    vector<int> ret;
    vector<int> postorderTraversal(TreeNode *root)
    {
        postOrder(root);
        return ret;
    }

    void postOrder(TreeNode *root)
    {
        if (root == nullptr)
            return;

        postOrder(root->left);
        postOrder(root->right);

        ret.push_back(root->val);
    }
};