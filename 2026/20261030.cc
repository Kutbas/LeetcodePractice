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
    int monotoneIncreasingDigits(int n)
    {
        string s = to_string(n);

        int m = s.size(), i = 0;
        while (i + 1 < m && s[i + 1] >= s[i])
            i++;

        if (i + 1 == m)
            return n;

        while (i - 1 >= 0 && s[i] == s[i - 1])
            i--;

        s[i]--;
        for (int j = i + 1; j < m; j++)
            s[j] = '9';

        return stoi(s);
    }

    // 2
    int brokenCalc(int startValue, int target)
    {
        int ret = 0;

        while (target > startValue)
        {
            if (target % 2 == 0)
                target /= 2;
            else
                target++;
            ret++;
        }

        return ret + startValue - target;
    }

    // 3
    int maxProfit(vector<int> &prices, int fee)
    {
        int n = prices.size();
        vector<int> f(n);
        auto g = f;
        f[0] = -prices[0];

        for (int i = 1; i < n; i++)
        {
            f[i] = max(f[i - 1], g[i - 1] - prices[i]);
            g[i] = max(g[i - 1], f[i - 1] + prices[i] - fee);
        }

        return g[n - 1];
    }
};