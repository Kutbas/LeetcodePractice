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
    bool evaluateTree(TreeNode *root)
    {
        if (root->left == nullptr && root->right == nullptr)
            return root->val;

        bool left = evaluateTree(root->left);
        bool right = evaluateTree(root->right);

        return root->val == 2 ? left | right : left & right;
    }

    // 2
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

    // 3
    class MyQueue
    {
    private:
        stack<int> in, out;

        void in2out()
        {
            while (in.size())
            {
                out.push(in.top());
                in.pop();
            }
        }

    public:
        MyQueue() {}

        void push(int x) { in.push(x); }

        int pop()
        {
            if (out.empty())
                in2out();

            int r = out.top();
            out.pop();

            return r;
        }

        int peek()
        {
            if (out.empty())
                in2out();
            int r = out.top();
            return r;
        }

        bool empty() { return in.empty() && out.empty(); }
    };

    // 4
    class MinStack
    {
    private:
        stack<long> st;
        long minElem;

    public:
        MinStack()
        {
        }

        void push(int value)
        {
            if (st.empty())
            {
                minElem = value;
                st.push(0);
            }
            else
            {
                long diff = value - minElem;

                if (diff < 0)
                    minElem = value;

                st.push(diff);
            }
        }

        void pop()
        {
            long diff = st.top();
            st.pop();

            if (diff < 0)
                minElem = minElem - diff;
        }

        int top()
        {
            long diff = st.top();

            if (diff > 0)
                return minElem + diff;

            return minElem;
        }

        int getMin()
        {
            return minElem;
        }
    };

    // 5
    int numberOfArithmeticSlices(vector<int> &nums)
    {
        int n = nums.size();
        if (n < 3)
            return 0;

        int prev = 0, sum = 0;
        for (int i = 2; i < n; i++)
        {
            if (nums[i] - nums[i - 1] == nums[i - 1] - nums[i - 2])
            {
                prev += 1;
                sum += prev;
            }
            else
            {
                prev = 0;
            }
        }

        return sum;
    }
};