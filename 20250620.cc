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
    int minNumberOfFrogs(string croakOfFrogs)
    {
        string frog = "croak";
        int n = frog.size();
        vector<int> count(n);
        unordered_map<char, int> hash;

        for (int i = 0; i < n; i++)
            hash[frog[i]] = i;

        for (char ch : croakOfFrogs)
        {
            if (ch == 'c')
            {
                if (count[n - 1])
                    count[n - 1]--;
                count[0]++;
            }
            else
            {
                if (count[hash[ch] - 1] == 0)
                    return -1;
                count[hash[ch] - 1]--;
                count[hash[ch]]++;
            }
        }

        for (int i = 0; i < n - 1; i++)
            if (count[i])
                return -1;
        return count[n - 1];
    }

    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
    {
        if (l1 == nullptr)
            return l2;
        if (l2 == nullptr)
            return l1;

        if (l1->val < l2->val)
        {
            l1->next = mergeTwoLists(l1->next, l2);
            return l1->next;
        }
        else
        {
            l2->next = mergeTwoLists(l1, l2->next);
            return l2->next;
        }
    }

    vector<vector<string>> groupAnagrams(vector<string> &strs)
    {
        vector<vector<string>> ret;
        unordered_map<string, vector<string>> hash;

        for (auto s : strs)
        {
            string tmp = s;
            sort(tmp.begin(), tmp.end());
            hash[tmp].push_back(s);
        }

        for (auto &[a, b] : hash)
            ret.push_back(b);

        return ret;
    }

    string decodeString(string s)
    {
        string ret;
        int n = 0;
        stack<int> nums;
        stack<string> st;

        for (char ch : s)
        {
            if (isdigit(ch))
                n = n * 10 + (ch - '0');
            else if (ch == '[')
            {
                st.push(ret);
                ret = "";
                nums.push(n);
                n = 0;
            }
            else if (ch == ']')
            {
                string tmp = st.top();
                st.pop();
                int k = nums.top();
                nums.pop();
                while (k--)
                    tmp += ret;
                ret = tmp;
            }
            else
                ret += ch;
        }

        return ret;
    }

    int left, right, N;

    string path;

    vector<string> ret;

    vector<string> generateParenthesis(int n)
    {

        N = n;

        dfs();

        return ret;
    }

    void dfs()
    {

        if (right == N)
        {

            ret.push_back(path);

            return;
        }

        if (left < N)
        {

            path.push_back('(');

            left++;

            dfs();

            path.pop_back();

            left--;
        }

        if (right < left)
        {

            path.push_back(')');

            right++;

            dfs();

            path.pop_back();

            right--;
        }
    }
};

class MedianFinder
{
public:
    priority_queue<int> left;
    priority_queue<int, vector<int>, greater<int>> right;

    MedianFinder() {}

    void addNum(int num)
    {
        if (left.size() == right.size())
        {
            if (left.empty() || num < left.top())
                left.push(num);
            else
            {
                right.push(num);
                left.push(right.top());
                right.pop();
            }
        }
        else
        {
            if (num >= left.top())
                right.push(num);
            else
            {
                left.push(num);
                right.push(left.top());
                left.pop();
            }
        }
    }

    double findMedian()
    {
        return left.size() == right.size() ? (left.top() + right.top()) / 2.0
                                           : left.top();
    }
};