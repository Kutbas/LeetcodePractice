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
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost)
    {
        int n = gas.size();

        for (int i = 0; i < n; i++)
        {
            int rest = 0, step = 0;
            for (; step < n; step++)
            {
                int index = (i + step) % n;
                rest += gas[index] - cost[index];
                if (rest < 0)
                    break;
            }
            if (rest >= 0)
                return i;
            i = step;
        }
        return -1;
    }

    // 2
    int jump(vector<int> &nums)
    {
        int n = nums.size(), ret = 0, cur = 0, far = 0;

        for (int i = 0; i < n - 1; i++)
        {
            far = max(far, i + nums[i]);

            if (cur == i)
            {
                cur = far;
                ret++;

                if (cur >= n - 1)
                    break;
            }
        }

        return ret;
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

        int ret = 0;
        double tar = sum / 2.0;
        while (sum > tar)
        {
            auto t = q.top();
            q.pop();

            ret++;
            sum -= t / 2.0;
            q.push(t / 2.0);
        }

        return ret;
    }

    // 4
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
        for (auto n : nums1)
        {
            if (n > nums2[index2[left]])
                ret[index2[left++]] = n;
            else
                ret[index2[right--]] = n;
        }

        return ret;
    }

    // 5
    int lengthOfLIS(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> ret;
        ret.push_back(nums[0]);

        for (int i = 1; i < n; i++)
        {
            if (nums[i] > ret.back())
                ret.push_back(nums[i]);
            else
            {
                int left = 0, right = ret.size() - 1;
                while (left < right)
                {
                    int mid = left + (right - left) / 2;
                    if (nums[i] < ret[mid])
                        left = mid + 1;
                    else
                        right = mid;
                }
                ret[left] = nums[i];
            }
        }

        return ret.size();
    }

    // 6
    int ret = 0, aim;
    int findTargetSumWays(vector<int> &nums, int target)
    {
        aim = target;
        dfs(nums, 0, 0);
        return ret;
    }

    void dfs(vector<int> &nums, int pos, int sum)
    {
        if (pos == nums.size())
        {
            if (sum == aim)
                ret++;
            return;
        }

        if (sum > aim)
            return;

        dfs(nums, pos + 1, sum + nums[pos]);
        dfs(nums, pos + 1, sum - nums[pos]);
    }

    // 7
    int tmp[50010];
    int reversePairs(vector<int> &nums)
    {
        return mergeSort(nums, 0, nums.size() - 1);
    }

    int mergeSort(vector<int> &nums, int left, int right)
    {
        if (left >= right)
            return 0;

        int ret = 0, mid = left + (right - left) / 2;
        ret += mergeSort(nums, left, mid);
        ret += mergeSort(nums, mid + 1, right);

        int cur1 = left, cur2 = mid + 1, i = 0;
        while (cur1 <= mid)
        {
            if (nums[cur1] <= nums[cur2] * 2.0)
                cur2++;
            else
            {
                ret += right - cur2 + 1;
                cur1++;
            }
        }

        cur1 = left, cur2 = mid + 1;
        while (cur1 <= mid && cur2 <= right)
            tmp[i++] = nums[cur1] <= nums[cur2] ? nums[cur2++] : nums[cur1++];
        while (cur1 <= mid)
            tmp[i++] = nums[cur1++];
        while (cur2 <= right)
            tmp[i++] = nums[cur2++];

        for (int j = left; j <= right; j++)
            nums[j] = tmp[j - left];

        return ret;
    }
};