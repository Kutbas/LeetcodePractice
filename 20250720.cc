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
    vector<vector<int>> generate(int numRows)
    {
        vector<vector<int>> ret;
        ret.resize(numRows);
        for (int i = 0; i < numRows; i++)
        {
            ret[i].resize(i + 1);
            ret[i][0] = ret[i][i] = 1;
            for (int j = 1; j < i; j++)
                ret[i][j] = ret[i - 1][j] + ret[i - 1][j - 1];
        }

        return ret;
    }

    bool backspaceCompare(string s, string t)
    {
        return change(s) == change(t);
    }

    string change(string s)
    {
        string ret;
        for (auto ch : s)
        {
            if (ch == '#')
            {
                if (ret.size())
                    ret.pop_back();
            }
            else
                ret += ch;
        }
        return ret;
    }

    ListNode *reverseKGroup(ListNode *head, int k)
    {
        ListNode *cur = head;
        int n = 0;
        while (cur)
        {
            cur = cur->next;
            n++;
        }

        n /= k;

        ListNode *newhead = new ListNode(0);
        ListNode *prev = newhead;
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
        prev = newhead->next;
        delete newhead;
        return prev;
    }

    int findMaxLength(vector<int> &nums)
    {
        unordered_map<int, int> hash;
        hash[0] = -1;
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

    int lastStoneWeight(vector<int> &stones)
    {
        priority_queue<int> q;
        for (auto n : stones)
            q.push(n);

        while (q.size() > 1)
        {
            int x = q.top();
            q.pop();
            int y = q.top();
            q.pop();
            q.push(x - y);
        }

        return q.top();
    }

    vector<int> findSubstring(string s, vector<string> &words)
    {
        int m = words.size(), len = words[0].size();
        unordered_map<string, int> hash1;
        for (auto word : words)
            hash1[word]++;

        vector<int> ret;
        for (int i = 0; i < len; i++)
        {
            unordered_map<string, int> hash2;
            for (int left = i, right = i, count = 0; right + len <= s.size(); right += len)
            {
                string in = s.substr(right, len);
                ++hash2[in];
                if (hash1.count(in) && hash2[in] <= hash1[in])
                    count++;
                while (right - left + 1 > len * m)
                {
                    if (count == m)
                        ret.push_back(left);

                    string out = s.substr(left, len);
                    if (hash1.count(out) && hash2[out] <= hash1[out])
                        count--;
                    hash2[out]--;
                    left += len;
                }
            }
        }

        return ret;
    }
};