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
    int jump(vector<int> &nums)
    {
        int left = 0, right = 0, maxPos = 0, ret = 0, n = nums.size();

        while (left <= right)
        {
            if (maxPos >= n - 1)
                return ret;

            for (int i = left; i <= right; i++)
                maxPos = max(maxPos, nums[i] + i);

            left = right + 1;
            right = maxPos;
            ret++;
        }

        return -1;
    }

    // 1
    int minOperations(vector<int> &nums, int x)
    {
        int sum = 0;
        for (auto n : nums)
            sum += n;

        int aim = sum - x;
        if (aim < 1)
            return -1;

        int ret = 0;
        for (int left = 0, right = 0, tmp = 0; right < nums.size(); right++)
        {
            tmp += nums[right];
            while (tmp > aim)
                tmp -= nums[left++];
            if (tmp == aim)
                ret = max(ret, right - left + 1);
        }

        return nums.size() - ret;
    }

    // 2
    int subarraySum(vector<int> &nums, int k)
    {
        unordered_map<int, int> hash;
        hash[0] = -1;

        int ret = 0, sum = 0;
        for (auto n : nums)
        {
            sum += n;
            if (hash.count(sum - k))
                ret += hash[sum - k];
            hash[sum]++;
        }

        return ret;
    }

    // 3
    typedef pair<string, int> PSI;

    struct cmp
    {
        bool operator()(const PSI &p1, const PSI &p2)
        {
            if (p1.second == p2.second)
                return p1.first > p2.first;
            return p1.second < p2.second;
        }
    };

    vector<string> topKFrequent(vector<string> &words, int k)
    {
        unordered_map<string, int> hash;
        for (auto word : words)
            hash[word]++;

        priority_queue<PSI, vector<PSI>, cmp> q;
        for (auto &pair : hash)
            q.push(pair);

        vector<string> ret;
        while (k--)
        {
            auto [a, b] = q.top();
            q.pop();
            ret.push_back(a);
        }

        return ret;
    }

    // 4
    int sum = 0, xorsum = 0;
    int subsetXORSum(vector<int> &nums)
    {
        dfs(nums, 0);
        return sum;
    }

    void dfs(vector<int> &nums, int pos)
    {
        sum += xorsum;

        for (int i = pos; i < nums.size(); i++)
        {
            xorsum ^= nums[i];
            dfs(nums, i + 1);
            xorsum ^= nums[i];
        }
    }

    // 5
    int lengthOfLIS(vector<int> &nums)
    {
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
                    if (ret[mid] < nums[i])
                        left = mid + 1;
                    else
                        right = mid;
                }
                ret[left] = nums[i];
            }
        }

        return ret.size() + 1;
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
            pickRightFork();
            pickLeftFork();
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