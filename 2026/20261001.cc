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
    int subarraySum(vector<int> &nums, int k)
    {
        unordered_map<int, int> hash;
        int ret = 0, sum = 0;
        hash[0] = 1;

        for (auto n : nums)
        {
            sum += n;
            if (hash[sum - k])
                ret += hash[sum - k];
            // else
            hash[sum]++;
        }

        return ret;
    }

    // 2
    TreeNode *pruneTree(TreeNode *root)
    {

        if (root->left)
            root->left = pruneTree(root->left);
        if (root->right)
            root->right = pruneTree(root->right);

        if (root->left == nullptr && root->right == nullptr && root->val == 0)
            return nullptr;

        return root;
    }

    // 3
    vector<int> diStringMatch(string s)
    {
        int n = s.size();
        int left = 0, right = n;
        vector<int> ret;

        for (int i = 0; i <= n; i++)
        {
            if (s[i] == 'I')
                ret.push_back(left++);
            else
                ret.push_back(right--);
        }

        return ret;
    }

    // 4
    int minFallingPathSum(vector<vector<int>> &matrix)
    {
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 2, INT_MAX));

        for (int i = 0; i < n + 2; i++)
            dp[0][i] = 0;

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                dp[i][j] = min(dp[i - 1][j], min(dp[i - 1][j - 1], dp[i - 1][j + 1])) + matrix[i - 1][j - 1];
            }

        int ret = INT_MAX;
        for (int i = 1; i <= n; i++)
            ret = min(ret, dp[m][i]);

        return ret;
    }

    // 5
    bool canPartition(vector<int> &nums)
    {
        int n = nums.size(), sum = 0;
        for (auto num : nums)
            sum += num;

        if (sum % 2)
            return false;

        int aim = sum / 2;
        vector<vector<bool>> dp(n + 1, vector<bool>(aim + 1));

        for (int i = 0; i <= n; i++)
            dp[i][0] = true;

        for (int i = 1; i <= n; i++)
            for (int j = 0; j <= aim; j++)
            {
                dp[i][j] = dp[i - 1][j];
                if (j >= nums[i - 1])
                    dp[i][j] = dp[i][j] || dp[i - 1][j - nums[i - 1]];
            }

        return dp[n][aim];
    }

    // 7
    int MoreThanHalfNum_Solution(vector<int> &numbers)
    {
        int ret = numbers[0], count = 1;

        for (int i = 1; i < numbers.size(); i++)
        {
            if (numbers[i] == ret)
                count++;
            else if (--count == 0)
            {
                ret = numbers[i];
                count = 1;
            }
        }

        return ret;
    }
};

// 6
int main()
{
    string s;
    while (cin >> s)
        ;
    cout << s.size() << endl;
    return 0;
}