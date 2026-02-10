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
    // 2
    int findLengthOfLCIS(vector<int> &nums)
    {
        int n = nums.size(), ret = 0;
        for (int left = 0, right = 0; right < n; right++)
        {
            while (right + 1 < n && nums[right + 1] > nums[right])
                right++;
            ret = max(ret, right - left + 1);
            left = right + 1;
        }
        return ret;
    }

    // 3
    int largestSumAfterKNegations(vector<int> &nums, int k)
    {
        int n = nums.size(), minElem = INT_MAX, count = 0;

        for (auto num : nums)
        {
            if (num < 0)
                count++;
            minElem = min(minElem, abs(num));
        }

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

    // 4
    int eraseOverlapIntervals(vector<vector<int>> &intervals)
    {
        // 1. 先按开始时间排序（如果开始时间相同，按结束时间排序）
        // 这样我们可以从左到右处理区间
        sort(intervals.begin(), intervals.end());

        // 记录最少需要移除的区间数量
        int ret = 0;

        // 2. 初始化：以第一个区间为基准
        // left: 当前保留区间的开始时间（其实后面没用到）
        // right: 当前保留区间的结束时间
        int left = intervals[0][0];
        int right = intervals[0][1];

        // 3. 从第二个区间开始遍历
        for (int i = 1; i < intervals.size(); i++)
        {
            // 当前检查的区间
            int a = intervals[i][0]; // 当前区间开始时间
            int b = intervals[i][1]; // 当前区间结束时间

            // 情况1：有重叠（当前区间开始时间 < 已保留区间的结束时间）
            if (a < right)
            {
                // 必须移除一个区间，移除数量+1
                ret++;

                // 关键决策：保留结束时间更早的那个区间
                // 因为结束越早，给后面区间留的空间越大
                right = min(right, b);
            }
            // 情况2：没有重叠
            else
            {
                // 接受当前区间，更新结束时间为当前区间的结束时间
                right = b;
            }
        }

        return ret;
    }
};

// 1
const int N = 1010;
int V[N], W[N], dp[N][N];
int n, v;

int main()
{
    cin >> n >> v;
    for (int i = 1; i <= n; i++)
        cin >> V[i] >> W[i];

    memset(dp, 0, sizeof dp);
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= v; j++)
        {
            dp[i][j] = dp[i - 1][j];

            if (j >= V[i])
                dp[i][j] = max(dp[i][j], dp[i][j - V[i]] + W[i]);
        }

    cout << dp[n][v] << endl;

    memset(dp, 0, sizeof dp);
    for (int i = 1; i <= v; i++)
        dp[0][i] = -1;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= v; j++)
        {
            dp[i][j] = dp[i - 1][j];

            if (j >= V[i] && dp[i][j - V[i]] != -1)
                dp[i][j] = max(dp[i][j], dp[i][j - V[i]] + W[i]);
        }

    cout << (dp[n][v] == -1 ? 0 : dp[n][v]) << endl;
    return 0;
}