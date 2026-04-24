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
    string addStrings(string num1, string num2)
    {
        int m = num1.size(), n = num2.size();
        string ret;

        int t = 0, cur1 = m - 1, cur2 = n - 1;
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
        return ret;
    }

    // 2
    bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
    {
        vector<vector<int>> edges(numCourses);
        vector<int> in(numCourses);

        // [a,b]:b->a
        for (auto &e : prerequisites)
        {
            int a = e[0], b = e[1];
            in[a]++;
            edges[b].push_back(a);
        }

        queue<int> q;
        for (int i = 0; i < numCourses; i++)
            if (in[i] == 0)
                q.push(i);

        while (q.size())
        {
            auto t = q.front();
            q.pop();

            for (auto a : edges[t])
                if (--in[a] == 0)
                    q.push(a);
        }

        for (int i = 0; i < numCourses; i++)
            if (in[i])
                return false;
        return true;
    }

    // 3
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

};