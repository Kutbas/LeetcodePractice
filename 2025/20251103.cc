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
    string longestCommonPrefix(vector<string> &strs)
    {
        for (int i = 0; i < strs[0].size(); i++)
            for (int j = 1; j < strs.size(); j++)
                if (i == strs[j].size() || strs[0][i] != strs[j][i])
                    return strs[0].substr(0, i);
        return strs[0];
    }

    // 2
    vector<int> missingTwo(vector<int> &nums)
    {
        int xorsum = 0;
        for (auto n : nums)
            xorsum ^= n;
        for (int i = 1; i <= nums.size() + 2; i++)
            xorsum ^= i;

        int lsb = xorsum == INT_MIN ? xorsum : xorsum & (-xorsum);
        int x = 0, y = 0;
        for (auto n : nums)
        {
            if (n & lsb)
                x ^= n;
            else
                y ^= n;
        }
        for (int i = 1; i <= nums.size() + 2; i++)
        {
            if (i & lsb)
                x ^= i;
            else
                y ^= i;
        }

        return {x, y};
    }

    // 3
    int minOperations(vector<int> &nums, int x)
    {
        int sum = 0;
        for (auto n : nums)
            sum += n;

        int aim = sum - x;
        if (aim < 0)
            return -1;

        int ret = INT_MIN;
        for (int left = 0, right = 0, tmp = 0; right < nums.size(); right++)
        {
            tmp += nums[right];
            while (tmp > aim)
                tmp -= nums[left++];
            if (tmp == aim)
                ret = max(ret, right - left + 1);
        }

        return ret == INT_MIN ? -1 : nums.size() - ret;
    }

    // 4
    string addBinary(string a, string b)
    {
        int m = a.size(), n = b.size();
        string ret;

        int cur1 = a.size() - 1, cur2 = b.size() - 1, carry = 0, sum = 0;
        while (cur1 || cur2 || carry)
        {
            if (cur1)
                carry += a[cur1--] - '0';
            if (cur2)
                carry += b[cur2--] - '0';

            ret += to_string(carry % 2);
            carry /= 2;
        }

        reverse(ret.begin(), ret.end());
        return ret;
    }

    // 5
    string hash[10] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    vector<string> ret;
    string path;
    vector<string> letterCombinations(string digits)
    {
        dfs(digits, 0);
        return ret;
    }

    void dfs(string &digits, int pos)
    {
        if (pos == digits.size())
        {
            ret.push_back(path);
            return;
        }

        for (char ch : hash[digits[pos] - '0'])
        {
            path.push_back(ch);
            dfs(digits, pos + 1);
            path.pop_back();
        }
    }
};

// 6
class KthLargest
{
public:
    KthLargest(int k, vector<int> &nums)
        : _k(k)
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