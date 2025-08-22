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
    unordered_map<int, int> hash;
    int integerReplacement(int n)
    {
        int ret = 0;
        while (n > 1)
        {
            if (n % 2 == 0)
            {
                n /= 2;
                ret++;
            }
            else
            {
                if (n == 3)
                {
                    ret += 2;
                    n = 1;
                }
                else if (n % 4 == 1)
                {
                    n /= 2;
                    ret += 2;
                }
                else
                {
                    n /= 2 + 1;
                    ret += 2;
                }
            }
        }

        return ret;
    }

    // 1
    int memo[201][201];
    int getMoneyAmount(int n)
    {
        return dfs(1, n);
    }

    int dfs(int left, int right)
    {
        if (memo[left][right])
            return memo[left][right];

        if (left >= right)
            return 0;

        int ret = INT_MAX;
        for (int head = left; head < right; head++)
        {
            int tmp1 = dfs(left, head - 1);
            int tmp2 = dfs(head + 1, right);

            ret = min(ret, head + (max(tmp1, tmp2)));
        }

        memo[left][right] = ret;
        return ret;
    }

    // 2
    int subarraysDivByK(vector<int> &nums, int k)
    {
        unordered_map<int, int> hash;
        hash[0] = 1;

        int sum = 0, ret = 0;
        for (auto n : nums)
        {
            sum += n;
            int r = (sum % k + k) % k;
            if (hash.count(r))
                ret += hash[r];
            hash[r]++;
        }
        return ret;
    }

    // 3
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

        return ret.size() + 1;
    }

    // 4
    vector<string> ret;
    string path;
    vector<string> letterCasePermutation(string s)
    {
        dfs(s, 0);
        return ret;
    }

    void dfs(string &s, int pos)
    {
        if (pos == s.size())
        {
            ret.push_back(path);
            return;
        }

        char ch = s[pos];

        path.push_back(ch);
        dfs(s, pos + 1);
        path.pop_back();

        if (!isdigit(ch))
        {
            char tmp = change(ch);
            path.push_back(tmp);
            dfs(s, pos + 1);
            path.pop_back();
        }
    }

    char change(char ch)
    {
        if (ch >= 'a' && ch <= 'z')
            ch -= 32;
        else
            ch += 32;
        return ch;
    }

    // 5
    bool Row[9][10], Col[9][10], grid[3][3][10];
    int m, n;
    void solveSudoku(vector<vector<char>> &board)
    {
        m = board.size(), n = board[0].size();
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (board[i][j] != '.')
                {
                    int num = board[i][j] - '0';
                    Row[i][num] = Col[j][num] = grid[i / 3][j / 3][num] = true;
                }

        dfs(board);
    }

    bool dfs(vector<vector<char>> &board)
    {
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (board[i][j] == '.')
                {
                    for (int num = 1; num <= 9; num++)
                    {
                        if (!Row[i][num] && !Col[j][num] && !grid[i / 3][j / 3][num])
                        {
                            board[i][j] = num + '0';
                            Row[i][num] = Col[j][num] = grid[i / 3][j / 3][num] = true;
                            if (dfs(board))
                                return true;
                            else
                            {
                                board[i][j] = '.';
                                Row[i][num] = Col[j][num] = grid[i / 3][j / 3][num] = false;
                            }
                        }
                    }
                    return false;
                }
        return true;
    }

    // 6
    string longestPalindrome(string s)
    {
        int n = s.size(), begin = 0, maxlen = 1;
        vector<vector<bool>> dp(n, vector<bool>(n));

        for (int i = 0; i < n; i++)
            dp[i][i] = true;

        for (int L = 2; L < n; L++)
        {
            for (int i = 0; i < n; i++)
            {
                int j = i + L - 1;
                if (j >= n)
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
                    begin = i;
                    maxlen = j - i + 1;
                }
            }
        }

        return s.substr(begin, maxlen);
    }
};
