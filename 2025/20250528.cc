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
    bool check = false;
    unordered_map<char, unordered_set<char>> hash;
    unordered_map<char, int> in;

    string alienOrder(vector<string> &words)
    {

        for (auto word : words)
            for (auto ch : word)
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

            for (auto a : hash[t])
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
        int i = 0;
        int n = min(s1.size(), s2.size());

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
        if (i < s1.size() && i == s2.size())
            check = true;
    }

    bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
    {
        unordered_map<int, vector<int>> edges;
        vector<int> in(numCourses);

        for (auto &e : prerequisites)
        {
            int a = e[0], b = e[1]; // b->a
            edges[b].push_back(a);
            in[a]++;
        }

        queue<int> q;
        for (int i = 0; i < numCourses; i++)
            if (in[i] == 0)
                q.push(i);

        vector<int> ret;
        while (q.size())
        {
            auto t = q.front();
            q.pop();
            ret.push_back(t);

            for (auto a : edges[t])
                if (--in[a] == 0)
                    q.push(a);
        }

        return ret.size() == numCourses;
    }

    int subarraySum(vector<int> &nums, int k)
    {
        unordered_map<int, int> hash;
        int sum = 0, ret = 0;

        for (auto n : nums)
        {
            sum += n;
            if (hash.count(sum - k))
                ret += hash[sum - k];
            else
                hash[sum]++;
        }

        return ret;
    }

    int search(vector<int> &nums, int target)
    {
        int left = 0, right = nums.size() - 1;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] < target)
                left = mid + 1;
            else if (nums[mid] > target)
                right = mid - 1;
            else
                return mid;
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
            else
                hash[sum]++;
        }

        return ret;
    }
};