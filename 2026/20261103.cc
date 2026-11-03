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
    vector<vector<string>> groupAnagrams(vector<string> &strs)
    {
        vector<vector<string>> ret;

        map<string, vector<string>> hash;
        for (auto s : strs)
        {
            string tmp = s;
            sort(tmp.begin(), tmp.end());
            hash[tmp].push_back(s);
        }

        for (auto [a, b] : hash)
            ret.push_back(b);

        return ret;
    }

    // 2
    int getMaxLen(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> f(n + 1);
        auto g = f;

        int ret = 0;
        for (int i = 1; i <= n; i++)
        {
            if (nums[i - 1] > 0)
            {
                f[i] = f[i - 1] + 1;
                g[i] = g[i - 1] == 0 ? 0 : g[i - 1] + 1;
            }
            else if (nums[i - 1] < 0)
            {
                f[i] = g[i - 1] == 0 ? 0 : g[i - 1] + 1;
                g[i] = f[i - 1] + 1;
            }
            ret = max(ret, f[i]);
        }

        return ret;
    }

    // 3
    vector<string> uncommonFromSentences(string s1, string s2)
    {
        unordered_map<string, int> hash;

        auto countWord = [&](const string &s)
        {
            string word;
            istringstream iss(s);

            while (iss >> word)
                hash[word]++;
        };

        countWord(s1);
        countWord(s2);

        vector<string> ret;
        for (auto [a, b] : hash)
            if (b == 1)
                ret.push_back(a);

        return ret;
    }

    // 4
    string reverseWords(string s)
    {
        int n = s.size(), start = 0;

        for (int i = 0; i <= n; i++)
        {
            if (s[i] == ' ' || i == n)
            {
                reverse(s.begin() + start, s.begin() + i);
                start = i + 1;
            }
        }

        return s;
    }

    // 5
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

            for (auto &[v, w] : graph[u])
            {
                if (dist[u] + w < dist[v])
                {
                    dist[v] = w + dist[u];
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