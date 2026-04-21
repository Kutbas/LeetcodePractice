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
    string countAndSay(int n)
    {
        string ret = "1";

        for (int i = 1; i < n; i++)
        {
            string tmp;
            int len = ret.size();
            for (int left = 0, right = 0; right < len; right++)
            {
                while (right + 1 < len && ret[right + 1] == ret[right])
                    right++;
                tmp += to_string(right - left + 1) + ret[left];
                left = right + 1;
            }
            ret = tmp;
        }

        return ret;
    }

    // 2
    int getSum(int a, int b)
    {
        while (b)
        {
            int carry = (a & b) << 1;
            a = a ^ b;
            b = carry;
        }
        return a;
    }

    // 3
    int maxSumDivThree(vector<int> &nums)
    {
        const int INF = 0x3f3f3f;
        int x1 = INF, x2 = INF, y1 = INF, y2 = INF;
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

    // 4
    int maxSubArray(vector<int> &nums)
    {
        int n = nums.size(), ret = INT_MIN;
        vector<int> dp(n + 1);

        for (int i = 1; i <= n; i++)
        {
            dp[i] = max(dp[i - 1] + nums[i - 1], nums[i - 1]);
            ret = max(ret, dp[i]);
        }

        return ret;
    }

    // 5
    int findKthLargest(vector<int> &nums, int k)
    {
        srand(time(nullptr));
        return quickSort(nums, 0, nums.size() - 1, k);
    }

    int getRandom(vector<int> &nums, int left, int right)
    {
        int r = rand();
        return nums[r % (right - left + 1) + left];
    }

    int quickSort(vector<int> &nums, int l, int r, int k)
    {
        if (l >= r)
            return nums[l];

        int key = getRandom(nums, l, r);
        int i = l, left = l - 1, right = r + 1;
        while (i < right)
        {
            if (nums[i] < key)
                swap(nums[i++], nums[++left]);
            else if (nums[i] == key)
                i++;
            else
                swap(nums[i], nums[--right]);
        }

        int rRange = r - right + 1, mRange = (right - 1) - (left + 1) + 1;
        if (rRange >= k)
            return quickSort(nums, right, r, k);
        else if (rRange + mRange >= k)
            return key;
        else
            return quickSort(nums, l, left, k - rRange - mRange);
    }

    // 6
    vector<int> findAnagrams(string s, string p)
    {
        int m = p.size(), n = s.size();
        int hash1[128] = {0}, hash2[128] = {0};
        for (char ch : p)
            hash1[ch]++;

        vector<int> ret;
        for (int left = 0, right = 0, count = 0; right < n; right++)
        {
            char in = s[right];
            if (++hash2[in] <= hash1[in])
                count++;
            while (right - left + 1 > m)
            {

                char out = s[left++];
                if (hash2[out]-- <= hash1[out])
                    count--;
            }
            if (count == m)
                ret.push_back(left);
        }

        return ret;
    }

    // 7
    int fib(int n)
    {
        if (n == 0 || n == 1)
            return n;

        return fib(n - 1) + fib(n - 2);
    }

    // 8
    int maxProfit(vector<int>& prices) {
        int n=prices.size();
        vector<vector<int>> dp(n,vector<int>(3));
        dp[0][0]=-prices[0];

        for(int i=1;i<n;i++)
        {
            dp[i][0]=max(dp[i-1][0],dp[i-1][1]-prices[i]);
            dp[i][1]=max(dp[i-1][1],dp[i-1][2]);
            dp[i][2]=dp[i-1][0]+prices[i];
        }

        return max(dp[n-1][1],dp[n-1][2]);
    }
};