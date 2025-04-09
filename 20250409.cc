#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        unordered_map<int, int> hash;
        for (int i = 0; i < nums.size(); i++)
        {
            int x = target - nums[i];
            if (hash.count(x))
                return {hash[x], i};
            hash[nums[i]] = i;
        }

        return {-1, -1};
    }

    bool CheckPermutation(string s1, string s2)
    {
        if (s1.size() != s2.size())
            return false;
        int hash[128] = {0};

        // 统计第一个字符串的信息
        for (auto ch : s1)
            hash[ch]++;

        for (auto ch : s2)
        {
            hash[ch]--;
            if (hash[ch] < 0)
                return false;
        }

        return true;
    }

    bool containsDuplicate(vector<int> &nums)
    {
        unordered_map<int, int> hash;

        for (int i = 0; i < nums.size(); i++)
        {
            if (hash.count(nums[i]))
                return true;
            hash[nums[i]]++;
        }
        return false;
    }

    string convert(string s, int numRows)
    {
        if (numRows == 1)
            return s;

        string ret;
        int n = s.size(), d = 2 * numRows - 2;

        for (int i = 0; i < n; i += d)
            ret += s[i];

        for (int k = 1; k < numRows - 1; k++)
        {
            for (int i = k, j = d - k; i < n || j < n; i += d, j += d)
            {
                if (i < n)
                    ret += s[i];
                if (j < n)
                    ret += s[j];
            }
        }

        for (int i = numRows - 1; i < n; i += d)
            ret += s[i];

        return ret;
    }

    void sortColors(vector<int> &nums)
    {
        int i = 0, left = i - 1, right = nums.size();
        while (i < right)
        {
            if (nums[i] < 1)
                swap(nums[i++], nums[++left]);
            else if (nums[i] == 1)
                i++;
            else
                swap(nums[i], nums[--right]);
        }
    }

    int hammingWeight(int n)
    {
        int ret = 0;
        while (n)
        {
            ret++;
            n &= n - 1;
        }

        return ret;
    }

    int countBit(int n)
    {
        int ret = 0;
        while (n)
        {
            ret++;
            n &= n - 1;
        }

        return ret;
    }

    vector<int> countBits(int n)
    {
        vector<int> ret(n + 1);
        for (int i = 0; i <= n; i++)
            ret[i] = countBit(i);

        return ret;
    }

    int missingNumber(vector<int> &nums)
    {
        int xorsum = 0;

        for (auto n : nums)
            xorsum ^= n;
        for (int i = 1; i <= nums.size(); i++)
            xorsum ^= i;

        return xorsum;
    }

    int mySqrt(int x)
    {
        if (x == 0)
            return 0;

        int left = 1, right = x;
        while (left < right)
        {
            int mid = left + (right - left + 1) / 2;
            if (mid * mid <= x)
                left = mid;
            else
                right = mid - 1;
        }
        return left;
    }

    string modifyString(string s)
    {
        int n = s.size();
        for (int i = 0; i < n; i++)
        {
            if (s[i] == '?')
            {
                for (char ch = 'a'; ch <= 'z'; ch++)
                {
                    if ((i == 0 || s[i - 1] != ch) && (i == n - 1 || s[i + 1] != ch))
                        s[i] = ch;
                }
            }
        }
        return s;
    }
};
