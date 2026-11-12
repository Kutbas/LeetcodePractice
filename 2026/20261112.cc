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

    // 2
    string reorganizeString(string s)
    {
        int n = s.size(), maxCount = 0;
        char maxChar = '/0';
        unordered_map<int, int> hash;

        for (char ch : s)
        {
            if (++hash[ch] > maxCount)
            {
                maxCount = hash[ch];
                maxChar = ch;
            }
        }

        string ret;
        ret.append(n, '.');
        int index = 0;

        for (int i = 0; i < maxCount; i++)
        {
            if (index > n - 1)
                return "";

            ret[index] = maxChar;
            index += 2;
        }

        hash.erase(maxChar);

        for (auto [a, b] : hash)
            for (int i = 0; i < b; i++)
            {
                if (index > n - 1)
                    index = 1;

                ret[index] = a;
                index += 2;
            }

        for (int i = 0; i < n; i++)
            if (ret[i] == '.')
                return "";

        return ret;
    }

    // 3
    class MyStack
    {
    private:
        queue<int> q;

    public:
        MyStack() {}

        void push(int x)
        {
            int n = q.size();
            q.push(x);

            for (int i = 0; i < n; i++)
            {
                q.push(q.front());
                q.pop();
            }
        }

        int pop()
        {
            int r = q.front();
            q.pop();
            return r;
        }

        int top()
        {
            int r = q.front();
            return r;
        }

        bool empty() { return q.empty(); }
    };

    // 4
    class MinStack
    {
    private:
        long minElem;
        stack<long> st;

    public:
        MinStack() {}

        void push(int value)
        {
            if (st.empty())
            {
                st.push(0);
                minElem = value;
            }
            else
            {
                long diff = value - minElem;
                if (diff < 0)
                    minElem = value;
                st.push(diff);
            }
        }

        void pop()
        {
            long diff = st.top();
            st.pop();

            if (diff < 0)
                minElem = minElem - diff;
        }

        int top()
        {
            long diff = st.top();

            if (diff > 0)
                return minElem + diff;
            return minElem;
        }

        int getMin() { return minElem; }
    };
};