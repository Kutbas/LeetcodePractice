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
    int maxEnvelopes(vector<vector<int>> &e)
    {
        int n = e.size();
        sort(e.begin(), e.end(), [&](const vector<int> &v1, const vector<int> &v2)
             { return v1[0] != v2[0] ? v1[0] < v2[0] : v1[1] > v2[1]; });

        vector<int> ret;
        ret.push_back(e[0][1]);
        for (int i = 1; i < n; i++)
        {
            if (e[i][1] > ret.back())
                ret.push_back(e[i][1]);
            else
            {
                int left = 0, right = ret.size() - 1;
                while (left < right)
                {
                    int mid = left + (right - left) / 2;
                    if (e[i][1] > ret[mid])
                        left = mid + 1;
                    else
                        right = mid;
                }
                ret[left] = e[i][1];
            }
        }

        return ret.size();
    }

    // 2
    string decodeString(string s)
    {
        stack<int> nums;
        int k = 0;
        stack<string> st;
        st.push("");
        string tmp;

        for (char ch : s)
        {
            if (isdigit(ch))
                k = k * 10 + (ch - '0');
            else if (ch == '[')
            {
                st.push(tmp);
                tmp = "";
                nums.push(k);
                k = 0;
            }
            else if (ch == ']')
            {
                int count = nums.top();
                nums.pop();
                string top = st.top();
                st.pop();
                while (count--)
                    top += tmp;
            }
            else
                tmp += ch;
        }
        return tmp;
    }

    // 3
    int jump(vector<int> &nums)
    {
        int n = nums.size(), cur = 0, far = 0, ret = 0;

        for (int i = 0; i < n - 1; i++)
        {
            far = max(far, i + nums[i]);

            if (cur == i)
            {
                cur = far;
                ret++;
            }

            if (cur >= n - 1)
                break;
        }

        return ret;
    }

    // 4
    int minCostClimbingStairs(vector<int> &cost)
    {
        int n = cost.size();

        vector<int> dp(n + 1);
        for (int i = 2; i <= n; i++)
            dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);

        return dp[n];
    }

    // 5
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost)
    {
        int n = gas.size();

        for (int i = 0; i < n; i++)
        {
            int rest = 0, step = 0;
            for (; step < n; step++)
            {
                int index = (i + step) % n;
                rest += gas[index] - cost[index];

                if (rest < 0)
                    break;
            }

            if (rest >= 0)
                return i;
            i = i + step;
        }
        return -1;
    }

    // 6
    bool isValid(string s)
    {
        stack<char> st;
        st.push(' ');
        for (char ch : s)
        {
            if (ch == '(' || ch == '[' || ch == '{')
                st.push(ch);
            else if (((ch == ')' && st.top() == '(') ||
                      (ch == ']' && st.top() == '[') ||
                      (ch == '}' && st.top() == '{')))
                st.pop();
            else
                st.push(ch);
        }

        return st.top() == ' ';
    }

    // 7
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
};