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
    int peakIndexInMountainArray(vector<int> &arr)
    {
        int n = arr.size();
        int left = 0, right = n - 1;

        while (left < right)
        {
            int mid = left + (right - left + 1) / 2;
            if (arr[mid] > arr[mid - 1])
                left = mid;
            else
                right = mid - 1;
        }

        return left;
    }

    // 2
    int calculate(string s)
    {
        int n = s.size();
        char op = '+';
        vector<int> nums;

        for (int i = 0; i < n;)
        {
            if (s[i] == ' ')
            {
                i++;
                continue;
            }
            else if (isdigit(s[i]))
            {
                int tmp = 0;

                while (i < n && isdigit(s[i]))
                    tmp = tmp * 10 + (s[i++] - '0');

                if (op == '+')
                    nums.push_back(tmp);
                else if (op == '-')
                    nums.push_back(-tmp);
                else if (op == '*')
                    nums.back() *= tmp;
                else
                    nums.back() /= tmp;
            }
            else
                op = s[i++];
        }

        int ret = 0;
        for (auto num : nums)
            ret += num;

        return ret;
    }

    // 3
    int maxProfit(vector<int> &prices)
    {
        int n = prices.size();
        int prev = INT_MAX, ret = 0;

        for (int i = 1; i < n; i++)
        {
            prev = min(prev, prices[i - 1]);
            ret = max(ret, prices[i] - prev);
        }

        return ret;
    }

    // 4
    int largestSumAfterKNegations(vector<int> &nums, int k)
    {
        int n = nums.size(), count = 0, minElem = INT_MAX;
        for (auto num : nums)
        {
            minElem = min(minElem, abs(num));
            if (num < 0)
                count++;
        }

        // count>k:负数不能被全部反转
        int sum = 0;
        if (count > k)
        {
            sort(nums.begin(), nums.end());
            for (int i = 0; i < k; i++)
                sum += -nums[i];
            for (int i = k; i < n; i++)
                sum += nums[i];
        }
        else
        {
            for (auto num : nums)
                sum += abs(num);

            if ((k - count) % 2 == 1)
                sum -= 2 * minElem;
        }

        return sum;
    }

    // 5
    int numberOfArithmeticSlices(vector<int> &nums)
    {
        int n = nums.size(), prev = 0, sum = 0;

        if (n < 3)
            return 0;

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

    // 6
    int findSubstringInWraproundString(string s)
    {
        int n = s.size();
        vector<int> dp(n + 1, 1);

        for (int i = 1; i <= n; i++)
            if ((s[i - 1] == 'z' && s[i] == 'a') || s[i - 1] + 1 == s[i])
                dp[i] += dp[i - 1];

        int hash[26] = {0};
        for (int i = 0; i < n; i++)
        {
            int index = s[i] - 'a';
            hash[index] = max(hash[index], dp[i]);
        }

        int ret = 0;
        for (auto n : hash)
            ret += n;

        return ret;
    }

    // 7
    int maxUncrossedLines(vector<int> &nums1, vector<int> &nums2)
    {
        int m = nums1.size(), n = nums2.size(), ret = 0;
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                if (nums1[i - 1] == nums2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                ret = max(ret, dp[i][j]);
            }

        return ret;
    }

    // 8
    int removeDuplicates(vector<int> &nums)
    {
        int n = nums.size(), slow = 1, fast = 1;

        while (fast < n)
        {
            if (nums[fast - 1] != nums[fast])
            {
                nums[slow++] = nums[fast];
            }
            fast++;
        }

        return slow;
    }
};