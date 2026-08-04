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
#include <regex>
#include <map>
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
    int findKthLargest(vector<int> &nums, int k)
    {
        priority_queue<int, vector<int>, greater<int>> q;

        for (auto n : nums)
        {
            q.push(n);
            if (q.size() > k)
                q.pop();
        }

        return q.top();
    }

    // 2
    string multiply(string num1, string num2)
    {
        int m = num1.size(), n = num2.size();
        vector<int> tmp(m + n - 1);

        for (int i = m - 1; i >= 0; i--)
            for (int j = n - 1; j >= 0; j--)
            {
                tmp[i + j] += (num1[i] - '0') * (num2[j] - '0');
            }

        string ret;
        int t = 0, cur = m + n - 2;
        while (t || cur >= 0)
        {
            if (cur >= 0)
                t += tmp[cur--];

            ret += to_string(t % 10);
            t /= 10;
        }

        reverse(ret.begin(), ret.end());
        return ret[0] == '0' ? "0" : ret;
    }

    // 3
    int sum = 0;
    int sumNumbers(TreeNode *root)
    {
        dfs(root, 0);
        return sum;
    }

    void dfs(TreeNode *root, int tmp)
    {
        tmp = tmp * 10 + root->val;

        if (root->left == nullptr && root->right == nullptr)
        {
            sum += tmp;
            return;
        }

        if (root->left)
            dfs(root->left, tmp);

        if (root->right)
            dfs(root->right, tmp);
    }

    // 4
    bool increasingTriplet(vector<int> &nums)
    {
        int n = nums.size(), a = INT_MAX, b = nums[0];
        for (int i = 1; i < n; i++)
        {
            if (nums[i] > a)
                return true;
            else if (nums[i] > b)
                a = nums[i];
            else
                b = nums[i];
        }

        return false;
    }

    // 5
    int maxProfit(vector<int> &prices)
    {
        int n = prices.size(), prev = INT_MAX, ret = 0;

        for (int i = 1; i < n; i++)
        {
            prev = min(prev, prices[i - 1]);
            ret = max(ret, prices[i] - prev);
        }

        return ret;
    }

    // 6
};