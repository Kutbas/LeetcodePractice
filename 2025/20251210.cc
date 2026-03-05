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
    int calculateMinimumHP(vector<vector<int>> &dungeon)
    {
        int m = dungeon.size(), n = dungeon[0].size();

        vector<vector<int>> dp(m + 1, vector<int>(n + 1, INT_MAX));
        dp[m][n - 1] = dp[m - 1][n] = 1;

        for (int i = m - 1; i >= 0; i--)
            for (int j = n - 1; j >= 0; j--)
            {
                int min_required = min(dp[i + 1][j], dp[i][j + 1]);

                dp[i][j] = min_required - dungeon[i][j];

                dp[i][j] = max(dp[i][j], 1);
            }

        return dp[0][0];
    }

    // 2
    int lastStoneWeightII(vector<int> &stones)
    {
        int n = stones.size(), sum = 0;
        for (auto n : stones)
            sum += n;

        int m = sum / 2;
        vector<vector<int>> dp(n + 1, vector<int>(m + 1));

        for (int i = 1; i <= n; i++)
            for (int j = 0; j <= m; j++)
            {
                dp[i][j] = dp[i - 1][j];
                if (j >= stones[i - 1])
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - stones[i - 1]] + stones[i - 1]);
            }

        return sum - 2 * dp[n][m];
    }

    // 4
    vector<vector<int>> ret;
    vector<int> path;
    int aim;
    vector<vector<int>> combinationSum(vector<int> &candidates, int target)
    {
        aim = target;
        dfs(candidates, 0, 0);
        return ret;
    }

    void dfs(vector<int> &nums, int pos, int sum)
    {
        if (sum == aim)
        {
            ret.push_back(path);
            return;
        }

        if (sum > aim || pos == nums.size())
            return;

        for (int i = pos; i < nums.size(); i++)
        {
            path.push_back(nums[i]);
            dfs(nums, i, sum + nums[i]);
            path.pop_back();
        }
    }

    // 5
    int findLengthOfLCIS(vector<int> &nums)
    {
        int n = nums.size(), ret = 1;
        for (int left = 0, right = 0; right < n; right++)
        {
            while (right + 1 < n && nums[right + 1] > nums[right])
                right++;
            ret = max(ret, right - left + 1);
            left = right + 1;
        }
        return ret;
    }

    // 6
    int maxProfit(vector<int> &prices)
    {
        int n = prices.size(), ret = 0;
        for (int i = 0; i < n; i++)
        {
            int j = i;
            while (j + 1 < n && prices[j + 1] > prices[j])
                j++;
            ret += prices[j] - prices[i];
            i = j;
        }
        return ret;
    }

    // 7
    int numDecodings(string s)
    {
        int n = s.size();

        vector<int> dp(n);
        dp[0] = s[0] == '0' ? 0 : 1;
        if (n == 1)
            return dp[0];

        if (s[0] != '0' && s[1] != '0')
        {
            int twoDigits = (s[0] - '0') * 10 + (s[1] - '0');
            if (twoDigits >= 10 && twoDigits <= 26)
                dp[0] += 1;
        }

        for (int i = 2; i < n; i++)
        {
            dp[i] += dp[i - 1];

            if (s[i] != '0' && s[i - 1] != '0')
            {
                int twoDigits = (s[i - 1] - '0') * 10 + (s[i] - '0');
                if (twoDigits >= 10 && twoDigits <= 26)
                    dp[i] += dp[i - 2];
            }
        }

        return dp[n - 1];
    }
};

// 3
class DiningPhilosophers
{
public:
    DiningPhilosophers()
    {
    }

    void wantsToEat(int philosopher,
                    function<void()> pickLeftFork,
                    function<void()> pickRightFork,
                    function<void()> eat,
                    function<void()> putLeftFork,
                    function<void()> putRightFork)
    {
        int l = philosopher, r = (philosopher + 1) % 5;

        if (l % 2 == 0)
        {
            lock[l].lock();
            lock[r].lock();
        }
        else
        {
            lock[r].lock();
            lock[l].lock();
        }
        pickLeftFork();
        pickRightFork();
        eat();
        putLeftFork();
        putRightFork();
        lock[l].unlock();
        lock[r].unlock();
    }

private:
    std::mutex lock[5];
};