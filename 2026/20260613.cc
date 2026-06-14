#include <bits/stdc++.h>
#include <mutex>
using namespace std;

class Solution
{
public:
    // 1
    vector<int> searchRange(vector<int> &nums, int target)
    {
        int n = nums.size();
        if (n == 0)
            return {-1, -1};

        int left = 0, right = n - 1;
        while (left < right)
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] < target)
                left = mid + 1;
            else
                right = mid;
        }

        if (nums[left] != target)
            return {-1, -1};

        int tmp = left;
        left = 0, right = n - 1;
        while (left < right)
        {
            int mid = left + (right - left + 1) / 2;
            if (nums[mid] <= target)
                left = mid;
            else
                right = mid - 1;
        }

        return {tmp, left};
    }

    // 2
    vector<vector<int>> generate(int numRows)
    {
        vector<vector<int>> ret(numRows);

        for (int i = 0; i < numRows; i++)
        {
            ret[i].resize(i + 1);
            ret[i][0] = ret[i][i] = 1;

            for (int j = 1; j < i; j++)
                ret[i][j] = ret[i - 1][j - 1] + ret[i - 1][j];
        }

        return ret;
    }

    // 3
    int largestSumAfterKNegations(vector<int> &nums, int k)
    {
        int n = nums.size(), minElem = INT_MAX, count = 0, sum = 0;

        for (auto num : nums)
        {
            if (num < 0)
                count++;
            minElem = min(minElem, abs(num));
        }

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
            // count<=k;
            for (auto num : nums)
                sum += abs(num);

            if ((k - count) % 2 == 1)
                sum -= 2 * minElem;
        }

        return sum;
    }

    // 4
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
};