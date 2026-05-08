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
    vector<int> twoSum(vector<int> &nums, int target)
    {
        int n = nums.size();
        unordered_map<int, int> hash;

        for (int i = 0; i < n; i++)
        {
            int x = target - nums[i];
            if (hash.count(x))
                return {i, hash[x]};
            hash[nums[i]] = i;
        }

        return {-1, -1};
    }

    // 2
    int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid)
    {
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        dp[0][1] = 1;

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                if (obstacleGrid[i - 1][j - 1] == 0)
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }

        return dp[m][n];
    }

    // 3
    string addStrings(string num1, string num2)
    {
        int m = num1.size(), n = num2.size();
        string ret;

        int cur1 = m - 1, cur2 = n - 1, t = 0;
        while (cur1 >= 0 || cur2 >= 0 || t)
        {
            if (cur1 >= 0)
                t += (num1[cur1--] - '0');
            if (cur2 >= 0)
                t += (num2[cur2--] - '0');
            ret += to_string(t % 10);
            t /= 10;
        }

        reverse(ret.begin(), ret.end());
        return ret;
    }

    // 4
    int removeDuplicates(vector<int> &nums)
    {
        int n = nums.size(), slow = 1, fast = 1;

        while (fast < n)
        {
            if (nums[fast - 1] != nums[fast])
                nums[slow++] = nums[fast];
            fast++;
        }

        return slow;
    }

    // 5
    vector<int> intersection(vector<int> &nums1, vector<int> &nums2)
    {
        int hash[1001] = {0};
        vector<int> ret;

        for (auto n : nums1)
            if (hash[n] == 0)
                hash[n]++;

        for (auto n : nums2)
            if (--hash[n] == 0)
                ret.push_back(n);

        return ret;
    }

    // 6
    int longestPalindromeSubseq(string s)
    {
        int n = s.size();
        // dp[i][j]: 在 s 的区间 [i, j] 内，最长回文子序列的长度
        vector<vector<int>> dp(n, vector<int>(n, 0));

        // i 从右往左遍历（因为计算 dp[i][j] 依赖 dp[i+1][...]）
        for (int i = n - 1; i >= 0; i--)
        {
            // 单个字符本身就是长度为 1 的回文
            dp[i][i] = 1;
            // j 从左往右遍历（比 i 大，构成合法区间）
            for (int j = i + 1; j < n; j++)
            {
                if (s[i] == s[j])
                {
                    // 情况一：两端字符相同
                    // 这两个字符作为回文的外壳，中间套上 [i+1, j-1] 的回文
                    //    +2 是因为 s[i] 和 s[j] 各贡献 1 个长度
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                }
                else
                {
                    // 情况二：两端字符不同
                    // 两端的字符不可能同时出现在回文里
                    // 尝试放弃一端，取较大的：
                    //   dp[i+1][j]  → 放弃左端 s[i]
                    //   dp[i][j-1]  → 放弃右端 s[j]
                    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
                }
            }
        }

        // 整个字符串 [0, n-1] 的最长回文子序列
        return dp[0][n - 1];
    }
};