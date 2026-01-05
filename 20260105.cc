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
    int findLengthOfLCIS(vector<int> &nums)
    {
        int n = nums.size();
        int ret = 0;
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
    int K;
    vector<vector<int>> ret;
    vector<int> path;
    vector<vector<int>> combine(int n, int k)
    {
        K = k;
        dfs(n, 1);
        return ret;
    }

    void dfs(int n, int pos)
    {
        if (path.size() == K)
        {
            ret.push_back(path);
            return;
        }

        for (int i = pos; i <= n; i++)
        {
            path.push_back(i);
            dfs(n, i + 1);
            path.pop_back();
        }
    }

    // 5
    ListNode *swapPairs(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *ret = new ListNode(0);
        ListNode *prev = ret;
        ListNode *cur = head, *next = cur->next, *nnext = next->next;

        while (cur && next)
        {
            prev->next = next;
            next->next = cur;
            cur->next = nnext;
            prev = cur;
            cur = nnext;
            if (cur)
                next = cur->next;
            if (next)
                nnext = next->next;
        }

        prev = ret->next;
        delete ret, cur, next, nnext;
        return prev;
    }

    // 6
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    bool vis[51][51] = {0};
    int maxAreaOfIsland(vector<vector<int>> &grid)
    {
        m = grid.size(), n = grid[0].size();

        int ret = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == 1 && !vis[i][j])
                    ret = max(ret, dfs(grid, i, j));
            }

        return ret;
    }

    int dfs(vector<vector<int>> &grid, int i, int j)
    {
        int ret = 1;
        vis[i][j] = true;
        queue<pair<int, int>> q;
        q.push({i, j});

        while (q.size())
        {
            auto [a, b] = q.front();
            q.pop();
            for (int k = 0; k < 4; k++)
            {
                int x = a + dx[k], y = b + dy[k];
                if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && grid[x][y] == 1)
                {
                    ret++;
                    q.push({x, y});
                    vis[x][y] = true;
                }
            }
        }

        return ret;
    }

    // 7
    int lengthOfLIS(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> ret;

        ret.push_back(nums[0]);
        for (int i = 1; i < nums.size(); i++)
        {
            if (nums[i] > ret.back())
                ret.push_back(nums[i]);
            else
            {
                int left = 0, right = ret.size() - 1;
                while (left < right)
                {
                    int mid = left + (right - left) / 2;
                    if (nums[i] > ret[mid])
                        left = mid + 1;
                    else
                        right = mid;
                }
                ret[left] = nums[i];
            }
        }
        return ret.size();
    }
};

// 2
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

// 4
class MedianFinder
{
public:
    MedianFinder()
    {
    }

    void addNum(int num)
    {
        if (left.size() == right.size())
        {
            if (left.empty() || num < left.top())
                left.push(num);
            else
            {
                right.push(num);
                left.push(right.top());
                right.pop();
            }
        }
        else
        {
            if (num > right.top())
                right.push(num);
            else
            {
                left.push(num);
                right.push(left.top());
                left.pop();
            }
        }
    }

    double findMedian()
    {
        return left.size() == right.size() ? (left.top() + right.top()) / 2.0 : left.top();
    }

private:
    priority_queue<double> left;
    priority_queue<double, vector<double>, greater<double>> right;
};