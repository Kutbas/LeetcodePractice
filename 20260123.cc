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
    vector<int> countBits(int n)
    {
        vector<int> ret;

        for (int i = 0; i <= n; i++)
        {
            int count = 0;
            for (int j = 0; j < 32; j++)
            {
                if ((i >> j) & 1)
                    count++;
            }
            ret.push_back(count);
        }

        return ret;
    }

    // 2
    int largestSumAfterKNegations(vector<int> &nums, int k)
    {
        int n = nums.size(), minElem = INT_MAX, count = 0;
        for (auto n : nums)
        {
            if (n < 0)
                count++;
            minElem = min(minElem, abs(n));
        }

        int ret = 0;
        if (count > k)
        {
            sort(nums.begin(), nums.end());
            for (int i = 0; i < k; i++)
                ret += -nums[i];
            for (int i = k; i < n; i++)
                ret += nums[i];
        }
        else
        {
            for (auto n : nums)
                ret += abs(n);
            if ((k - count) % 2 == 1)
                ret -= 2 * minElem;
        }

        return ret;
    }

    // 3
    int hammingWeight(int n)
    {
        int ret = 0;
        while (n)
        {
            n &= (n - 1);
            ret++;
        }
        return ret;
    }

    // 4
    vector<int> smallestK(vector<int> &arr, int k)
    {
        srand(time(NULL));
        quickSort(arr, 0, arr.size() - 1, k);
        return {arr.begin(), arr.begin() + k};
    }

    int getRandom(vector<int> &nums, int left, int right)
    {
        int r = rand();
        return nums[r % (right - left + 1) + left];
    }

    void quickSort(vector<int> &nums, int l, int r, int k)
    {
        if (l >= r)
            return;

        int key = getRandom(nums, l, r);
        int i = l, left = l - 1, right = r + 1;

        while (i < right)
        {
            if (nums[i] < key)
                swap(nums[i++], nums[++left]);
            else if (nums[i] == key)
                i++;
            else
                swap(nums[i], nums[--right]);
        }

        int lRange = left - l + 1, mRange = (right - 1) - (left + 1) + 1;
        if (lRange >= k)
            quickSort(nums, l, left, k);
        else if (lRange + mRange >= k)
            return;
        else
            quickSort(nums, right, r, k - lRange - mRange);
    }

    // 5
    string multiply(string num1, string num2)
    {
        int m = num1.size(), n = num2.size();

        vector<int> tmp(m + n - 1);
        for (int i = m - 1; i >= 0; i--)
            for (int j = n - 1; j >= 0; j--)
                tmp[i + j] += (num1[i] - '0') * (num2[j] - '0');

        string ret;
        int t = 0, i = m + n - 2;
        while (t || i >= 0)
        {
            if (i >= 0)
                t += tmp[i--];

            ret += to_string(t % 10);
            t /= 10;
        }

        reverse(ret.begin(), ret.end());
        return ret[0] == '0' ? "0" : ret;
    }

    // 6
    string countAndSay(int n)
    {
        string ret = "1";

        for (int i = 1; i < n; i++)
        {
            string tmp;
            int len = ret.size();
            for (int left = 0, right = 0; right < len; right++)
            {
                while (right + 1 < len && ret[right + 1] == ret[right])
                    right++;
                tmp += to_string(right - left + 1) + ret[left];
                left = right + 1;
            }
            ret = tmp;
        }
        return ret;
    }

    // 7
    int maxEnvelopes(vector<vector<int>> &e)
    {
        int n = e.size();

        sort(e.begin(), e.end(),
             [&](const vector<int> &v1, const vector<int> &v2)
             {
                 return v1[0] != v2[0] ? v1[0] < v2[0] : v1[1] > v2[1];
             });

        vector<int> ret;
        ret.push_back(e[0][1]);
        for (int i = 1; i < n; i++)
        {
            if (e[i][1] > ret.back())
                ret.push_back(e[i][1]);
            else
            {
                int left = 0, right = ret.size() - 1;
                while (left < right)
                {
                    int mid = left + (right - left) / 2;
                    if (e[i][1] > ret[mid])
                        left = mid + 1;
                    else
                        right = mid;
                }
                ret[left] = e[i][1];
            }
        }

        return ret.size();
    }
};