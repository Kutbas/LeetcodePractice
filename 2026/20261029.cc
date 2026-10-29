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
    typedef pair<TreeNode *, unsigned int> PTL;
    int widthOfBinaryTree(TreeNode *root)
    {
        vector<PTL> q;
        q.push_back({root, 1});

        unsigned int ret = 1;
        while (q.size())
        {
            vector<PTL> tmp;
            auto &[x1, y1] = q[0];
            auto &[x2, y2] = q.back();
            ret = max(ret, y2 - y1 + 1);

            for (auto &[x, y] : q)
            {
                if (x->left)
                    tmp.push_back({x->left, 2 * y});
                if (x->right)
                    tmp.push_back({x->right, 2 * y + 1});
            }

            q = tmp;
        }

        return ret;
    }

    // 2
    class Singleton
    {
    public:
        static Singleton &getInstance()
        {
            static Singleton instanche;
            return instanche;
        }

        Singleton(const Singleton &) = delete;
        Singleton &operator=(const Singleton &) = delete;

        void doSomething()
        {
            cout << "check" << endl;
        }

    private:
        Singleton() = default;
        ~Singleton() = default;
    };

    // 3
    int longestSubsequence(vector<int> &arr, int difference)
    {
        int n = arr.size(), ret = 1;
        unordered_map<int, int> hash;
        hash[arr[0]] = 1;

        for (int i = 1; i < n; i++)
        {
            hash[arr[i]] = hash[arr[i] - difference] + 1;
            ret = max(ret, hash[arr[i]]);
        }

        return ret;
    }

    // 4
    int lenLongestFibSubseq(vector<int> &arr)
    {
        int n = arr.size();
        unordered_map<int, int> hash;
        for (int i = 0; i < n; i++)
            hash[arr[i]] = i;

        vector<vector<int>> dp(n, vector<int>(n, 2));
        int ret = 2;

        for (int j = 2; j < n; j++)
            for (int i = 1; i < j; i++)
            {
                int a = arr[j] - arr[i];
                if (a < arr[i] && hash.count(a))
                    dp[i][j] = dp[hash[a]][i] + 1;
                ret = max(ret, dp[i][j]);
            }

        return ret < 3 ? 0 : ret;
    }

    // 5
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

    // 6
    vector<int> intersect(vector<int> &nums1, vector<int> &nums2)
    {
        unordered_map<int, int> hash;
        for (auto n : nums1)
            hash[n]++;

        vector<int> ret;
        for (auto n : nums2)
            if (hash[n]-- > 0)
                ret.push_back(n);

        return ret;
    }

    // 7
    string reverseStr(string s, int k)
    {
        int n = s.size();
        for (int i = 0; i < n; i += 2 * k)
        {
            int right = min(i + k, n);
            reverse(s.begin() + i, s.begin() + right);
        }

        return s;
    }

    // 8
};