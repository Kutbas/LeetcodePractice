#include <bits/stdc++.h>
#include <mutex>
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
    int largestSumAfterKNegations(vector<int> &nums, int k)
    {
        int n = nums.size(), minElem = INT_MAX, count = 0;

        for (auto n : nums)
        {
            if (n < 0)
                count++;
            minElem = min(minElem, abs(n));
        }

        int ret = 0;
        if (count > k)
        {
            sort(nums.begin(), nums.end());
            for (int i = 0; i < k; i++)
                ret += -nums[i];

            for (int i = k; i < n; i++)
                ret += nums[i];
        }
        else
        {
            for (auto n : nums)
                ret += abs(n);

            if ((k - count) % 2 == 1)
                ret -= 2 * minElem;
        }

        return ret;
    }

    // 4
    int lastStoneWeightII(vector<int> &stones)
    {
        int n = stones.size(), sum = 0;
        for (auto num : stones)
            sum += num;
        int m = sum / 2;

        vector<vector<int>> dp(n + 1, vector<int>(m + 1));
        for (int i = 1; i <= n; i++)
            for (int j = 0; j <= m; j++)
            {
                dp[i][j] = dp[i - 1][j];

                if (j >= stones[i - 1])
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - stones[i - 1]] +
                                                 stones[i - 1]);
            }

        return sum - 2 * dp[n][m];
    }

    // 5
    int minCut(string s)
    {
        int n = s.size();
        vector<vector<int>> isPal(n, vector<int>(n));

        for (int i = n - 1; i >= 0; i--)
            for (int j = i; j < n; j++)
                if (s[i] == s[j])
                    isPal[i][j] = j - i > 1 ? isPal[i + 1][j - 1] : true;

        vector<int> dp(n, INT_MAX);
        for (int i = 0; i < n; i++)
        {
            if (isPal[0][i])
                dp[i] = 0;
            else
            {
                for (int j = 1; j <= i; j++)
                    if (isPal[j][i])
                        dp[i] = min(dp[i], dp[j - 1] + 1);
            }
        }

        return dp[n - 1];
    }
};

// 2
int main()
{
    string s;
    cin >> s;

    int n = s.size();
    int hash[128] = {0};
    for (char ch : s)
        hash[ch]++;

    for (char ch : s)
        if (hash[ch] == 1)
        {
            cout << ch << endl;
            return 0;
        }

    cout << -1 << endl;
    return 0;
}

// 3
int main()
{
    int n, m, q;
    cin >> n >> m >> q;

    vector<vector<int>> nums(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> nums[i][j];

    vector<vector<long long>> dp(n + 1, vector<long long>(m + 1));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1] + nums[i][j];

    int x1, y1, x2, y2;
    while (q--)
    {
        cin >> x1 >> y1 >> x2 >> y2;
        cout << dp[x2][y2] - dp[x1 - 1][y2] - dp[x2][y1 - 1] + dp[x1 - 1][y1 - 1] << endl;
    }

    return 0;
}