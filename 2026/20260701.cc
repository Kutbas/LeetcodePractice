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

// 1
class MedianFinder
{
private:
    priority_queue<int> left;
    priority_queue<int, vector<int>, greater<int>> right;

public:
    MedianFinder()
    {
    }

    void addNum(int num)
    {
        if (left.size() == right.size())
        {
            if (left.empty() || num < left.top())
                left.push(num);
            else
            {
                right.push(num);
                left.push(right.top());
                right.pop();
            }
        }
        else
        {
            if (num >= left.top())
                right.push(num);
            else
            {
                left.push(num);
                right.push(left.top());
                left.pop();
            }
        }
    }

    double findMedian()
    {
        return left.size() == right.size() ? (left.top() + right.top()) / 2.0 : left.top();
    }
};

// 2
int main()
{
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<int>> arr(n + 1, vector<int>(m + 1));

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> arr[i][j];

    vector<vector<long long>> dp(n + 1, vector<long long>(m + 1));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1] + arr[i][j];

    int x1, y1, x2, y2;
    while (q--)
    {
        cin >> x1 >> y1 >> x2 >> y2;
        cout << dp[x2][y2] - dp[x1 - 1][y2] - dp[x2][y1 - 1] + dp[x1 - 1][y1 - 1] << endl;
    }

    return 0;
}

class Solution
{
public:
    // 3
    int ret = 0, N;
    bool vis[16] = {0};
    int countArrangement(int n)
    {
        N = n;
        dfs(1);
        return ret;
    }

    void dfs(int pos)
    {
        if (pos == N + 1)
        {
            ret++;
            return;
        }

        for (int i = 1; i <= N; i++)
        {
            if (!vis[i] && (i % pos == 0 || pos % i == 0))
            {
                vis[i] = true;
                dfs(pos + 1);
                vis[i] = false;
            }
        }
    }

    // 4
    int findLengthOfLCIS(vector<int> &nums)
    {
        int n = nums.size(), ret = 1;

        for (int left = 0, right = 0; right < n; right++)
        {
            while (right + 1 < n && nums[right + 1] > nums[right])
                right++;
            ret = max(ret, right - left + 1);
            left = right + 1;
        }

        return ret;
    }

    // 5
    vector<int> rearrangeBarcodes(vector<int> &barcodes)
    {
        unordered_map<int, int> hash;
        int maxVal = 0, maxCount = 0;

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
        for (auto &[a, b] : hash)
            for (int i = 0; i < b; i++)
            {
                if (index >= n)
                    index = 1;

                ret[index] = a;
                index += 2;
            }

        return ret;
    }

    // 6
    int countSubstrings(string s)
    {
        int n = s.size(), ret = 0;
        vector<vector<bool>> dp(n, vector<bool>(n));

        for (int i = n - 1; i >= 0; i--)
            for (int j = i; j < n; j++)
            {
                if (s[i] == s[j])
                    dp[i][j] = j - i + 1 > 3 ? dp[i + 1][j - 1] : true;

                if (dp[i][j])
                    ret++;
            }

        return ret;
    }

    // 7
    int maxUncrossedLines(vector<int> &nums1, vector<int> &nums2)
    {
        int m = nums1.size(), n = nums2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                if (nums1[i - 1] == nums2[j - 1])
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }

        return dp[m][n];
    }

    // 8
    int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid)
    {
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();

        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        dp[0][1] = 1;

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                if (obstacleGrid[i - 1][j - 1] == 0)
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }

        return dp[m][n];
    }

    // 9
    int maxTurbulenceSize(vector<int> &arr)
    {
        int n = arr.size(), ret = 1;
        vector<int> f(n, 1), g(n, 1);

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
};