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

                if (far >= n - 1)
                    break;
            }
        }

        return ret;
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

    // 3
    int halveArray(vector<int> &nums)
    {
        priority_queue<double> q;
        double sum = 0;
        for (auto n : nums)
        {
            q.push(n);
            sum += n;
        }

        double aim = sum / 2.0;
        int ret = 0;

        while (sum > aim)
        {
            auto t = q.top() / 2.0;
            q.pop();
            q.push(t);
            sum -= t;
            ret++;
        }

        return ret;
    }

    // 4
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

    // 5
    vector<vector<int>> ret;
    vector<int> path;
    bool vis[7];
    vector<vector<int>> permute(vector<int> &nums)
    {
        dfs(nums, 0);
        return ret;
    }

    void dfs(vector<int> &nums, int pos)
    {
        if (path.size() == nums.size())
        {
            ret.push_back(path);
            return;
        }

        for (int i = pos; i < nums.size(); i++)
        {
            if (!vis[i])
            {
                vis[i] = true;
                path.push_back(nums[i]);
                dfs(nums, i);
                path.pop_back();
                vis[i] = false;
            }
        }
    }
};

// 6
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