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
    int tmp[50010];
    int reversePairs(vector<int> &nums)
    {
        return mergeSort(nums, 0, nums.size() - 1);
    }

    int mergeSort(vector<int> &nums, int left, int right)
    {
        if (left >= right)
            return 0;

        int ret = 0, mid = left + (right - left) / 2;
        ret += mergeSort(nums, left, mid);
        ret += mergeSort(nums, mid + 1, right);

        int i = 0, cur1 = left, cur2 = mid + 1;

        while (cur1 <= mid && cur2 <= right)
        {
            if (nums[cur1] <= nums[cur2])
                tmp[i++] = nums[cur2++];
            else
            {
                ret += right - cur2 + 1;
                tmp[i++] = nums[cur1++];
            }
        }
        while (cur1 <= mid)
            tmp[i++] = nums[cur1++];
        while (cur2 <= right)
            tmp[i++] = nums[cur2++];

        for (int j = left; j <= right; j++)
            nums[j] = tmp[j - left];

        return ret;
    }

    // 2
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    bool vis[7][7];
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
    int maxProfit(vector<int> &prices)
    {
        int ret = 0, n = prices.size();

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

    // 4
    int longestOnes(vector<int> &nums, int k)
    {
        int ret = 0;

        for (int left = 0, right = 0, count = 0; right < nums.size(); right++)
        {
            if (nums[right] == 0)
                count++;
            while (count > k)
                if (nums[left++] == 0)
                    count--;
            ret = max(ret, right - left + 1);
        }

        return ret;
    }

    // 5
    vector<string> ret;
    string path;
    int N, left = 0, right = 0;
    vector<string> generateParenthesis(int n)
    {
        N = n;
        dfs();
        return ret;
    }

    void dfs()
    {
        if (N == right)
        {
            ret.push_back(path);
            return;
        }

        if (left < N)
        {
            path.push_back('(');
            left++;
            dfs();
            path.pop_back();
            left--;
        }

        if (right < left)
        {
            path.push_back(')');
            right++;
            dfs();
            path.pop_back();
            right--;
        }
    }

    // 6
    vector<string> Ret;
    string Path;
    vector<string> letterCasePermutation(string s)
    {
        dfs(s, 0);
        return Ret;
    }

    void dfs(string &s, int pos)
    {
        if (pos == s.size())
        {
            Ret.push_back(Path);
            return;
        }

        char ch = s[pos];

        Path.push_back(ch);
        dfs(s, pos + 1);
        Path.pop_back();

        if (!isdigit(ch))
        {
            char tmp = change(ch);
            Path.push_back(tmp);
            dfs(s, pos + 1);
            Path.pop_back();
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
};