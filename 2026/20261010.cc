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
    int findLongestChain(vector<vector<int>> &pairs)
    {
        sort(pairs.begin(), pairs.end());

        int n = pairs.size(), ret = 1;
        vector<int> dp(n, 1);

        for (int i = 1; i < n; i++)
            for (int j = 0; j < i; j++)
            {
                int a = pairs[j][1], b = pairs[i][0];
                if (a < b)
                    dp[i] = max(dp[i], dp[j] + 1);
                ret = max(ret, dp[i]);
            }

        return ret;
    }

    // 2
    string reverseStr(string s, int k)
    {
        int n = s.size();

        for (int i = 0; i < n; i += 2 * k)
        {
            int right = min(i + k, n);
            reverse(s.begin() + i, s.begin() + right);
        }

        return s;
    }

    // 3
    vector<int> intersect(vector<int> &nums1, vector<int> &nums2)
    {
        unordered_map<int, int> cnt; // 统计 nums1 各元素出现次数
        for (int n : nums1)
            cnt[n]++;

        vector<int> ret;
        for (int n : nums2)
        {
            // 若 n 在 nums1 中还有剩余出现次数，则加入结果并消耗一次
            if (cnt[n] > 0)
            {
                ret.push_back(n);
                cnt[n]--;
            }
        }
        return ret;
    }
};