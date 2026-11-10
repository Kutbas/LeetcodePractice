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
    int lenLongestFibSubseq(vector<int> &arr)
    {
        int n = arr.size();
        unordered_map<int, int> hash;
        for (int i = 0; i < n; i++)
            hash[arr[i]] = i;

        int ret = 2;
        vector<vector<int>> dp(n, vector<int>(n, 2));
        for (int j = 2; j < n; j++)
            for (int i = 1; i < j; i++)
            {
                int a = arr[j] - arr[i];
                if (a < arr[i] && hash.count(a))
                    dp[i][j] = dp[hash[a]][i] + 1;
                ret = max(ret, dp[i][j]);
            }

        return ret < 3 ? 0 : ret;
    }

    // 2
    string reverseStr(string s, int k)
    {
        int n = s.size();

        for (int i = 0; i < n; i += 2 * k)
        {
            int right = min(n, i + k);
            reverse(s.begin() + i, s.begin() + right);
        }

        return s;
    }

    // 3
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
};