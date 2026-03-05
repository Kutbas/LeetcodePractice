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
    int tribonacci(int n)
    {
        if (n == 0)
            return 0;

        if (n == 1 || n == 2)
            return 1;

        int a = 0, b = 1, c = 1, d = 0;
        for (int i = 3; i <= n; i++)
        {
            d = a + b + c;
            a = b;
            b = c;
            c = d;
        }

        return d;
    }

    // 2
    int lastStoneWeightII(vector<int> &stones)
    {
        int n = stones.size(), sum = 0;
        for (auto x : stones)
            sum += x;

        int m = sum / 2;
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
            {
                dp[i][j] = dp[i - 1][j];
                if (j >= stones[i - 1])
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - stones[i - 1]] + stones[i - 1]);
            }

        return sum - 2 * dp[n][m];
    }

    // 3
    bool containsNearbyDuplicate(vector<int> &nums, int k)
    {
        unordered_map<int, int> hash;
        for (int i = 0; i < nums.size(); i++)
        {
            if (hash.count(nums[i]) && i - hash[nums[i]] <= k)
                return true;
            hash[nums[i]] = i;
        }

        return false;
    }
};

// 4
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
        int l = philosopher;
        int r = (philosopher + 1) % 5;

        if (l % 2 == 0)
        {
            lock[l].lock();
            lock[r].lock();
            pickLeftFork();
            pickRightFork();
        }
        else
        {
            lock[r].lock();
            lock[l].lock();
            pickLeftFork();
            pickRightFork();
        }
        eat();
        putLeftFork();
        putRightFork();
        lock[l].unlock();
        lock[r].unlock();
    }

private:
    std::mutex lock[5];
};