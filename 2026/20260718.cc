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
#include <regex>
#include <map>
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
    ListNode *reverseKGroup(ListNode *head, int k)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        int count = 0;
        ListNode *cur = head;
        while (cur)
        {
            cur = cur->next;
            count++;
        }

        ListNode *ret = new ListNode(0);
        ListNode *prev = ret;
        count /= k;
        cur = head;
        // ListNode* next=cur->next;

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

    // 2
    vector<vector<string>> ret;
    vector<string> path;
    int N;
    bool Col[10], Dig1[20], Dig2[20];
    vector<vector<string>> solveNQueens(int n)
    {
        N = n;
        path.resize(n);
        for (int i = 0; i < n; i++)
            path[i].append(n, '.');

        dfs(0);

        return ret;
    }

    void dfs(int row)
    {
        if (row == N)
        {
            ret.push_back(path);
            return;
        }

        for (int col = 0; col < N; col++)
        {
            if (!Col[col] && !Dig1[row + col] && !Dig2[row - col + N])
            {
                path[row][col] = 'Q';
                Col[col] = Dig1[row + col] = Dig2[row - col + N] = true;
                dfs(row + 1);
                Col[col] = Dig1[row + col] = Dig2[row - col + N] = false;
                path[row][col] = '.';
            }
        }
    }

    // 3
    vector<string> sortPeople(vector<string> &names, vector<int> &heights)
    {
        int n = names.size();
        vector<int> index(n);

        for (int i = 0; i < n; i++)
            index[i] = i;

        sort(index.begin(), index.end(), [&](const int i, const int j)
             { return heights[i] > heights[j]; });

        vector<string> ret;
        for (auto i : index)
            ret.push_back(names[i]);

        return ret;
    }

    // 4
    int longestPalindrome(string s)
    {
        int hash[128] = {0};
        for (char ch : s)
            hash[ch]++;

        int ret = 0;
        for (auto n : hash)
            ret += n / 2 * 2;

        return ret < s.size() ? ret + 1 : ret;
    }

    // 5
    int integerReplacement(int n)
    {
        int ret = 0;

        while (n != 1)
        {
            if (n % 2 == 0)
            {
                n /= 2;
                ret++;
            }
            else if (n == 3)
            {
                n = 1;
                ret += 2;
            }
            else if (n % 4 == 1)
            {
                n /= 2;
                ret += 2;
            }
            else
            {
                n = n / 2 + 1;
                ret += 2;
            }
        }

        return ret;
    }

    // 6
    vector<int> rearrangeBarcodes(vector<int> &barcodes)
    {
        unordered_map<int, int> hash;
        int maxCount = 0, maxVal = 0;

        for (auto n : barcodes)
            if (++hash[n] > maxCount)
            {
                maxCount = hash[n];
                maxVal = n;
            }

        int n = barcodes.size(), index = 0;
        vector<int> ret(n);
        for (int i = 0; i < maxCount; i++)
        {
            ret[index] = maxVal;
            index += 2;
        }

        hash.erase(maxVal);
        for (auto &[x, y] : hash)
            for (int i = 0; i < y; i++)
            {
                if (index >= n)
                    index = 1;

                ret[index] = x;
                index += 2;
            }

        return ret;
    }

    // 7
    vector<vector<int>> merge(vector<vector<int>> &intervals)
    {
        sort(intervals.begin(), intervals.end());

        int n = intervals.size(), left = intervals[0][0], right = intervals[0][1];
        vector<vector<int>> ret;

        for (int i = 1; i < n; i++)
        {
            int a = intervals[i][0], b = intervals[i][1];
            if (a <= right)
                right = max(right, b);
            else
            {
                ret.push_back({left, right});
                left = a, right = b;
            }
        }

        ret.push_back({left, right});

        return ret;
    }

    // 8
    vector<int> advantageCount(vector<int> &nums1, vector<int> &nums2)
    {
        sort(nums1.begin(), nums1.end());
        int n = nums1.size();
        vector<int> index(n);
        for (int i = 0; i < n; i++)
            index[i] = i;

        sort(index.begin(), index.end(), [&](const int i, const int j)
             { return nums2[i] < nums2[j]; });

        vector<int> ret(n);
        int left = 0, right = n - 1;
        for (auto n : nums1)
        {
            if (n > nums2[index[left]])
                ret[index[left++]] = n;
            else
                ret[index[right--]] = n;
        }

        return ret;
    }

    // 9
    int findSubstringInWraproundString(string s)
    {
        int n = s.size();

        vector<int> dp(n, 1);
        for (int i = 1; i < n; i++)
            if (s[i - 1] + 1 == s[i] || (s[i - 1] == 'z' && s[i] == 'a'))
                dp[i] += dp[i - 1];

        int hash[26] = {0};
        for (int i = 0; i < n; i++)
        {
            int index = s[i] - 'a';
            hash[index] = max(hash[index], dp[i]);
        }

        int ret = 0;
        for (auto n : hash)
            ret += n;

        return ret;
    }
};