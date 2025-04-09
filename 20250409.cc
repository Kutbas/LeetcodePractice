#include <bits/stdc++.h>
using namespace std;


struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

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

    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        return merge(lists, 0, lists.size() - 1);
    }

    ListNode *merge(vector<ListNode *> lists, int left, int right)
    {
        if (left > right)
            return nullptr;
        if (left == right)
            return lists[left];

        int mid = left + (right - left) / 2;

        ListNode *l1 = merge(lists, left, mid);
        ListNode *l2 = merge(lists, mid + 1, right);

        return mergeTwoLists(l1, l2);
    }

    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
    {
        if (l1 == nullptr)
            return l2;
        if (l2 == nullptr)
            return l1;

        ListNode head;
        ListNode *cur1 = l1, *cur2 = l2, *prev = &head;

        while (cur1 || cur2)
        {
            if (cur1->val < cur2->val)
            {
                prev = prev->next = cur1;
                cur1 = cur1->next;
            }
            else
            {
                prev = prev->next = cur2;
                cur2 = cur2->next;
            }
        }

        if (cur1)
            prev = prev->next = cur1;
        if (cur2)
            prev = prev->next = cur2;

        return head.next;
    }

    vector<vector<int>> fourSum(vector<int> &nums, int target)
    {
        sort(nums.begin(), nums.end());
        vector<vector<int>> ret;

        int n = nums.size();
        int i = 0;
        while (i < n - 3)
        {
            int j = i + 1;
            while (j < n - 2)
            {
                int left = j + 1, right = n - 1;
                while (left < right)
                {
                    long long aim = (long long)target - nums[i] - nums[j];
                    if (nums[left] + nums[right] > aim)
                        right--;
                    else if (nums[left] + nums[right] < aim)
                        left++;
                    else
                    {
                        ret.push_back({nums[i], nums[j], nums[left], nums[right]});

                        do
                        {
                            left++;
                        } while (nums[left] == nums[left - 1] && left < right);
                        do
                        {
                            right--;
                        } while (nums[right] == nums[right + 1] && left < right);
                    }
                }

                do
                {
                    j++;
                } while (nums[j] == nums[j - 1] && j < n - 3);
            }

            do
            {
                i++;
            } while (nums[i] == nums[i - 1] && i < n - 3);
        }

        return ret;
    }

    string longestPalindrome(string s)
    {
        int n = s.size();
        if (n < 2)
            return s;

        vector<vector<int>> dp(n, vector<int>(n));
        for (int i = 0; i < n; i++)
            dp[i][i] = true;

        int begin = -1, maxLen = 1;

        for (int L = 2; L <= n; L++)
        {
            for (int i = 0; i < n; i++)
            {
                int j = i + L - 1;
                if (j >= n)
                    break;

                if (s[i] != s[j])
                    dp[i][j] = false;
                else
                {
                    if (j - i < 3)
                        dp[i][j] = true;
                    else
                        dp[i][j] = dp[i + 1][j - 1];
                }

                if (dp[i][j] && j - i + 1 > maxLen)
                {
                    maxLen = j - i + 1;
                    begin = i;
                }
            }
        }

        return s.substr(begin, maxLen);
    }

    int minNumberOfFrogs(string croakOfFrogs)
    {
        string s = "croak";
        int n = s.size();

        unordered_map<char, int> index;
        vector<int> hash(n);

        for (int i = 0; i < n; i++)
            index[s[i]] = i;

        for (auto ch : croakOfFrogs)
        {
            if (ch == 'c')
            {
                if (hash[n - 1] != 0)
                {
                    hash[n - 1]--;
                    hash[0]++;
                }
                else
                    hash[0]++;
            }
            else
            {
                if (!index.count(ch))
                    return -1;
                else
                {
                    int pos = index[ch];

                    if (hash[pos - 1] == 0)
                        return -1;
                    else
                    {
                        hash[pos - 1]--;
                        hash[pos]++;
                    }
                }
            }
        }

        for (int i = 0; i < n - 1; i++)
            if (hash[i])
                return -1;
        return hash[n - 1];
    }

    int getSum(int a, int b)
    {
        while (b)
        {
            int xorsum = a ^ b;
            unsigned int carry = (a & b) << 1;
            a = xorsum;
            b = carry;
        }
        return a;
    }

    string longestPalindrome(string s)
    {
        int n = s.size();
        if (n < 2)
            return s;

        int begin = 0, maxlen = 1;

        vector<vector<int>> dp(n, vector<int>(n));
        for (int i = 0; i < n; i++)
            dp[i][i] = true;

        for (int L = 2; L <= n; L++)
            for (int i = 0; i < n; i++)
            {
                int j = i + L - 1;
                if (j >= n)
                    break;

                if (s[i] != s[j])
                    dp[i][j] = false;
                else
                {
                    if (j - i + 1 <= 2)
                        dp[i][j] = true;
                    else
                        dp[i][j] = dp[i + 1][j - 1];
                }

                if (dp[i][j] && j - i + 1 > maxlen)
                {
                    begin = i;
                    maxlen = j - i + 1;
                }
            }

        return s.substr(begin, maxlen);
    }
};
