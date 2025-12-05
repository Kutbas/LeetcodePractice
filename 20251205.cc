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
    int tmp[50010];
    vector<int> sortArray(vector<int> &nums)
    {
        mergeSort(nums, 0, nums.size() - 1);
        return nums;
    }

    void mergeSort(vector<int> &nums, int left, int right)
    {
        if (left >= right)
            return;

        int mid = left + (right - left) / 2;
        mergeSort(nums, left, mid);
        mergeSort(nums, mid + 1, right);

        int i = 0, cur1 = left, cur2 = mid + 1;
        while (cur1 <= mid && cur2 <= right)
            tmp[i++] = nums[cur1] < nums[cur2] ? nums[cur1++] : nums[cur2++];
        while (cur1 <= mid)
            tmp[i++] = nums[cur1++];
        while (cur2 <= right)
            tmp[i++] = nums[cur2++];

        for (int j = left; j <= right; j++)
            nums[j] = tmp[j - left];
    }

    // 2
    bool isInterleave(string s1, string s2, string s3)
    {
        int m = s1.size(), n = s2.size();
        if (m + n != s3.size())
            return false;

        s1 = " " + s1;
        s2 = " " + s2;
        s3 = " " + s3;

        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1));
        dp[0][0] = true;

        for (int i = 1; i <= m; i++)
        {
            if (s1[i] == s3[i])
                dp[i][0] = dp[i - 1][0];
            else
                break;
        }

        for (int i = 1; i <= n; i++)
        {
            if (s2[i] == s3[i])
                dp[0][i] = dp[0][i - 1];
            else
                break;
        }

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                bool from_s1 = (s1[i] == s3[i + j] && dp[i - 1][j]);
                bool from_s2 = (s2[j] == s3[i + j] && dp[i][j - 1]);

                dp[i][j] = from_s1 || from_s2;
            }

        return dp[m][n];
    }

    // 3
    int maxSumDivThree(vector<int> &nums)
    {
        const int INF = 0x3f3f3f;
        int sum = 0;
        int x1 = INF, x2 = INF;
        int y1 = INF, y2 = INF;

        for (auto n : nums)
        {
            sum += n;

            if (n % 3 == 1)
            {
                if (n < x1)
                    x2 = x1, x1 = n;
                else if (n < x2)
                    x2 = n;
            }
            else if (n % 3 == 2)
            {
                if (n < y1)
                    y2 = y1, y1 = n;
                else if (n < y2)
                    y2 = n;
            }
        }

        if (sum % 3 == 0)
            return sum;
        else if (sum % 3 == 1)
            return max(sum - x1, sum - y1 - y2);
        else
            return max(sum - y1, sum - x1 - x2);
    }

    // 4
    string hash[10] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    vector<string> ret;
    vector<string> letterCombinations(string digits)
    {
        dfs(digits, 0, "");
        return ret;
    }

    void dfs(string &s, int pos, string path)
    {
        if (pos == s.size())
        {
            ret.push_back(path);
            return;
        }

        for (char ch : hash[s[pos] - '0'])
        {
            path.push_back(ch);
            dfs(s, pos + 1, path);
            path.pop_back();
        }
    }

    // 5
    int memo[201][201];
    int getMoneyAmount(int n)
    {
        return dfs(1, n);
    }

    int dfs(int m, int n)
    {
        if (m >= n)
            return 0;

        if (memo[m][n])
            return memo[m][n];

        int ret = INT_MAX;
        for (int head = m; head <= n; head++)
        {
            int tmp1 = dfs(m, head - 1);
            int tmp2 = dfs(head + 1, n);

            ret = min(ret, head + max(tmp1, tmp2));
        }

        memo[m][n] = ret;
        return ret;
    }

    // 6
    int findNumberOfLIS(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> longestLen(n, 1);
        vector<int> ways(n, 1);
        int globalLongestLen = 1;
        int globalWays = 1;

        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (nums[j] < nums[i])
                {
                    int newlen = longestLen[j] + 1;
                    if (newlen == longestLen[i])
                        ways[i] += ways[j];
                    else if (newlen > longestLen[i])
                    {
                        longestLen[i] = newlen;
                        ways[i] = ways[j];
                    }
                }
            }

            if (globalLongestLen == longestLen[i])
                globalWays += ways[i];
            else if (globalLongestLen < longestLen[i])
            {
                globalLongestLen = longestLen[i];
                globalWays = ways[i];
            }
        }

        return globalWays;
    }

    // 7
    vector<vector<int>> res;
    vector<int> path;
    bool vis[9];
    vector<vector<int>> permuteUnique(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        dfs(nums);
        return res;
    }

    void dfs(vector<int> &nums)
    {
        if (path.size() == nums.size())
        {
            res.push_back(path);
            return;
        }

        for (int i = 0; i < nums.size(); i++)
        {
            if (vis[i] || (i != 0 && nums[i] == nums[i - 1] && !vis[i - 1]))
                continue;
            else
            {
                vis[i] = true;
                path.push_back(nums[i]);
                dfs(nums);
                path.pop_back();
                vis[i] = false;
            }
        }
    }

    // 8
    int numDecodings(string s)
    {
        int n = s.size();

        vector<int> dp(n);
        dp[0] = s[0] == '0' ? 0 : 1;
        if (n == 1)
            return dp[0];

        if (s[0] != '0' && s[1] != '0')
            dp[1] += 1;

        int twoDigits = (s[0] - '0') * 10 + (s[1] - '0');
        if (twoDigits >= 10 && twoDigits <= 26)
            dp[1] += 1;

        for (int i = 2; i < n; i++)
        {
            if (s[i] != '0')
                dp[i] += dp[i - 1];

            int twoDigits = (s[i - 1] - '0') * 10 + (s[i] - '0');
            if (twoDigits >= 10 && twoDigits <= 26)
                dp[i] += dp[i - 2];
        }

        return dp[n - 1];
    }
};