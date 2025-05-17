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
    int subarraySum(vector<int> &nums, int k)
    {
        unordered_map<int, int> hash;
        int sum = 0, ret = 0;

        for (auto n : nums)
        {
            sum += n;
            if (hash.count(sum - k))
                ret += hash[sum - k];
            hash[sum]++;
        }

        return ret;
    }

    bool check = false;
    unordered_map<char, unordered_set<char>> edges;
    unordered_map<char, int> in;

    string alienOrder(vector<string> &words)
    {
        string ret;

        for (auto &word : words)
            for (auto ch : word)
                in[ch] = 0;

        for (int i = 0; i < words.size(); i++)
            for (int j = i + 1; j < words.size(); j++)
            {
                add(words[i], words[j]);
                if (check)
                    return ret;
            }

        queue<char> q;
        for (auto [a, b] : in)
            if (b == 0)
                q.push(a);

        while (q.size())
        {
            auto t = q.front();
            q.pop();
            ret += t;

            for (auto a : edges[t])
                if (--in[a] == 0)
                    q.push(a);
        }

        for (auto [a, b] : in)
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
                char a = s1[i], b = s2[i]; // wrt wrf t->f
                if (!edges.count(a) || !edges[a].count(b))
                {
                    edges[a].insert(b);
                    in[b]++;
                }
                break;
            }
        }

        // s1=abc,s2=ab,false
        if (i < s1.size() && i == s2.size())
            check = true;
    }

    int findMaxLength(vector<int> &nums)
    {
        unordered_map<int, int> hash;
        hash[0] = 1;

        int sum = 0, ret = 0;

        for (int i = 0; i < nums.size(); i++)
        {
            sum += nums[i] == 0 ? -1 : 1;
            if (hash.count(sum))
                ret = max(ret, i - hash[sum]);
            hash[sum] = i;
        }

        return ret;
    }

    int minMutation(string startGene, string endGene, vector<string> &bank)
    {
        unordered_set<string> hash(bank.begin(), bank.end());
        unordered_set<string> vis;
        string change = "ACGT";

        if (startGene == endGene)
            return 0;
        if (!hash.count(endGene))
            return -1;

        queue<string> q;
        q.push(startGene);
        vis.insert(startGene);
        int ret = 0;

        while (q.size())
        {
            ret++;
            int sz = q.size();
            while (sz--)
            {
                auto t = q.front();
                q.pop();
                for (int i = 0; i < 8; i++)
                {
                    string tmp = t;
                    for (int j = 0; j < 4; j++)
                    {
                        tmp[i] = change[j];
                        if (hash.count(tmp) && !vis.count(tmp))
                        {
                            if (tmp == endGene)
                                return ret;
                            q.push(tmp);
                            vis.insert(tmp);
                        }
                    }
                }
            }
        }

        return -1;
    }

    int subarraysDivByK(vector<int> &nums, int k)
    {
        unordered_map<int, int> hash;
        hash[0] = 1;

        int sum = 0, ret = 0;

        for (auto n : nums)
        {
            sum += n;
            int r = (sum % k + k) % k;
            if (hash.count(r))
                ret += hash[r];
            hash[r]++;
        }
        return ret;
    }

    int minMutation(string startGene, string endGene, vector<string> &bank)
    {
        unordered_set<string> hash(bank.begin(), bank.end());
        unordered_set<string> vis;
        string change = "ATGC";

        if (startGene == endGene)
            return 0;
        if (!hash.count(endGene))
            return -1;

        queue<string> q;
        q.push(startGene);
        vis.insert(startGene);
        int ret = 0;

        while (q.size())
        {
            ret++;
            int sz = q.size();
            while (sz--)
            {
                auto t = q.front();
                q.pop();

                for (int i = 0; i < 8; i++)
                {
                    string tmp = t;
                    for (int j = 0; j < 4; j++)
                    {
                        tmp[i] = change[j];
                        if (hash.count(tmp) && !vis.count(tmp))
                        {
                            if (tmp == endGene)
                                return ret;
                            q.push(tmp);
                            vis.insert(tmp);
                        }
                    }
                }
            }
        }

        return -1;
    }

    vector<vector<int>> matrixBlockSum(vector<vector<int>> &mat, int k)
    {
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        vector<vector<int>> ret(m, vector<int>(n));

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1] + mat[i - 1][j - 1];

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                int x1 = max(0, i - k) + 1, y1 = max(0, j - k) + 1;
                int x2 = min(m - 1, i + k) + 1, y2 = min(n - 1, j + k) + 1;
                ret[i][j] = dp[x2][y2] - dp[x1 - 1][y2] - dp[x2][y1 - 1] + dp[x1 - 1][y1 - 1];
            }

        return ret;
    }

    void reorderList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr || head->next->next == nullptr)
            return;

        ListNode *slow = head, *fast = head;
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode *head2 = new ListNode(0);
        ListNode *cur = slow->next;
        slow->next = nullptr;

        while (cur)
        {
            ListNode *next = cur->next;
            cur->next = head2->next;
            head2->next = cur;
            cur = next;
        }

        ListNode *ret = new ListNode(0);
        ListNode *prev = ret;
        ListNode *cur1 = head, *cur2 = head2->next;

        while (cur1)
        {
            prev->next = cur1;
            prev = prev->next;
            cur1 = cur1->next;

            if (cur2)
            {
                prev->next = cur2;
                prev = prev->next;
                cur2 = cur2->next;
            }
        }

        prev = ret->next;
        delete head2, ret;
        return;
    }
};