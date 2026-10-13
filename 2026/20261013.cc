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
#include <set>
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
    vector<vector<int>> ret;
    vector<int> path;
    int aim;
    vector<vector<int>> combinationSum(vector<int> &candidates, int target)
    {
        aim = target;
        dfs(candidates, 0, 0);
        return ret;
    }

    void dfs(vector<int> &nums, int pos, int sum)
    {
        if (sum > aim)
            return;

        if (sum == aim)
        {
            ret.push_back(path);
            return;
        }

        for (int i = pos; i < nums.size(); i++)
        {
            path.push_back(nums[i]);
            dfs(nums, i, sum + nums[i]);
            path.pop_back();
        }
    }

    // 2
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

    // 3
    int findLength(vector<int> &nums1, vector<int> &nums2)
    {
        int m = nums1.size(), n = nums2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));

        int ret = 0;
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                if (nums1[i - 1] == nums2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                // else
                // dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
                ret = max(ret, dp[i][j]);
            }

        return ret;
    }

    // 4
    bool isPalindrome(string s)
    {
        string tmp;
        for (char ch : s)
            if (isalnum(ch))
                tmp += tolower(ch);

        int left = 0, right = tmp.size() - 1;
        while (left < right)
            if (tmp[left] != tmp[right])
                return false;
            else
                left++, right--;

        return true;
    }

    // 5
    vector<string> uncommonFromSentences(string s1, string s2)
    {
        unordered_map<string, int> hash;

        auto countWord = [&](const string s)
        {
            string word;
            istringstream iss(s);

            while (iss >> word)
                hash[word]++;
        };

        countWord(s1);
        countWord(s2);

        vector<string> ret;
        for (auto [a, b] : hash)
            if (b == 1)
                ret.push_back(a);

        return ret;
    }
};