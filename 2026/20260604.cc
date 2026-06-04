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
    // 1
    int pivotIndex(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> f(n), g(n);

        for (int i = 1; i < n; i++)
            f[i] = f[i - 1] + nums[i - 1];
        for (int i = n - 2; i >= 0; i--)
            g[i] = g[i + 1] + nums[i + 1];

        for (int i = 0; i < n; i++)
            if (f[i] == g[i])
                return i;

        return -1;
    }

    // 3
    unordered_map<char, int> in;
    unordered_map<char, unordered_set<char>> edges;
    bool check = false;
    string alienOrder(vector<string> &words)
    {
        for (auto &word : words)
            for (auto &ch : word)
                in[ch] = 0;

        int n = words.size();
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
            {
                add(words[i], words[j]);
                if (check)
                    return "";
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

            for (auto a : edges[t])
                if (--in[a] == 0)
                    q.push(a);
        }

        for (auto &[a, b] : in)
            if (b)
                return "";

        return ret;
    }

    void add(const string &s1, const string &s2)
    {
        int n = min(s1.size(), s2.size()), i = 0;

        for (; i < n; i++)
        {
            if (s1[i] != s2[i])
            {
                char a = s1[i], b = s2[i];
                if (!edges.count(a) || !edges[a].count(b))
                {
                    in[b]++;
                    edges[a].insert(b);
                }
                break;
            }
        }

        if (i < s1.size() && i == s2.size())
            check = true;
    }

    // 4
    ListNode *reverseList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *newhead = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;

        return newhead;
    }

    // 5
    bool wordBreak(string s, vector<string> &wordDict)
    {
        unordered_set<string> hash(wordDict.begin(), wordDict.end());
        int n = s.size();

        vector<bool> dp(n + 1);
        dp[0] = true;
        s = " " + s;

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

    // 7
    vector<int> intersection(vector<int> &nums1, vector<int> &nums2)
    {
        int hash[1001] = {0};
        vector<int> ret;

        for (auto n : nums1)
            if (hash[n] == 0)
                hash[n]++;
        for (auto n : nums2)
            if (--hash[n] == 0)
                ret.push_back(n);

        return ret;
    }

    // 8
    string addStrings(string num1, string num2)
    {
        int m = num1.size(), n = num2.size();

        string ret;
        int cur1 = m - 1, cur2 = n - 1, t = 0;
        while (cur1 >= 0 || cur2 >= 0 || t)
        {
            if (cur1 >= 0)
                t += num1[cur1--] - '0';
            if (cur2 >= 0)
                t += num2[cur2--] - '0';

            ret += to_string(t % 10);
            t /= 10;
        }

        reverse(ret.begin(), ret.end());

        return ret[0] == '0' ? "0" : ret;
    }

    // 9
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
};

// 2
class KthLargest
{
public:
    KthLargest(int k, vector<int> &nums) : _k(k)
    {
        for (auto n : nums)
        {
            q.push(n);
            if (q.size() > _k)
                q.pop();
        }
    }

    int add(int val)
    {
        q.push(val);
        if (q.size() > _k)
            q.pop();

        return q.top();
    }

private:
    int _k;
    priority_queue<int, vector<int>, greater<int>> q;
};

// 6
string s;

string &change(string &s)
{
    if (s[0] >= 'A' && s[0] <= 'Z')
        s[0] = tolower(s[0]);
    return s;
}

int main()
{
    getline(cin, s);

    regex re{R"([a-zA-Z]+)"};
    sregex_token_iterator begin(s.begin(), s.end(), re, 0);
    sregex_token_iterator end;

    vector<string> words(begin, end);
    map<string, int> hash;

    for (auto &word : words)
    {
        string &tmp = change(word);
        hash[tmp]++;
    }

    for (auto &[a, b] : hash)
        cout << a << ":" << b << endl;

    return 0;
}