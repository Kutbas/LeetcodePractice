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
    int numSquares(int n)
    {
        int m = sqrt(n);
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));

        for (int i = 1; i <= n; i++)
            dp[0][i] = INT_MAX;

        for (int i = 1; i <= m; i++)
            for (int j = 0; j <= n; j++)
            {
                dp[i][j] = dp[i - 1][j];
                if (i * i <= j)
                    dp[i][j] = min(dp[i][j], dp[i][j - i * i] + 1);
            }

        return dp[m][n];
    }

    // 3
};

// 2
int main()
{
    string s;
    while (cin >> s)
        ;
    cout << s.size() << endl;

    return 0;
}