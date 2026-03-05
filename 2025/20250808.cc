#include <bits/stdc++.h>
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
    int lengthOfLIS(vector<int> &nums)
    {
        vector<int> ret;
        ret.push_back(nums[0]);

        for (int i = 1; i < nums.size(); i++)
        {
            if (nums[i] > ret.back())
                ret.push_back(nums[i]);
            else
            {
                int left = 0, right = ret.size() - 1;
                while (left < right)
                {
                    int mid = left + (right - left) / 2;
                    if (nums[i] < ret[mid])
                        left = mid + 1;
                    else
                        right = mid;
                }
                ret[left] = nums[i];
            }
        }

        return ret.size();
    }

    // 2
    ListNode *swapPairs(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *ret = swapPairs(head->next->next);
        ListNode *tmp = head->next;
        tmp->next = head;
        head->next = ret;

        return ret;
    }

    // 3
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;

    vector<vector<int>> pacificAtlantic(vector<vector<int>> &heights)
    {
        m = heights.size(), n = heights[0].size();
        vector<vector<bool>> pac(m, vector<bool>(n));
        vector<vector<bool>> atl(m, vector<bool>(n));

        for (int i = 0; i < m; i++)
            dfs(heights, i, 0, pac);
        for (int i = 0; i < n; i++)
            dfs(heights, 0, i, pac);
        for (int i = 0; i < m; i++)
            dfs(heights, i, n - 1, atl);
        for (int i = 0; i < n; i++)
            dfs(heights, m - 1, i, atl);

        vector<vector<int>> ret;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (pac[i][j] && atl[i][j])
                    ret.push_back({i, j});

        return ret;
    }

    void dfs(vector<vector<int>> &heights, int i, int j, vector<vector<bool>> &vis)
    {
        for (int k = 0; k < 4; k++)
        {
            int x = i + dx[k], y = j + dy[k];
            if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && heights[x][y] >= heights[i][j])
            {
                vis[x][y] = true;
                dfs(heights, x, y, vis);
            }
        }
    }

    // 4
    int memo[201][201];
    int getMoneyAmount(int n)
    {
        return dfs(1, n);
    }

    int dfs(int left, int right)
    {
        if (left >= right)
            return 0;
        if (memo[left][right])
            return memo[left][right];

        int ret = INT_MAX;
        for (int head = left; head <= right; head++)
        {
            int tmp1 = dfs(left, head - 1);
            int tmp2 = dfs(head + 1, right);

            ret = min(ret, max(tmp1, tmp2));
        }

        memo[left][right] = ret;
        return ret;
    }

    // 5
    vector<string> res;
    string path;
    vector<string> letterCasePermutation(string s)
    {
        dfs(s, 0);
        return res;
    }

    void dfs(string &s, int pos)
    {
        if (s.size() == pos)
        {
            res.push_back(path);
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

    // 6
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    bool vis[101][101];
    int K;
    int wardrobeFinishing(int m, int n, int cnt)
    {
        K = cnt;
        int ret = 1;
        queue<pair<int, int>> q;
        q.push({0, 0});
        vis[0][0] = true;

        while (q.size())
        {
            auto [a, b] = q.front();
            q.pop();
            for (int k = 0; k < 4; k++)
            {
                int x = a + dx[k], y = b + dy[k];
                if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && check(x, y))
                {
                    vis[x][y] = true;
                    ret++;
                    q.push({x, y});
                }
            }
        }

        return ret;
    }

    bool check(int x, int y)
    {
        int tmp = 0;
        while (x)
        {
            tmp += x % 10;
            x /= 10;
        }
        while (y)
        {
            tmp += y % 10;
            y /= 10;
        }
        return tmp <= K;
    }

    // 7
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
                    if (dfs(board, i, j, word, 0))
                        return true;
                    else
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
            if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && board[x][y] == word[pos + 1])
            {
                vis[x][y] = true;
                if (dfs(board, i, j, word, pos + 1))
                    return true;
                else
                    return false;
            }
        }

        return false;
    }
};