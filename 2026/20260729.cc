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
    int subarraysDivByK(vector<int> &nums, int k)
    {
        unordered_map<int, int> hash;
        hash[0] = 1;

        int sum = 0, ret = 0;
        for (auto n : nums)
        {
            sum += n;
            int r = (sum % k + k) % k;
            if (hash.count(r))
                ret += hash[r];
            hash[r]++;
        }

        return ret;
    }

    // 2
    ListNode *reverseList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *newhead = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;

        return newhead;
    }

    // 3
    int jump(vector<int> &nums)
    {
        int n = nums.size(), cur = 0, far = 0, ret = 0;

        for (int i = 0; i < n - 1; i++)
        {
            far = max(far, i + nums[i]);

            if (i == cur)
            {
                cur = far;
                ret++;
            }
        }

        return ret;
    }

    // 4
    vector<vector<int>> merge(vector<vector<int>> &intervals)
    {
        vector<vector<int>> ret;
        sort(intervals.begin(), intervals.end());

        int n = intervals.size(), left = intervals[0][0],
            right = intervals[0][1];

        for (int i = 1; i < n; i++)
        {
            int a = intervals[i][0], b = intervals[i][1];
            if (a <= right)
                right = max(right, b);
            else
            {
                ret.push_back({left, right});
                left = a, right = b;
            }
        }

        ret.push_back({left, right});

        return ret;
    }

    // 5
    int maxTurbulenceSize(vector<int> &arr)
    {
        int n = arr.size(), ret = 1;
        vector<int> f(n, 1), g(n, 1);

        for (int i = 1; i < n; i++)
        {
            if (arr[i - 1] > arr[i])
                f[i] = g[i - 1] + 1;
            else if (arr[i - 1] < arr[i])
                g[i] = f[i - 1] + 1;
            ret = max(ret, max(f[i], g[i]));
        }

        return ret;
    }

    // 6
    int minimumDeleteSum(string s1, string s2)
    {
        int m = s1.size(), n = s2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);

                if (s1[i - 1] == s2[j - 1])
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + s1[i - 1]);
            }

        int sum = 0;
        for (char ch : s1)
            sum += ch;
        for (char ch : s2)
            sum += ch;

        return sum - 2 * dp[m][n];
    }

    // 7
    int lastStoneWeightII(vector<int> &stones)
    {
        int n = stones.size(), sum = 0;
        for (auto s : stones)
            sum += s;

        int m = sum / 2;
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                dp[i][j] = dp[i][j - 1];
                if (i >= stones[j - 1])
                    dp[i][j] = max(dp[i][j], dp[i - stones[j - 1]][j - 1] + stones[j - 1]);
            }

        return sum - 2 * dp[m][n];
    }

    // 8
    int combinationSum4(vector<int> &nums, int target)
    {
        vector<double> dp(target + 1);
        dp[0] = 1;

        for (int i = 1; i <= target; i++)
            for (auto n : nums)
            {
                if (i >= n)
                    dp[i] += dp[i - n];
            }

        return dp[target];
    }

    // 9
    int myAtoi(string str)
    {
        int n = str.size(), sign = 1, cur = 0, ret = 0;

        while (str[cur] == ' ')
            cur++;

        if (str[cur] == '+' || str[cur] == '-')
        {
            if (str[cur] == '-')
                sign = -1;
            cur++;
        }

        for (int i = cur; i < n; i++)
        {
            char ch = str[i];
            if (!isdigit(ch))
                break;

            if (ret > (INT_MAX - (ch - '0')) / 10)
                return sign == 1 ? INT_MAX : INT_MIN;

            ret = ret * 10 + (ch - '0');
        }

        return ret * sign;
    }

    // 10
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
};