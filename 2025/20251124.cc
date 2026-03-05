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
    int wiggleMaxLength(vector<int> &nums)
    {
        int n = nums.size(), left = 0, right = 0, ret = 0;
        for (int i = 0; i < n - 1; i++)
        {
            right = nums[i + 1] - nums[i];
            if (right == 0)
                continue;
            if (left * right <= 0)
                ret++;
            left = right;
        }
        return ret;
    }

    // 2
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    bool vis[16][16];
    bool exist(vector<vector<char>> &board, string word)
    {
        m = board.size(), n = board[0].size();

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (board[i][j] == word[0])
                {
                    vis[i][j] = true;
                    if (dfs(board, i, j, word, 1))
                        return true;
                    vis[i][j] = false;
                }
        return false;
    }

    bool dfs(vector<vector<char>> &board, int i, int j, string &word, int pos)
    {
        if (pos == word.size())
            return true;

        for (int k = 0; k < 4; k++)
        {
            int x = i + dx[k], y = j + dy[k];
            if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && board[x][y] == word[pos])
            {
                vis[x][y] = true;
                if (dfs(board, x, y, word, pos + 1))
                    return true;
                vis[x][y] = false;
            }
        }

        return false;
    }

    // 3
    string largestNumber(vector<int> &nums)
    {
        vector<string> strs;
        for (auto n : nums)
            strs.push_back(to_string(n));

        sort(strs.begin(), strs.end(), [=](const string &s1, const string &s2)
             { return s1 + s2 > s2 + s1; });

        string ret;
        for (auto &str : strs)
            ret += str;

        return ret[0] == '0' ? "0" : ret;
    }

    // 4
    bool validateStackSequences(vector<int> &pushed, vector<int> &popped)
    {
        int n = pushed.size(), i = 0;
        stack<int> st;

        for (auto n : pushed)
        {
            st.push(n);
            while (st.size() && st.top() == popped[i])
            {
                st.pop();
                i++;
            }
        }

        return i == n;
    }

    // 5
    vector<int> smallestK(vector<int> &arr, int k)
    {
        srand(time(nullptr));
        quickSort(arr, 0, arr.size() - 1, k);
        return {arr.begin(), arr.begin() + k};
    }

    int getRandom(vector<int> &nums, int left, int right)
    {
        int r = rand();
        return nums[r % (right - left + 1) + left];
    }

    void quickSort(vector<int> &nums, int l, int r, int k)
    {
        if (l >= r)
            return;

        int key = getRandom(nums, l, r);
        int i = l, left = l - 1, right = r + 1;
        while (i < right)
        {
            if (nums[i] < key)
                swap(nums[i++], nums[++left]);
            else if (nums[i] == key)
                i++;
            else
                swap(nums[i], nums[--right]);
        }

        int lRange = left - l + 1, mRange = (right - 1) - (left + 1) + 1;
        if (lRange >= k)
            quickSort(nums, l, left, k);
        else if (lRange + mRange >= k)
            return;
        else
            quickSort(nums, right, r, k - lRange - mRange);
    }

    // 6
    string longestPalindrome(string s)
    {
        int n = s.size();
        vector<vector<bool>> dp(n, vector<bool>(n));

        for (int i = 0; i < n; i++)
            dp[i][i] = true;

        int begin = 0, maxlen = 1;
        for (int L = 2; L <= n; L++)
        {
            for (int i = 0; i < n; i++)
            {
                int j = i + L - 1;
                if (j > n - 1)
                    break;

                if (s[i] != s[j])
                    dp[i][j] = false;
                else
                {
                    if (L == 2)
                        dp[i][j] = true;
                    else
                        dp[i][j] = dp[i + 1][j - 1];
                }

                if (dp[i][j] && j - i + 1 > maxlen)
                {
                    maxlen = j - i + 1;
                    begin = i;
                }
            }
        }

        return s.substr(begin, maxlen);
    }

    // 7
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    bool vis[16][16];
    int getMaximumGold(vector<vector<int>> &grid)
    {
        m = grid.size(), n = grid[0].size();
        int ret = 0;

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j])
                {
                    vis[i][j] = true;
                    ret = max(ret, grid[i][j] + dfs(grid, i, j));
                    vis[i][j] = false;
                }

        return ret;
    }

    int dfs(vector<vector<int>> &grid, int i, int j)
    {
        int ret = 0;

        for (int k = 0; k < 4; k++)
        {
            int x = i + dx[k], y = j + dy[k];
            if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && grid[x][y])
            {
                vis[x][y] = true;
                ret = max(ret, grid[x][y] + dfs(grid, x, y));
                vis[x][y] = false;
            }
        }

        return ret;
    }
};