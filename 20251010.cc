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
    int longestCommonSubsequence(string s1, string s2)
    {
        int m = s1.size(), n = s2.size();

        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                if (s1[i - 1] == s2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);

        return dp[m][n];
    }

    int maxUncrossedLines(vector<int> &nums1, vector<int> &nums2)
    {
        int m = nums1.size(), n = nums2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                if (nums1[i - 1] == nums2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        return dp[m][n];
    }

    // 1
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost)
    {
        int n = gas.size();

        for (int i = 0; i < n; i++)
        {
            int step = 0, rest = 0;
            for (; step < n; step++)
            {
                int index = (i + step) % n;
                rest = rest + gas[index] - cost[index];
                if (rest <= 0)
                    break;
            }
            if (rest > 0)
                return i;
        }

        return -1;
    }

    // 2
    int maxSumDivThree(vector<int> &nums)
    {
        const int INF = 0x3f3f3f;
        int n = nums.size(), sum = 0;
        int x1 = INF, x2 = INF;
        int y1 = INF, y2 = INF;

        for (auto n : nums)
        {
            sum += n;

            if (n % 3 == 1)
            {
                if (n < x2)
                    x1 = x2, x2 = n;
                else if (n < x1)
                    x1 = n;
            }
            else if (n % 3 == 2)
            {
                if (n < y2)
                    y1 = y2, y2 = n;
                else if (n < y1)
                    y1 = n;
            }
        }

        if (sum % 3 == 0)
            return sum;
        else if (sum % 3 == 1)
            return max(sum - x2, sum - y1 - y2);
        else
            return max(sum - y2, sum - x1 - x2);
    }

    // 3
    int brokenCalc(int startValue, int target)
    {
        int ret = 0;

        while (target > startValue)
        {
            if (target % 2 == 0)
                target /= 2;
            else
                target += 1;
            ret++;
        }

        return ret + startValue - target;
    }

    // 4
    int findContentChildren(vector<int> &g, vector<int> &s)
    {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        int m = g.size(), n = s.size(), ret = 0;

        for (int i = 0, j = 0; i < m && j < n; i++, j++)
        {
            while (j < n && s[j] < g[i])
                j++;
            if (j < n)
                ret++;
        }

        return ret;
    }

    // 5
    vector<int> tmp;
    vector<int> ret;
    vector<int> index;
    vector<int> tmpIndex;
    vector<int> countSmaller(vector<int> &nums)
    {
        int n = nums.size();
        tmp.resize(n);
        ret.resize(n);
        index.resize(n);
        tmpIndex.resize(n);

        for (int i = 0; i < n; i++)
            index[i] = i;

        mergeSort(nums, 0, nums.size() - 1);

        return ret;
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
        {
            if (nums[cur1] <= nums[cur2])
            {
                tmp[i] = nums[cur2];
                tmpIndex[i++] = index[cur2++];
            }
            else
            {
                ret[index[cur1]] += right - cur2 + 1;
                tmp[i] = nums[cur1];
                tmpIndex[i++] = index[cur1++];
            }
        }
        while (cur1 <= mid)
        {
            tmp[i] = nums[cur1];
            tmpIndex[i++] = index[cur1++];
        }
        while (cur2 <= right)
        {
            tmp[i] = nums[cur2];
            tmpIndex[i++] = index[cur2++];
        }

        for (int j = left; j <= right; j++)
        {
            nums[j] = tmp[j - left];
            index[j] = tmpIndex[j - left];
        }
    }

    // 6
    string largestNumber(vector<int> &nums)
    {
        vector<string> strs;
        for (auto n : nums)
            strs.push_back(to_string(n));

        sort(strs.begin(), strs.end(), [](const string &s1, const string &s2)
             { return s1 + s2 > s2 + s1; });

        string ret;
        for (auto s : strs)
            ret += s;

        return ret[0] == '0' ? "0" : ret;
    }
};