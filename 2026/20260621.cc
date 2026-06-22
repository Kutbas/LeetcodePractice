#include <mutex>
#include <vector>
#include <algorithm>
#include <climits>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
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
    int m, n;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    bool vis[301][301] = {0};
    int numIslands(vector<vector<char>> &grid)
    {
        m = grid.size(), n = grid[0].size();

        int ret = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j] == '1' && !vis[i][j])
                {
                    ret++;
                    dfs(grid, i, j);
                }

        return ret;
    }

    void dfs(vector<vector<char>> &grid, int i, int j)
    {
        vis[i][j] = true;
        queue<pair<int, int>> q;
        q.push({i, j});

        while (q.size())
        {
            auto [a, b] = q.front();
            q.pop();

            for (int k = 0; k < 4; k++)
            {
                int x = a + dx[k], y = b + dy[k];
                if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && grid[x][y] == '1')
                {
                    vis[x][y] = true;
                    q.push({x, y});
                }
            }
        }
    }

    // 2
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

    // 3
    int maxTurbulenceSize(vector<int> &arr)
    {
        int n = arr.size(), ret = 1;
        vector<int> f(n, 1);
        auto g = f;

        for (int i = 1; i < n; i++)
        {
            if (arr[i] > arr[i - 1])
                f[i] = g[i - 1] + 1;
            else if (arr[i] < arr[i - 1])
                g[i] = f[i - 1] + 1;
            ret = max(ret, max(f[i], g[i]));
        }

        return ret;
    }

    // 4
    bool wordBreak(string s, vector<string> &wordDict)
    {
        unordered_set<string> hash(wordDict.begin(), wordDict.end());
        int n = s.size();

        s = " " + s;
        vector<bool> dp(n + 1);
        dp[0] = true;

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

    // 5
    int massage(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 0)
            return 0;

        vector<int> f(n);
        auto g = f;
        f[0] = nums[0];

        for (int i = 1; i < n; i++)
        {
            f[i] = g[i - 1] + nums[i];
            g[i] = max(f[i - 1], g[i - 1]);
        }

        return max(f[n - 1], g[n - 1]);
    }

    // 6
    bool isInterleave(string s1, string s2, string s3)
    {
        int m = s1.size(), n = s2.size();
        if (m + n != s3.size())
            return false;

        s1 = " " + s1, s2 = " " + s2, s3 = " " + s3;
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1));
        dp[0][0] = true;

        for (int i = 1; i <= m; i++)
            if (s1[i] == s3[i])
                dp[i][0] = true;
            else
                break;

        for (int i = 1; i <= n; i++)
            if (s2[i] == s3[i])
                dp[0][i] = true;
            else
                break;

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                bool case1 = s1[i] == s3[i + j] && dp[i - 1][j];
                bool case2 = s2[j] == s3[i + j] && dp[i][j - 1];
                dp[i][j] = case1 || case2;
            }

        return dp[m][n];
    }

    // 7
    bool isPalindrome(string s)
    {
        string tmp;
        for (char ch : s)
            if (isalnum(ch))
                tmp += tolower(ch);

        int n = tmp.size(), left = 0, right = n - 1;
        while (left < right)
        {
            if (tmp[left] != tmp[right])
                return false;
            left++;
            right--;
        }

        return true;
    }
};

// 8
class MinStack
{
private:
    stack<long> st;
    long minVal;

public:
    MinStack() {}

    void push(int value)
    {
        if (st.empty())
        {
            st.push(0);
            minVal = value;
        }
        else
        {

            long diff = value - minVal;
            if (diff < 0)
                minVal = value;

            st.push(diff);
        }
    }

    void pop()
    {
        long diff = st.top();
        st.pop();

        if (diff < 0)
            minVal = minVal - diff;
    }

    int top()
    {
        long diff = st.top();

        if (diff > 0)
            return minVal + diff;

        return minVal;
    }

    int getMin() { return minVal; }
};