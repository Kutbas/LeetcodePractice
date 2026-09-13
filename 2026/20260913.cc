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
    ListNode *swapPairs(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *ret = new ListNode(0);
        ListNode *prev = ret, *cur = head, *next = cur->next,
                 *nnext = next->next;

        while (cur && next)
        {
            prev->next = next;
            next->next = cur;
            cur->next = nnext;

            prev = cur;
            cur = nnext;

            if (cur)
                next = cur->next;
            if (next)
                nnext = next->next;
        }

        prev = ret->next;
        delete ret;
        return prev;
    }

    // 3
    string decodeString(string s)
    {
        stack<int> nums;
        int num = 0;
        stack<string> st;
        string ret;

        for (char ch : s)
        {
            if (isdigit(ch))
                num = num * 10 + (ch - '0');
            else if (ch == '[')
            {
                st.push(ret);
                ret = "";
                nums.push(num);
                num = 0;
            }
            else if (ch == ']')
            {
                int k = nums.top();
                nums.pop();
                string tmp = st.top();
                st.pop();
                while (k--)
                    tmp += ret;
                ret = tmp;
            }
            else
                ret += ch;
        }

        return ret;
    }

    // 4
    bool lemonadeChange(vector<int> &bills)
    {
        int hash[20] = {0};

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
            else
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
    string optimalDivision(vector<int> &nums)
    {
        int n = nums.size();

        if (n == 1)
            return to_string(nums[0]);
        if (n == 2)
            return to_string(nums[0]) + '/' + to_string(nums[1]);

        string ret = to_string(nums[0]) + "/(" + to_string(nums[1]);

        for (int i = 2; i < n; i++)
            ret += '/' + to_string(nums[i]);
        ret += ")";

        return ret;
    }

    // 6
    int numberOfArithmeticSlices(vector<int> &nums)
    {
        int n = nums.size(), prev = 0, sum = 0;
        if (n < 3)
            return 0;

        for (int i = 2; i < n; i++)
        {
            // 2-1 1-0
            if (nums[i] - nums[i - 1] == nums[i - 1] - nums[i - 2])
            {
                prev += 1;
                sum += prev;
            }
            else
                prev = 0;
        }

        return sum;
    }

    // 7
    int coinChange(vector<int> &coins, int amount)
    {
        const int INF = 0x3f3f3f;
        int n = coins.size();
        vector<vector<int>> dp(n + 1, vector<int>(amount + 1));

        for (int i = 1; i <= amount; i++)
            dp[0][i] = INF;

        for (int i = 1; i <= n; i++)
            for (int j = 0; j <= amount; j++)
            {
                dp[i][j] = dp[i - 1][j];
                if (j >= coins[i - 1])
                    dp[i][j] = min(dp[i][j], dp[i][j - coins[i - 1]] + 1);
            }

        return dp[n][amount] == INF ? -1 : dp[n][amount];
    }

    // 8
    bool GetPath(TreeNode *root, TreeNode *x, stack<TreeNode *> &path)
    {
        if (root == nullptr)
            return false;

        path.push(root);

        if (root == x)
            return true;

        if (GetPath(root->left, x, path))
            return true;
        if (GetPath(root->right, x, path))
            return true;

        path.pop();
        return false;
    }

    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        stack<TreeNode *> qPath, pPath;

        GetPath(root, p, pPath);
        GetPath(root, q, qPath);

        while (qPath.size() != pPath.size())
        {
            if (qPath.size() > pPath.size())
                qPath.pop();
            else
                pPath.pop();
        }

        while (qPath.top() != pPath.top())
            qPath.pop(), pPath.pop();

        return qPath.top();
    }
};