#include <mutex>
#include <vector>
#include <algorithm>
#include <climits>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <queue>
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
    int K, N;
    vector<vector<int>> combine(int n, int k)
    {
        K = k;
        N = n;
        dfs(1);
        return ret;
    }

    void dfs(int pos)
    {
        if (path.size() == K)
        {
            ret.push_back(path);
            return;
        }

        for (int i = pos; i <= N; i++)
        {

            path.push_back(i);
            dfs(i + 1);
            path.pop_back();
        }
    }

    // 2
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
        for (int i : index)
            ret.push_back(names[i]);

        return ret;
    }

    // 4
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost)
    {
        int n = gas.size();

        for (int i = 0; i < n; i++)
        {
            int step = 0, rest = 0;
            for (; step < n; step++)
            {
                int index = (i + step) % n;
                rest += gas[index] - cost[index];
                if (rest < 0)
                    break;
            }

            if (rest >= 0)
                return i;

            i = i + step;
        }

        return -1;
    }

    // 5
    int maxProfit(vector<int> &prices, int fee)
    {
        int n = prices.size();
        vector<int> f(n);
        auto g = f;
        f[0] = -prices[0];

        for (int i = 1; i < n; i++)
        {
            f[i] = max(f[i - 1], g[i - 1] - prices[i]);
            g[i] = max(g[i - 1], f[i - 1] + prices[i] - fee);
        }

        return g[n - 1];
    }

    // 6
    int maxProfit(vector<int> &prices)
    {
        const int INF = 0x3f3f3f;
        int n = prices.size();
        vector<vector<int>> f(n, vector<int>(3, -INF));
        auto g = f;

        f[0][0] = -prices[0];
        g[0][0] = 0;

        for (int i = 1; i < n; i++)
            for (int j = 0; j < 3; j++)
            {
                f[i][j] = max(f[i - 1][j], g[i - 1][j] - prices[i]);
                g[i][j] = g[i - 1][j];

                if (j >= 1)
                    g[i][j] = max(g[i][j], f[i - 1][j - 1] + prices[i]);
            }

        int ret = -INF;
        for (int i = 0; i < 3; i++)
            ret = max(ret, g[n - 1][i]);

        return ret;
    }

    // 7
    int longestSubsequence(vector<int> &arr, int difference)
    {
        unordered_map<int, int> hash;
        hash[arr[0]] = 1;
        int ret = 0;

        for (int i = 1; i < arr.size(); i++)
        {
            hash[arr[i]] = max(hash[arr[i]], hash[arr[i] - difference] + 1);
            ret = max(ret, hash[arr[i]]);
        }

        return ret;
    }

    // 8
    int myAtoi(string str)
    {
        int n = str.size(), cur = 0, sign = 1;

        while (str[cur] == ' ')
            if (++cur == n)
                break;

        if (str[cur] == '+' || str[cur] == '-')
        {
            if (str[cur] == '-')
                sign = -1;
            cur++;
        }

        int ret = 0;
        for (int i = cur; i < n; i++)
        {
            if (!isdigit(str[i]))
                break;

            if (ret > (INT_MAX - (str[i] - '0')) / 10)
                return sign == 1 ? INT_MAX : INT_MIN;

            ret = ret * 10 + (str[i] - '0');
        }

        return ret * sign;
    }
};