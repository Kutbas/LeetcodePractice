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
    // 1 ThreadPool

    // 2
    int numberOfArithmeticSlices(vector<int> &nums)
    {
        int n = nums.size(), sum = 0, prev = 0;

        for (int i = 2; i < n; i++)
        {
            if (nums[i] - nums[i - 1] == nums[i - 1] - nums[i - 2])
            {
                prev += 1;
                sum += prev;
            }
            else
                prev = 0;
        }

        return sum;
    }

    // 3
    int findLength(vector<int> &nums1, vector<int> &nums2)
    {
        int m = nums1.size(), n = nums2.size();
        int ret = 0;
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                if (nums1[i - 1] == nums2[j - 1])
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
                ret = max(ret, dp[i][j]);
            }

        return ret;
    }

    // 4
    int lastStoneWeightII(vector<int> &stones)
    {
        int n = stones.size(), sum = 0;
        for (auto s : stones)
            sum += s;

        int m = sum / 2;
        vector<vector<int>> dp(n + 1, vector<int>(m + 1));
        for (int i = 1; i <= n; i++)
            for (int j = 0; j <= m; j++)
            {
                dp[i][j] = dp[i - 1][j];
                if (j >= stones[i - 1])
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - stones[i - 1]] + stones[i - 1]);
            }

        return sum - 2 * dp[n][m];
    }

    // 5
    vector<string> uncommonFromSentences(string s1, string s2)
    {
        unordered_map<string, int> hash;

        auto countWord = [&](const string s)
        {
            string word;
            istringstream iss(s);

            while (iss >> word)
                hash[word]++;
        };

        countWord(s1);
        countWord(s2);

        vector<string> ret;
        for (auto [a, b] : hash)
            if (b == 1)
                ret.push_back(a);

        return ret;
    }
};
