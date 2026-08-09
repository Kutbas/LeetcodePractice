#include <mutex>
#include <vector>
#include <algorithm>
#include <climits>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <iostream>
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
    int longestOnes(vector<int> &nums, int k)
    {
        int n = nums.size(), ret = 0;

        for (int left = 0, right = 0, count = 0; right < n; right++)
        {
            if (nums[right] == 0)
                count++;
            while (count > k)
                if (nums[left++] == 0)
                    count--;
            ret = max(ret, right - left + 1);
        }

        return ret;
    }

    // 2
    int searchInsert(vector<int> &nums, int target)
    {
        int n = nums.size(), left = 0, right = nums.size() - 1;

        while (left < right)
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] < target)
                left = mid + 1;
            else
                right = mid;
        }

        return nums[left] < target ? left + 1 : left;
    }

    // 3
    bool isPalindrome(string s)
    {
        string tmp;
        for (char ch : s)
            if (isalnum(ch))
                tmp += tolower(ch);

        int left = 0, right = tmp.size() - 1;
        while (left < right)
        {
            if (tmp[left] == tmp[right])
                left++, right--;
            else
                return false;
        }

        return true;
    }

    // 4
    string longestCommonPrefix(vector<string> &strs)
    {
        for (int i = 0; i < strs[0].size(); i++)
            for (int j = 1; j < strs.size(); j++)
                if (i == strs[j].size() || strs[0][i] != strs[j][i])
                    return strs[0].substr(0, i);
        return strs[0];
    }

    // 5
    unordered_map<char, int> in;
    unordered_map<char, unordered_set<char>> edges;
    bool check = false;
    string alienOrder(vector<string> &words)
    {
        for (auto &word : words)
            for (auto &ch : word)
                in[ch] = 0;

        int n = words.size();
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
            {
                add(words[i], words[j]);
                if (check)
                    return "";
            }

        queue<char> q;
        for (auto [a, b] : in)
            if (b == 0)
                q.push(a);

        string ret;
        while (q.size())
        {
            auto t = q.front();
            q.pop();
            ret += t;

            for (auto a : edges[t])
                if (--in[a] == 0)
                    q.push(a);
        }

        for (auto [a, b] : in)
            if (b)
                return "";

        return ret;
    }

    void add(const string &s1, const string &s2)
    {
        int n = min(s1.size(), s2.size()), i = 0;

        for (; i < n; i++)
        {
            if (s1[i] != s2[i])
            {
                char a = s1[i], b = s2[i]; // a->b
                if (!edges.count(a) || !edges[a].count(b))
                {
                    in[b]++;
                    edges[a].insert(b);
                }
                break;
            }
        }

        if (i < s1.size() && i == s2.size())
            check = true;
    }

    // 6
    int maxSumDivThree(vector<int> &nums)
    {
        const int INF = 0x3f3f3f;
        int x1 = INF, x2 = INF, y1 = INF, y2 = INF;
        int sum = 0;

        for (auto n : nums)
        {
            sum += n;
            if (n % 3 == 1)
            {
                if (n < x1)
                    x2 = x1, x1 = n;
                else if (n < x2)
                    x2 = n;
            }
            else if (n % 3 == 2)
            {
                if (n < y1)
                    y2 = y1, y1 = n;
                else if (n < y2)
                    y2 = n;
            }
        }

        if (sum % 3 == 0)
            return sum;
        return sum % 3 == 1 ? max(sum - x1, sum - y1 - y2) : max(sum - y1, sum - x1 - x2);
    }

    // 7
    vector<int> rearrangeBarcodes(vector<int> &barcodes)
    {
        unordered_map<int, int> hash;
        int maxCount = 0, maxVal = 0, n = barcodes.size();

        for (auto num : barcodes)
            if (++hash[num] > maxCount)
            {
                maxCount = hash[num];
                maxVal = num;
            }

        vector<int> ret(n);
        int index = 0;
        for (int i = 0; i < maxCount; i++)
        {
            ret[index] = maxVal;
            index += 2;
        }

        hash.erase(maxVal);
        for (auto [a, b] : hash)
            for (int i = 0; i < b; i++)
            {
                if (index >= n)
                    index = 1;
                ret[index] = a;
                index += 2;
            }

        return ret;
    }

    // 8
    int findNumberOfLIS(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> longestLength(n, 1);
        vector<int> ways(n, 1);
        int globalLongestLength = 1, globalWays = 1;

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

            if (globalLongestLength == longestLength[i])
                globalWays += ways[i];
            else if (longestLength[i] > globalLongestLength)
            {
                globalWays = ways[i];
                globalLongestLength = longestLength[i];
            }
        }

        return globalWays;
    }

    // 9
    int maxUncrossedLines(vector<int> &nums1, vector<int> &nums2)
    {
        int m = nums1.size(), n = nums2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                if (nums1[i - 1] == nums2[j - 1])
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
            }

        return dp[m][n];
    }
};
