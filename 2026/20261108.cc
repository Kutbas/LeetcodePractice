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
    int deleteAndEarn(vector<int> &nums)
    {
        const int N = 10001;
        int arr[N] = {0};

        for (auto n : nums)
            arr[n] += n;

        vector<int> f(N);
        auto g = f;

        for (int i = 1; i < N; i++)
        {
            f[i] = g[i - 1] + arr[i];
            g[i] = max(g[i - 1], f[i - 1]);
        }

        return max(f[N - 1], g[N - 1]);
    }

    // 2
    int findSubstringInWraproundString(string s)
    {
        int n = s.size();
        vector<int> dp(n, 1);
        for (int i = 1; i < n; i++)
            if ((s[i - 1] == 'z' && s[i] == 'a') || s[i - 1] + 1 == s[i])
                dp[i] += dp[i - 1];

        int hash[26] = {0};
        for (int i = 0; i < n; i++)
        {
            int index = s[i] - 'a';
            hash[index] = max(hash[index], dp[i]);
        }

        int ret = 0;
        for (auto i : hash)
            ret += i;

        return ret;
    }

    // 3
    vector<int> intersect(vector<int> &nums1, vector<int> &nums2)
    {
        unordered_map<int, int> hash;
        vector<int> ret;

        for (auto n : nums1)
            hash[n]++;
        for (auto n : nums2)
            if (hash[n]-- > 0)
                ret.push_back(n);

        return ret;
    }
};