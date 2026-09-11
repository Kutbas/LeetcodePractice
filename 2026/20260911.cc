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
    int missingNumber(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        int n = nums.size();

        int left = 0, right = n - 1;
        while (left < right)
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] == mid)
                left = mid + 1;
            else
                right = mid;
        }

        return nums[left] < left + 1 ? left + 1 : left;
    }

    // 2
    int m, n;
    vector<vector<int>> matrixBlockSum(vector<vector<int>> &mat, int k)
    {
        m = mat.size(), n = mat[0].size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1] + mat[i - 1][j - 1] - dp[i - 1][j - 1];
            }

        vector<vector<int>> ret(m, vector<int>(n));

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                int x1 = max(0, i - k) + 1, y1 = max(0, j - k) + 1;
                int x2 = min(m - 1, i + k) + 1, y2 = min(n - 1, j + k) + 1;
                ret[i][j] = dp[x2][y2] - dp[x1 - 1][y2] - dp[x2][y1 - 1] + dp[x1 - 1][y1 - 1];
            }

        return ret;
    }

    // 3
    string modifyString(string s)
    {
        int n = s.size();

        for (int i = 0; i < n; i++)
        {
            if (s[i] == '?')
            {
                for (char ch = 'a'; ch <= 'z'; ch++)
                {
                    // i==0 s[i+1]!=ch
                    // i==n-1 s[i-1]!=ch
                    if ((i == 0 && s[i + 1] != ch) || (s[i + 1] != ch && s[i - 1] != ch) || (i == n - 1 && s[i - 1] != ch))
                        s[i] = ch;
                }
            }
        }

        return s;
    }

    // 4
    ListNode *swapPairs(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *newhead = swapPairs(head->next->next);
        ListNode *ret = head->next;
        ret->next = head;
        head->next = newhead;

        return ret;
    }

    // 5
    int memo[201][201] = {0};
    int getMoneyAmount(int n)
    {
        return dfs(1, n);
    }

    int dfs(int left, int right)
    {
        if (left >= right)
            return 0;

        if (memo[left][right])
            return memo[left][right];

        int ret = INT_MAX;
        for (int head = left; head <= right; head++)
        {
            int tmp1 = dfs(left, head - 1);
            int tmp2 = dfs(head + 1, right);

            ret = min(ret, max(tmp1, tmp2) + head);
        }

        memo[left][right] = ret;

        return ret;
    }

    // 6
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

    // 7
    int eraseOverlapIntervals(vector<vector<int>> &intervals)
    {
        sort(intervals.begin(), intervals.end());
        int n = intervals.size(), right = intervals[0][1], ret = 0;

        for (int i = 1; i < n; i++)
        {
            int a = intervals[i][0], b = intervals[i][1];
            if (a < right)
            {
                ret++;
                right = min(right, b);
            }
            else
                right = b;
        }

        return ret;
    }

    // 8
    string ret;
    string tree2str(TreeNode *root)
    {
        dfs(root);
        return ret;
    }

    void dfs(TreeNode *root)
    {
        if (root == nullptr)
            return;

        ret += to_string(root->val);

        if (root->left || root->right)
        {
            ret += '(';
            dfs(root->left);
            ret += ')';
        }

        if (root->right)
        {
            ret += '(';
            dfs(root->right);
            ret += ')';
        }
    }
};