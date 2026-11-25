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
    bool isHappy(int n)
    {
        int slow = n, fast = bitSquareSum(n);

        while (slow != fast)
        {
            slow = bitSquareSum(slow);
            fast = bitSquareSum(bitSquareSum(fast));
        }

        return slow == 1;
    }

    int bitSquareSum(int n)
    {
        int ret = 0;
        while (n)
        {
            int i = n % 10;
            ret += i * i;
            n /= 10;
        }

        return ret;
    }

    // 2 ThreadPool

    // 3
    int minCost(vector<vector<int>> &costs)
    {
        int n = costs.size();
        vector<vector<int>> dp(n + 1, vector<int>(3));

        for (int i = 1; i <= n; i++)
        {
            dp[i][0] = min(dp[i - 1][1], dp[i - 1][2]) + costs[i - 1][0];
            dp[i][1] = min(dp[i - 1][0], dp[i - 1][2]) + costs[i - 1][1];
            dp[i][2] = min(dp[i - 1][1], dp[i - 1][0]) + costs[i - 1][2];
        }

        return min(dp[n][0], min(dp[n][1], dp[n][2]));
    }

    // 4
    int numberOfArithmeticSlices(vector<int> &nums)
    {
        int n = nums.size(), prev = 0, sum = 0;

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

    // 5
    int combinationSum4(vector<int> &nums, int target)
    {
        int n = nums.size();
        vector<double> dp(target + 1);

        dp[0] = 1;

        for (int i = 1; i <= target; i++)
            for (auto x : nums)
            {
                if (i >= x)
                    dp[i] += dp[i - x];
            }

        return dp[target];
    }

    // 6
    int firstUniqChar(string s)
    {
        int n = s.size();
        int hash[128] = {0};

        for (char ch : s)
            hash[ch]++;

        for (int i = 0; i < n; i++)
            if (hash[s[i]] == 1)
                return i;

        return -1;
    }

    // 7
    int MoreThanHalfNum_Solution(vector<int> &numbers)
    {
        int n = numbers.size(), ret = numbers[0], count = 1;

        for (int i = 1; i < n; i++)
        {
            if (numbers[i] == ret)
                count++;
            else if (--count == 0)
            {
                ret = numbers[i];
                count = 1;
            }
        }

        return ret;
    }
};