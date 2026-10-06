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
    string reorganizeString(string s)
    {
        int n = s.size(), maxCount = 0;
        unordered_map<char, int> hash;
        char maxChar = '/0';

        for (char ch : s)
            if (++hash[ch] > maxCount)
            {
                maxCount = hash[ch];
                maxChar = ch;
            }

        string ret;
        ret.append(n, '.');
        int index = 0;
        for (int i = 0; i < maxCount; i++)
        {
            if (index > n - 1)
                break;

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

        for (char ch : ret)
            if (ch == '.')
                return "";

        return ret;
    }

    // 2
    int maxProfit(int k, vector<int> &prices)
    {
        const int INF = 0x3f3f3f;
        int n = prices.size();
        k = min(k, n / 2);
        vector<vector<int>> f(n, vector<int>(k + 1, -INF));
        auto g = f;
        f[0][0] = -prices[0];
        g[0][0] = 0;

        int ret = 0;

        for (int i = 1; i < n; i++)
            for (int j = 0; j <= k; j++)
            {
                f[i][j] = max(f[i - 1][j], g[i - 1][j] - prices[i]);
                g[i][j] = g[i - 1][j];
                if (j >= 1)
                    g[i][j] = max(g[i][j], f[i - 1][j - 1] + prices[i]);
                ret = max(ret, g[i][j]);
            }

        return ret;
    }

    // 3
    int myAtoi(string str)
    {
        int n = str.size(), sign = 1, cur = 0;

        while (str[cur] == ' ')
            cur++;

        if (str[cur] == '-' || str[cur] == '+')
        {
            if (str[cur] == '-')
                sign = -1;
            cur++;
        }

        int ret = 0;
        for (int i = cur; i < n; i++)
        {
            if (!isdigit(str[i]))
                break;

            // ret*10+(str[i]-'0)>INT_MAX
            if (ret > (INT_MAX - (str[i] - '0')) / 10)
                return sign == 1 ? INT_MAX : INT_MIN;

            ret = ret * 10 + (str[i] - '0');
        }

        return ret * sign;
    }

    // 4
    vector<int> ret;
    vector<int> inorderTraversal(TreeNode *root)
    {
        Inorder(root);
        return ret;
    }

    void Inorder(TreeNode *root)
    {
        if (root == nullptr)
            return;

        Inorder(root->left);
        ret.push_back(root->val);
        Inorder(root->right);
    }

    // 5
    string addStrings(string num1, string num2)
    {
        int m = num1.size(), n = num2.size(), t = 0;
        int cur1 = m - 1, cur2 = n - 1;

        string ret;
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

        return ret[0] == '0' ? "0" : ret;
    }

    // 6
    vector<int> intersection(vector<int> &nums1, vector<int> &nums2)
    {
        set<int> hash;
        set<int> tmp;
        vector<int> ret;

        for (auto n : nums1)
            hash.insert(n);
        for (auto n : nums2)
            if (hash.count(n))
                tmp.insert(n);
        for (auto n : tmp)
            ret.push_back(n);

        return ret;
    }
};