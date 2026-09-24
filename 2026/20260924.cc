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
    int minSubArrayLen(int target, vector<int> &nums)
    {
        int n = nums.size(), ret = INT_MAX, sum = 0;

        for (int left = 0, right = 0, tmp = 0; right < n; right++)
        {
            tmp += nums[right];

            while (tmp >= target)
            {
                ret = min(ret, right - left + 1);
                tmp -= nums[left++];
            }
        }

        return ret == INT_MAX ? 0 : ret;
    }

    // 2
    int jump(vector<int> &nums)
    {
        int n = nums.size(), cur = 0, far = 0, ret = 0;

        for (int i = 0; i < n - 1; i++)
        {
            far = max(far, i + nums[i]);

            if (i == cur)
            {
                cur = far;
                ret++;
            }

            if (cur == n - 1)
                break;
        }

        return ret;
    }

    // 3
    int monotoneIncreasingDigits(int n)
    {
        string s = to_string(n);
        int m = s.size(), i = 0;

        while (i + 1 < m && s[i] <= s[i + 1])
            i++;

        if (i + 1 == m)
            return n;

        while (i - 1 >= 0 && s[i] == s[i - 1])
            i--;

        s[i]--;
        for (int j = i + 1; j < m; j++)
            s[j] = '9';

        return stoi(s);
    }

    // 4
    bool wordBreak(string s, vector<string> &wordDict)
    {
        unordered_set<string> hash(wordDict.begin(), wordDict.end());
        int n = s.size();

        vector<bool> dp(n + 1);
        dp[0] = true;
        s = " " + s;
        for (int i = 1; i <= n; i++)
            for (int j = i; j >= 1; j--)
            {
                if (dp[j - 1] && hash.count(s.substr(j, i - j + 1)))
                {
                    dp[i] = true;
                    break;
                }
            }

        return dp[n];
    }
};

// 5
int main()
{
    string s;
    while (cin >> s)
        ;
    cout << s.size() << endl;

    return 0;
}