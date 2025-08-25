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
    vector<int> rearrangeBarcodes(vector<int> &b)
    {
        unordered_map<int, int> hash;
        int maxVal = 0, maxCount = 0;

        for (auto x : b)
        {
            if (maxCount < ++hash[x])
            {
                maxCount = hash[x];
                maxVal = x;
            }
        }

        // 先处理出现次数最多的数
        int n = b.size(), index = 0;
        vector<int> ret(n);
        for (int i = 0; i < maxCount; i++)
        {
            ret[index] = maxVal;
            index += 2;
        }

        // 处理剩下的数
        hash.erase(maxVal);
        for (auto &[x, y] : hash)
        {
            for (int i = 0; i < y; i++)
            {
                if (index >= n)
                    index = 1;
                ret[index] = x;
                index += 2;
            }
        }

        return ret;
    }

    // 1
    vector<vector<int>> ret;
    vector<int> path;
    vector<vector<int>> subsets(vector<int> &nums)
    {
        dfs(nums, 0);
        return ret;
    }

    void dfs(vector<int> &nums, int pos)
    {
        ret.push_back(path);

        if (pos == nums.size())
        {
            return;
        }

        for (int i = pos; i < nums.size(); i++)
        {
            path.push_back(nums[i]);
            dfs(nums, i + 1);
            path.pop_back();
        }
    }

    // 2
    int aim, ret1 = 0;
    int findTargetSumWays(vector<int> &nums, int target)
    {
        aim = target;
        dfs(nums, 0, 0);
        return ret1;
    }

    void dfs(vector<int> &nums, int pos, int sum)
    {
        if (pos == nums.size())
        {
            if (sum == aim)
                ret1++;
            return;
        }

        dfs(nums, pos + 1, sum + nums[pos]);
        dfs(nums, pos + 1, sum - nums[pos]);
    }

    // 3
    int memo[101][101];
    int uniquePaths(int m, int n)
    {
        return dfs(m, n);
    }

    int dfs(int m, int n)
    {
        if (memo[m][n])
            return memo[m][n];

        if (m == 0 || n == 0)
            return 0;

        if (m == 1 && n == 1)
        {
            memo[m][n] = 1;
            return 1;
        }

        memo[m][n] = dfs(m, n - 1) + dfs(m - 1, n);
        return memo[m][n];
    }

    // 4
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
        ListNode *ret = new ListNode(0);
        ListNode *prev = ret;
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
        prev = ret->next;
        delete ret;
        return prev;
    }

    // 5
    unordered_map<char, unordered_set<char>> hash;
    unordered_map<char, int> in;
    bool check = false;
    string alienOrder(vector<string> &words)
    {
        for (auto word : words)
            for (auto ch : word)
                in[ch] = 0;

        for (int i = 0; i < words.size(); i++)
        {
            for (int j = i + 1; j < words.size(); j++)
            {
                add(words[i], words[j]);
                if (check)
                    return "";
            }
        }

        string ret;
        queue<char> q;
        for (auto [a, b] : in)
            if (b == 0)
                q.push(a);

        while (q.size())
        {
            auto t = q.front();
            q.pop();
            ret += t;
            for (auto a : hash[t])
                if (--in[a] == 0)
                    q.push(a);
        }

        for (auto &[a, b] : in)
            if (b)
                return "";
        return ret;
    }

    void add(string &s1, string &s2)
    {
        int n = min(s1.size(), s2.size());
        int i = 0;
        for (; i < n; i++)
        {
            if (s1[i] != s2[i])
            {
                char a = s1[i], b = s2[i]; // a->b
                if (!hash.count(a) || !hash[a].count(b))
                {
                    hash[a].insert(b);
                    in[b]++;
                }
                break;
            }
        }
        // abc ab
        if (i == s2.size() && i < s1.size())
            check = true;
    }

    // 6
    bool vis[7];
    vector<vector<int>> Ret;
    vector<int> Path;
    vector<vector<int>> permute(vector<int> &nums)
    {
        DFS(nums, 0);
        return Ret;
    }

    void DFS(vector<int> &nums, int pos)
    {
        if (pos == nums.size())
        {
            Ret.push_back(Path);
            return;
        }

        for (int i = 0; i < nums.size(); i++)
        {
            if (!vis[i])
            {
                vis[i] = true;
                Path.push_back(nums[i]);
                DFS(nums, pos + 1);
                Path.pop_back();
                vis[i] = false;
            }
        }
    }

    string reorganizeString(string s)
    {
        int hash[26] = {0};
        char maxChar = ' ';
        int maxCount = 0;

        for (auto ch : s)
        {
            if (maxCount < ++hash[ch - 'a'])
            {
                maxChar = ch;
                maxCount = hash[ch - 'a'];
            }
        }

        int n = s.size();
        if (maxCount > (n + 1) / 2)
            return "";

        string ret(n, ' ');
        int index = 0;

        for (int i = 0; i < maxCount; i++)
        {
            ret[index] = maxChar;
            index += 2;
        }

        hash[maxChar - 'a'] = 0;
        for (int i = 0; i < 26; i++)
        {
            for (int j = 0; j < hash[i]; j++)
            {
                if (index >= n)
                    index = 1;
                ret[index] = 'a' + i;
                index += 2;
            }
        }

        return ret;
    }
};