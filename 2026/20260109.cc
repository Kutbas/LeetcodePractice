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
    int maxSumDivThree(vector<int> &nums)
    {
        const int INF = 0x3f3f3f;
        int x1 = INF, x2 = INF;
        int y1 = INF, y2 = INF;

        int sum = 0;
        for (auto n : nums)
        {
            sum += n;

            if (n % 3 == 1)
            {
                if (n < x1)
                    x2 = x1, x1 = n;
                else if (n < x2)
                    x2 = n;
            }
            else if (n % 3 == 2)
            {
                if (n < y1)
                    y2 = y1, y1 = n;
                else if (n < y2)
                    y2 = n;
            }
        }

        if (sum % 3 == 0)
            return sum;
        else if (sum % 3 == 1)
            return max(sum - x1, sum - y1 - y2);
        else
            return max(sum - y1, sum - x1 - x2);
    }

    // 2
    int ladderLength(string beginWord, string endWord, vector<string> &wordList)
    {
        if (beginWord == endWord)
            return 0;
        unordered_set<string> hash(wordList.begin(), wordList.end());
        unordered_set<string> vis;
        if (!hash.count(endWord))
            return 0;

        int ret = 1;
        queue<string> q;
        q.push(beginWord);
        vis.insert(beginWord);
        while (q.size())
        {
            ret++;
            int sz = q.size();
            while (sz--)
            {
                auto t = q.front();
                q.pop();
                for (int i = 0; i < t.size(); i++)
                {
                    string tmp = t;
                    for (char ch = 'a'; ch <= 'z'; ch++)
                    {
                        tmp[i] = ch;
                        if (hash.count(tmp) && !vis.count(tmp))
                        {
                            if (tmp == endWord)
                                return ret;
                            q.push(tmp);
                            vis.insert(tmp);
                        }
                    }
                }
            }
        }

        return 0;
    }

    // 3
    int m, n;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    bool vis[16][16] = {0};
    bool exist(vector<vector<char>> &board, string word)
    {
        m = board.size(), n = board[0].size();

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (board[i][j] == word[0])
                {
                    vis[i][j] = true;
                    if (dfs(board, word, i, j, 1))
                        return true;
                    vis[i][j] = false;
                }

        return false;
    }

    bool dfs(vector<vector<char>> &board, string &word, int i, int j, int pos)
    {
        if (pos == word.size())
            return true;

        for (int k = 0; k < 4; k++)
        {
            int x = i + dx[k], y = j + dy[k];
            if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && board[x][y] == word[pos])
            {
                vis[x][y] = true;
                if (dfs(board, word, x, y, pos + 1))
                    return true;
                vis[x][y] = false;
            }
        }

        return false;
    }

    // 4
    int lastStoneWeightII(vector<int> &stones)
    {
        int n = stones.size(), sum = 0;
        for (auto n : stones)
            sum += n;
        int m = sum / 2;

        vector<vector<int>> dp(n + 1, vector<int>(m + 1));
        for (int i = 1; i <= n; i++)
            for (int j = 0; j <= m; j++)
            {
                dp[i][j] = dp[i - 1][j];

                if (j >= stones[i - 1])
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - stones[i - 1]] + stones[i - 1]);
            }

        return sum - 2 * dp[n][m];
    }

    // 5
    int maxProfit(vector<int> &prices)
    {
        int n = prices.size(), ret = 0;

        for (int i = 0; i < n; i++)
        {
            int j = i;
            while (j + 1 < n && prices[j + 1] > prices[j])
                j++;
            ret += prices[j] - prices[i];
            i = j;
        }
        return ret;
    }

    // 6
    int MoreThanHalfNum_Solution(vector<int> &numbers)
    {
        int n = numbers.size();
        unordered_map<int, int> hash;
        for (auto n : numbers)
            if (++hash[n] > n / 2)
                return n;
        return -1;
    }
};