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
    int maxEnvelopes(vector<vector<int>> &envelopes)
    {
        int n = envelopes.size();
        sort(envelopes.begin(), envelopes.end(),
             [](const vector<int> &e1, const vector<int> &e2)
             {
                 return e1[0] != e2[0] ? e1[0] < e2[0] : e1[1] > e2[1];
             });

        vector<int> ret;
        ret.push_back(envelopes[0][1]);
        for (int i = 1; i < n; i++)
        {
            if (envelopes[i][1] > ret.back())
                ret.push_back(envelopes[i][1]);
            else
            {
                int left = 0, right = ret.size() - 1;
                while (left < right)
                {
                    int mid = left + (right - left) / 2;
                    if (envelopes[i][1] > ret[mid])
                        left = mid + 1;
                    else
                        right = mid;
                }
                ret[left] = envelopes[i][1];
            }
        }

        return ret.size();
    }

    // 2
    class MyStack
    {
    private:
        queue<int> q;

    public:
        MyStack()
        {
        }

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
            return q.front();
        }

        bool empty()
        {
            return q.empty();
        }
    };

    // 3
    class MyQueue
    {
    private:
        stack<int> in, out;

        void in2out()
        {
            while (in.size())
            {
                out.push(in.top());
                in.pop();
            }
        }

    public:
        MyQueue()
        {
        }

        void push(int x)
        {
            in.push(x);
        }

        int pop()
        {
            if (out.empty())
                in2out();

            int r = out.top();
            out.pop();
            return r;
        }

        int peek()
        {
            if (out.empty())
                in2out();

            int r = out.top();
            return r;
        }

        bool empty()
        {
            return in.empty() && out.empty();
        }
    };
};