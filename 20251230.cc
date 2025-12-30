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
    // 2
    int numDecodings(string s)
    {
        int n = s.size();
        vector<int> dp(n);

        dp[0] = s[0] == '0' ? 0 : 1;
        if (n == 1)
            return dp[0];

        if (s[0] != '0' && s[1] != '0')
            dp[1] += 1;

        int twoDigits = (s[0] - '0') * 10 + (s[1] - '0');
        if (twoDigits >= 10 && twoDigits <= 26)
            dp[1] += 1;

        for (int i = 2; i < n; i++)
        {
            if (s[i] != '0')
                dp[i] += dp[i - 1];

            int twoDigits = (s[i - 1] - '0') * 10 + (s[i] - '0');
            if (twoDigits >= 10 && twoDigits <= 26)
                dp[i] += dp[i - 2];
        }

        return dp[n - 1];
    }

    // 3
    class KthLargest
    {
    public:
        KthLargest(int k, vector<int> &nums)
            : _k(k)
        {
            for (auto n : nums)
            {
                q.push(n);
                if (q.size() > _k)
                    q.pop();
            }
        }

        int add(int val)
        {
            q.push(val);
            if (q.size() > _k)
                q.pop();
            return q.top();
        }

    private:
        int _k;
        priority_queue<int, vector<int>, greater<int>> q;
    };

    // 4
    int removeDuplicates(vector<int> &nums)
    {
        int n = nums.size(), slow = 1, fast = 1;
        while (fast < n)
        {
            if (nums[fast] != nums[fast - 1])
                nums[slow++] = nums[fast];

            fast++;
        }
        return slow;
    }

    // 5
    int findSubstringInWraproundString(string s)
    {
        int n = s.size();
        vector<int> dp(n, 1);

        for (int i = 1; i < n; i++)
            if (s[i - 1] + 1 == s[i] || (s[i - 1] == 'z' && s[i] == 'a'))
                dp[i] += dp[i - 1];

        int hash[26] = {0};
        for (int i = 0; i < n; i++)
        {
            int index = s[i] - 'a';
            hash[index] = max(hash[index], dp[i]);
        }

        int sum = 0;
        for (int i = 0; i < 26; i++)
            sum += hash[i];

        return sum;
    }

    // 6
    int tribonacci(int n)
    {
        if (n == 0)
            return 0;

        if (n == 1 || n == 2)
            return 1;

        int a = 0, b = 1, c = 1, d = 0;
        for (int i = 3; i <= n; i++)
        {
            d = a + b + c;
            a = b;
            b = c;
            c = d;
        }

        return d;
    }

    // 7
    int wiggleMaxLength(vector<int> &nums)
    {
        int n = nums.size(), ret = 0, left = 0, right = 0;

        for (int i = 1; i < n; i++)
        {
            right = nums[i] - nums[i - 1];
            if (right >= 0)
                continue;
            if (left * right <= 0)
                ret++;

            left = right;
        }

        return ret + 1;
    }
};

// 1
const int N = 1010;
int n, v;
int V[N], W[N];
int dp[N][N];

int main()
{
    cin >> n >> v;
    for (int i = 1; i <= n; i++)
        cin >> V[i] >> W[i];

    memset(dp, 0, sizeof dp);
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= v; j++)
        {
            dp[i][j] = dp[i - 1][j];

            if (j >= V[i])
                dp[i][j] = max(dp[i][j], dp[i][j - V[i]] + W[i]);
        }
    cout << dp[n][v] << endl;

    memset(dp, 0, sizeof dp);
    for (int i = 1; i <= v; i++)
        dp[0][i] = -1;

    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= v; j++)
        {
            dp[i][j] = dp[i - 1][j];

            if (j >= V[i] && dp[i][j - V[i]] != -1)
                dp[i][j] = max(dp[i][j], dp[i][j - V[i]] + W[i]);
        }

    cout << (dp[n][v] == -1 ? 0 : dp[n][v]) << endl;

    return 0;
}