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
    int countSubstrings(string s)
    {
        int n = s.size();
        vector<vector<bool>> dp(n, vector<bool>(n));

        int ret = 0;
        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = i; j < n; j++)
            {
                if (s[i] == s[j])
                    dp[i][j] = i + 1 < j ? dp[i + 1][j - 1] : true;
                if (dp[i][j])
                    ret++;
            }
        }

        return ret;
    }

    // 1
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost)
    {
        int n = gas.size();

        for (int i = 0; i < n; i++)
        {
            int rest = 0, step = 0;
            for (; step < n; step++)
            {
                int index = (i + step) % n;
                rest = rest + gas[index] - cost[index];
                if (rest < 0)
                    break;
            }
            if (rest >= 0)
                return i;
            i = i + step;
        }
        return -1;
    }

    // 2
    int findContentChildren(vector<int> &g, vector<int> &s)
    {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());

        int ret = 0, m = g.size(), n = s.size();
        for (int i = 0, j = 0; i < m, j < n; i++, j++)
        {
            while (j < n && s[j] < g[i])
                j++;
            if (j < n)
                ret++;
        }

        return ret;
    }

    // 3
    int halveArray(vector<int> &nums)
    {
        priority_queue<int> q;
        double sum = 0;
        for (auto n : nums)
        {
            sum += n;
            q.push(n);
        }

        int ret = 0;
        double half = sum / 2.0;
        while (sum > half)
        {
            auto t = q.top();
            q.pop();

            sum -= t / 2.0;
            q.push(t / 2.0);

            ret++;
        }

        return ret;
    }

    // 4
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

    // 5
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

    // 6
    vector<int> advantageCount(vector<int> &nums1, vector<int> &nums2)
    {
        int n = nums1.size();
        sort(nums1.begin(), nums1.end());

        vector<int> index2(n);
        for (int i = 0; i < n; i++)
            index2[i] = i;

        sort(index2.begin(), index2.end(), [&](int i, int j)
             { return nums2[i] < nums2[j]; });

        vector<int> ret(n);
        int left = 0, right = n - 1;

        for (auto x : nums1)
        {
            if (x > nums2[index2[left]])
                ret[index2[left++]] = x;
            else
                ret[index2[right--]] = x;
        }

        return ret;
    }
};