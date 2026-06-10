#include <bits/stdc++.h>
#include <mutex>
using namespace std;

class Solution
{
public:
    // 1
    unordered_map<char, int> in;
    unordered_map<char, unordered_set<char>> hash;
    bool check = false;
    string alienOrder(vector<string> &words)
    {
        for (auto &word : words)
            for (auto &ch : word)
                in[ch] = 0;

        int n = words.size();
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
            {
                add(words[i], words[j]);
                if (check)
                    return "";
            }

        queue<char> q;
        for (auto [a, b] : in)
            if (b == 0)
                q.push(a);

        string ret;
        while (q.size())
        {
            auto t = q.front();
            q.pop();
            ret += t;

            for (auto ch : hash[t])
                if (--in[ch] == 0)
                    q.push(ch);
        }

        for (auto [a, b] : in)
            if (b)
                return "";

        return ret;
    }

    void add(const string &s1, const string &s2)
    {
        int n = min(s1.size(), s2.size()), i = 0;

        for (; i < n; i++)
        {
            if (s1[i] != s2[i])
            {
                char a = s1[i], b = s2[i];
                if (!hash.count(a) || !hash[a].count(b))
                {
                    in[b]++;
                    hash[a].insert(b);
                }
                break;
            }
        }

        if (i < s1.size() && i == s2.size())
            check = true;
    }

    // 2
    double myPow(double x, int n)
    {
        long N = n;
        if (N < 0)
        {
            N = -N;
            x = 1 / x;
        }

        return dfs(x, N);
    }

    double dfs(double x, long n)
    {
        if (n == 0)
            return 1;

        double tmp = dfs(x, n / 2);

        return n % 2 == 0 ? tmp * tmp : tmp * tmp * x;
    }

    // 3
    int aim, ret = 0;
    int findTargetSumWays(vector<int> &nums, int target)
    {
        aim = target;
        dfs(nums, 0, 0);
        return ret;
    }

    void dfs(vector<int> &nums, int pos, int sum)
    {

        if (pos == nums.size())
        {
            if (sum == aim)
                ret++;
            return;
        }

        dfs(nums, pos + 1, sum + nums[pos]);
        dfs(nums, pos + 1, sum - nums[pos]);
    }

    // 4
    int jump(vector<int> &nums)
    {
        int n = nums.size(), ret = 0, cur = 0, far = 0;

        for (int i = 0; i < n; i++)
        {
            far = max(far, i + nums[i]);

            if (cur >= n - 1)
                break;

            if (cur == i)
            {
                cur = far;
                ret++;
            }
        }

        return ret;
    }

    // 5
    int maxSumDivThree(vector<int> &nums)
    {
        const int INF = 0x3f3f3f;
        int x1 = INF, x2 = INF;
        int y1 = INF, y2 = INF;

        int sum = 0;
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
        return sum % 3 == 1 ? max(sum - x1, sum - y1 - y2) : max(sum - y1, sum - x1 - x2);
    }

    // 6
    bool wordBreak(string s, vector<string> &wordDict)
    {
        unordered_set<string> hash(wordDict.begin(), wordDict.end());
        int n = s.size();
        s = " " + s;

        vector<bool> dp(n + 1);
        dp[0] = true;

        for (int i = 1; i <= n; i++)
            for (int j = i; j >= 1; j--)
            {
                if (dp[j - 1] && hash.count(s.substr(j, i - j + 1)))
                {
                    dp[i] = true;
                    break;
                }
            }

        return dp[n];
    }

    // 7
    int findLongestChain(vector<vector<int>> &pairs)
    {
        sort(pairs.begin(), pairs.end());

        int n = pairs.size(), ret = 1;
        vector<int> dp(n, 1);

        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < i; j++)
            {
                int a = pairs[j][1], b = pairs[i][0];
                if (a < b)
                {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            ret = max(ret, dp[i]);
        }

        return ret;
    }

    // 8
    bool isMatch(string s, string p)
    {
        int m = s.size(), n = p.size();
        s = " " + s, p = " " + p;

        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1));
        dp[0][0] = true;

        for (int i = 2; i <= n; i += 2)
            if (p[i] == '*')
                dp[0][i] = true;
            else
                break;

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                if (p[j] == '*')
                {
                    bool case1 = dp[i][j - 2];
                    bool case2 = (p[j - 1] == '.' || p[j - 1] == s[i]) && dp[i - 1][j];
                    dp[i][j] = case1 || case2;
                }
                else
                    dp[i][j] = (p[j] == '.' || p[j] == s[i]) && dp[i - 1][j - 1];
            }

        return dp[m][n];
    }

    // 9
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
};