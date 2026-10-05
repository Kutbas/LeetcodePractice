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
#include <sstream>
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
    int getSum(int a, int b)
    {

        while (b)
        {
            int x = a ^ b;
            int carry = (a & b) << 1;
            a = x;
            b = carry;
        }

        return a;
    }

    // 2
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        int t = 0;

        ListNode *ret = new ListNode(0);
        ListNode *prev = ret;
        ListNode *cur1 = l1, *cur2 = l2;

        while (cur1 || cur2 || t)
        {
            if (cur1)
            {
                t += cur1->val;
                cur1 = cur1->next;
            }
            if (cur2)
            {
                t += cur2->val;
                cur2 = cur2->next;
            }

            prev->next = new ListNode(t % 10);
            t /= 10;

            prev = prev->next;
        }

        prev = ret->next;
        delete ret;
        return prev;
    }

    // 3
    int m, n;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    vector<vector<int>> highestPeak(vector<vector<int>> &isWater)
    {
        m = isWater.size(), n = isWater[0].size();
        vector<vector<int>> dist(m, vector<int>(n, -1));

        queue<pair<int, int>> q;

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (isWater[i][j] == 1)
                {
                    dist[i][j] = 0;
                    q.push({i, j});
                }
            }

        while (q.size())
        {
            int sz = q.size();
            while (sz--)
            {
                auto [a, b] = q.front();
                q.pop();

                for (int k = 0; k < 4; k++)
                {
                    int x = a + dx[k], y = b + dy[k];
                    if (x >= 0 && x < m && y >= 0 && y < n && dist[x][y] == -1)
                    {
                        dist[x][y] = dist[a][b] + 1;
                        q.push({x, y});
                    }
                }
            }
        }

        return dist;
    }

    // 4
    bool lemonadeChange(vector<int> &bills)
    {
        int hash[21] = {0};

        for (auto n : bills)
        {
            if (n == 5)
                hash[5]++;
            else if (n == 10)
            {
                if (!hash[5])
                    return false;
                hash[5]--, hash[10]++;
            }
            else if (n == 20)
            {
                if (hash[5] && hash[10])
                    hash[5]--, hash[10]--;
                else if (hash[5] >= 3)
                    hash[5] -= 3;
                else
                    return false;
            }
        }

        return true;
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

    // 6
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
            else
            {
                if (n == 3)
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
        }

        return ret;
    }

    // 7
    vector<int> rearrangeBarcodes(vector<int> &barcodes)
    {
        int n = barcodes.size(), maxVal = 0, maxCount = 0;
        unordered_map<int, int> hash;

        for (auto num : barcodes)
        {
            if (++hash[num] > maxCount)
            {
                maxCount = hash[num];
                maxVal = num;
            }
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
                if (index > n - 1)
                    index = 1;

                ret[index] = a;
                index += 2;
            }

        return ret;
    }

    // 8
    bool isMatch(string s, string p)
    {
        int m = s.size(), n = p.size();
        s = " " + s, p = " " + p;

        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1));
        dp[0][0] = true;
        for (int i = 1; i <= n; i++)
            if (p[i] == '*')
                dp[0][i] = true;
            else
                break;

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                if (p[j] == '*')
                {
                    dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
                }
                else
                    dp[i][j] = (p[j] == '?' || p[j] == s[i]) && dp[i - 1][j - 1];
            }

        return dp[m][n];
    }

    // 9
    string reorganizeString(string s)
    {
        int n = s.size(), maxCount = 0;
        char maxChar;
        unordered_map<char, int> hash;
        for (auto ch : s)
        {
            if (++hash[ch] > maxCount)
            {
                maxCount = hash[ch];
                maxChar = ch;
            }
        }

        string ret;
        ret.append(n, ' ');
        int index = 0;
        for (int i = 0; i < maxCount; i++)
        {
            if (index > n - 1)
                break;
            ret[index] = maxChar;
            index += 2;
        }

        hash.erase(maxChar);
        for (auto [a, b] : hash)
            for (int i = 0; i < b; i++)
            {
                if (index > n - 1)
                    index = 1;

                ret[index] = a;
                index += 2;
            }

        for (char ch : ret)
            if (ch == ' ')
                return "";
        return ret;
    }
};