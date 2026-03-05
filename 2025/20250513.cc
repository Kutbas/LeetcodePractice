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

typedef pair<string, int> PSI;

struct cmp
{
    bool operator()(const PSI &a, const PSI &b)
    {
        if (a.second == b.second)
            return a.first < b.first;
        return a.second > b.second;
    }
};

class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        unordered_map<int, int> hash;

        for (int i = 0; i < nums.size(); i++)
        {
            if (hash.count(target - nums[i]))
                return {i, hash[target - nums[i]]};
            hash[nums[i]] = i;
        }
        return {-1, -1};
    }

    vector<string> topKFrequent(vector<string> &words, int k)
    {
        unordered_map<string, int> hash;
        for (auto word : words)
            hash[word]++;

        priority_queue<PSI, vector<PSI>, cmp> q;
        for (auto &[a, b] : hash)
        {
            q.push({a, b});
            if (q.size() > k)
                q.pop();
        }

        vector<string> ret;
        while (q.size())
        {
            ret.push_back(q.top().first);
            q.pop();
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }

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

    int ladderLength(string beginWord, string endWord, vector<string> &wordList)
    {
        unordered_set<string> hash(wordList.begin(), wordList.end());
        unordered_set<string> vis;

        if (beginWord == endWord)
            return 0;
        if (!hash.count(endWord))
            return 0;

        int ret = 0;
        queue<string> q;
        q.push(beginWord);
        vis.insert(beginWord);

        while (q.size())
        {
            ret++;
            int sz = q.size();
            while (sz--)
            {
                auto t = q.front();
                q.pop();
                for (int i = 0; i < t.size(); i++)
                {
                    string tmp = t;
                    for (char ch = 'a'; ch <= 'z'; ch++)
                    {
                        tmp[i] = ch;
                        if (hash.count(tmp) && !vis.count(tmp))
                        {
                            if (tmp == endWord)
                                return ret;
                            q.push(tmp);
                            vis.insert(tmp);
                        }
                    }
                }
            }
        }

        return 0;
    }

    string decodeString(string s)
    {
        stack<int> nums;
        stack<string> st;
        int n = s.size(), i = 0;

        while (i < n)
        {
            if (s[i] >= '0' && s[i] <= '9')
            {
                int tmp = 0;
                while (s[i] >= '0' && s[i] <= '9')
                    tmp = tmp * 10 + (s[i] - '0');
                nums.push(tmp);
            }
            else if (s[i] == '[')
            {
                i++;
                string tmp = "";
                while (s[i] >= 'a' && s[i] <= 'z')
                    tmp += s[i++];
                st.push(tmp);
            }
            else if (s[i] == ']')
            {
                string tmp = st.top();
                st.pop();
                int k = nums.top();
                while (k--)
                    st.top() += tmp;
            }
            else
            {
                string tmp;
                while (i < n && s[i] >= 'a' && s[i] <= 'z')
                    tmp += s[i++];
                st.top() += tmp;
            }
        }
        return st.top();
    }

    string decodeString(string s)
    {
        stack<int> nums;
        stack<string> st;
        st.push("");
        int i = 0, n = s.size();

        while (i < n)
        {
            if (s[i] >= '0' && s[i] <= '9')
            {
                int tmp = 0;
                while (s[i] >= '0' && s[i] <= '9')
                    tmp = tmp * 10 + (s[i++] - '0');
                nums.push(tmp);
            }
            else if (s[i] == '[')
            {
                i++;
                string tmp = "";
                while (s[i] >= 'a' && s[i] <= 'z')
                    tmp += s[i++];
                st.push(tmp);
            }
            else if (s[i] == ']')
            {
                string tmp = st.top();
                st.pop();
                int k = nums.top();
                nums.pop();

                while (k--)
                    st.top() += tmp;
                i++;
            }
            else
            {
                string tmp = "";
                while (s[i] >= 'a' && s[i] <= 'z')
                    tmp += s[i++];
                st.top() += tmp;
            }
        }

        return st.top();
    }

    string decodeString(string s)
    {
        stack<int> nums;
        stack<string> st;
        st.push("");
        int i = 0, n = s.size();

        while (i < n)
        {
            if (s[i] >= '0' && s[i] <= '9')
            {
                int tmp = 0;
                while (s[i] >= '0' && s[i] <= '9')
                    tmp = tmp * 10 + (s[i++] - '0');
                nums.push(tmp);
            }
            else if (s[i] == '[')
            {
                i++;
                string tmp = "";
                while (s[i] >= 'a' && s[i] <= 'z')
                    tmp += s[i++];
                st.push(tmp);
            }
            else if (s[i] == ']')
            {
                string tmp = st.top();
                st.pop();
                int k = nums.top();
                nums.pop();

                while (k--)
                    st.top() += tmp;
                i++;
            }
            else
            {
                string tmp = "";
                while (s[i] >= 'a' && s[i] <= 'z')
                    tmp += s[i++];
                st.top() += tmp;
            }
        }

        return st.top();
    }
};