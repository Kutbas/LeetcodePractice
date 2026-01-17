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
    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        return mergeSort(lists, 0, lists.size() - 1);
    }

    ListNode *mergeSort(vector<ListNode *> &lists, int left, int right)
    {
        if (left > right)
            return nullptr;
        if (left == right)
            return lists[left];

        int mid = left + (right - left) / 2;
        ListNode *cur1 = mergeSort(lists, left, mid);
        ListNode *cur2 = mergeSort(lists, mid + 1, right);

        return merge2Lists(cur1, cur2);
    }

    ListNode *merge2Lists(ListNode *l1, ListNode *l2)
    {
        if (l1 == nullptr)
            return l2;
        if (l2 == nullptr)
            return l1;

        ListNode *ret = new ListNode(0);
        ListNode *prev = ret;
        ListNode *cur1 = l1, *cur2 = l2;
        while (cur1 && cur2)
        {
            if (cur1->val < cur2->val)
            {
                prev->next = cur1;
                cur1 = cur1->next;
                prev = prev->next;
            }
            else
            {
                prev->next = cur2;
                cur2 = cur2->next;
                prev = prev->next;
            }
        }
        if (cur1)
            prev->next = cur1;
        if (cur2)
            prev->next = cur2;

        prev = ret->next;
        delete ret;
        return prev;
    }

    // 2
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
            g[i] = max(g[i - 1], f[i - 1]);
        }

        return max(f[N - 1], g[N - 1]);
    }

    // 4
    int findNumberOfLIS(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> longestLength(n, 1);
        vector<int> ways(n, 1);
        int globalLongestLength = 1;
        int globalWays = 1;

        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (nums[j] < nums[i])
                {
                    int newlen = longestLength[j] + 1;
                    if (newlen == longestLength[i])
                        ways[i] += ways[j];
                    else if (newlen > longestLength[i])
                    {
                        longestLength[i] = newlen;
                        ways[i] = ways[j];
                    }
                }
            }

            if (longestLength[i] == globalLongestLength)
                globalWays += ways[i];
            else if (longestLength[i] > globalLongestLength)
            {
                globalWays = ways[i];
                globalLongestLength = longestLength[i];
            }
        }

        return globalWays;
    }

    // 5
    int ret = 0, N;
    bool vis[16] = {0};
    int countArrangement(int n)
    {
        N = n;
        dfs(1);
        return ret;
    }

    void dfs(int pos)
    {
        if (pos == N + 1)
        {
            ret++;
            return;
        }

        for (int i = 1; i <= N; i++)
        {
            if (!vis[i] && (i % pos == 0 || pos % i == 0))
            {
                vis[i] = true;
                dfs(pos + 1);
                vis[i] = false;
            }
        }
    }

    // 6
    int MoreThanHalfNum_Solution(vector<int> &numbers)
    {
        int ret = numbers[0], count = 1;

        for (auto n : numbers)
        {
            if (n == ret)
                count++;
            else if (--count == 0)
            {
                ret = n;
                count = 1;
            }
        }

        return ret;
    }


};

// 3
class DiningPhilosophers
{
public:
    DiningPhilosophers() {}

    void wantsToEat(int philosopher, function<void()> pickLeftFork,
                    function<void()> pickRightFork, function<void()> eat,
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