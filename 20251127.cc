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
                    dp[i][j] = max(dp[i][j], dp[i][j - stones[i - 1]] + stones[i - 1]);
            }

        return sum - 2 * dp[n][m];
    }

    // 2
    long prev = LONG_MIN;
    bool isValidBST(TreeNode *root)
    {
        if (root == nullptr)
            return true;

        bool left = isValidBST(root->left);
        if (!left)
            return false;

        bool cur = true;
        if (prev >= root->val)
            cur = false;
        if (!cur)
            return false;

        prev = root->val;
        bool right = isValidBST(root->right);
        return right;
    }

    // 3
    bool backspaceCompare(string s, string t)
    {
        string tmp1, tmp2;
        for (char ch : s)
        {
            if (ch == '#')
            {
                if (tmp1.size())
                    tmp1.pop_back();
            }
            else
                tmp1.push_back(ch);
        }

        for (char ch : t)
        {
            if (ch == '#')
            {
                if (tmp2.size())
                    tmp2.pop_back();
            }
            else
                tmp2.push_back(ch);
        }

        return tmp1 == tmp2;
    }

    // 5
    int deleteAndEarn(vector<int> &nums)
    {
        const int N = 10001;
        int arr[N] = {0};
        for (auto n : nums)
            arr[n] += n;

        vector<int> f(N), g(N);

        for (int i = 1; i < N; i++)
        {
            f[i] = g[i - 1] + arr[i];
            g[i] = max(f[i - 1], g[i - 1]);
        }

        return max(f[N - 1], g[N - 1]);
    }

    // 6
    bool isInterleave(string s1, string s2, string s3)
    {
        int m = s1.size(), n = s2.size();
        if (m + n != s3.size())
            return false;

        s1 = " " + s1;
        s2 = " " + s2;
        s3 = " " + s3;

        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1));

        for (int i = 1; i <= m; i++)
            if (s1[i] == s3[i])
                dp[i][0] = true;
            else
                break;

        for (int i = 1; i <= n; i++)
            if (s2[i] == s3[i])
                dp[0][i] = true;
            else
                break;

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                bool from_s1 = (s1[i] == s3[i + j] && dp[i - 1][j]);
                bool from_s2 = (s2[j] == s3[i + j] && dp[i][j - 1]);
                dp[i][j] = from_s1 || from_s2;
            }

        return dp[m][n];
    }

    // 7
    ListNode *reverseKGroup(ListNode *head, int k)
    {
        int count = 0;
        ListNode *cur = head;

        while (cur)
        {
            cur = cur->next;
            count++;
        }

        count /= k;

        ListNode *ret = new ListNode(0);
        ListNode *prev = ret;
        cur = head;

        for (int i = 0; i < count; i++)
        {
            ListNode *tmp = cur;
            for (int j = 0; j < k; j++)
            {
                ListNode *next = cur->next;
                cur->next = prev->next;
                prev->next = cur;
                cur = next;
            }
            prev = tmp;
        }

        prev->next = cur;

        prev = ret->next;
        delete ret;
        return prev;
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