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
    int waysToStep(int n)
    {
        int base = 1000000007, dp1 = 1, dp2 = 2, dp3 = 4;
        if (n < 3)
            return n;

        while (n-- != 3)
        {
            int tmp3 = dp3, tmp2 = dp2;
            dp3 = ((dp1 + dp2) % base + dp3) % base;
            dp2 = tmp3, dp1 = tmp2;
        }
        return dp3;
    }

    ListNode *reverseKGroup(ListNode *head, int k)
    {
        int n = 0;
        ListNode *cur = head;
        while (cur)
        {
            n++;
            cur = cur->next;
        }

        n /= k;

        ListNode *newhead = new ListNode(0);
        ListNode *prev = newhead;
        cur = head;

        for (int i = 0; i < n; i++)
        {
            ListNode *tmp = cur;
            for (int j = 0; j < k; j++)
            {
                ListNode *next = cur->next;
                cur->next = prev->next;
                prev->next = cur;

                cur = next;
            }
            prev = tmp;
        }

        prev->next = cur;
        prev = newhead->next;
        delete newhead;
        return prev;
    }

    int triangleNumber(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        int ret = 0, n = nums.size();

        for (int i = n - 1; i >= 2; i--)
        {
            int left = 0, right = i - 1;
            while (left < right)
            {
                if (nums[left] + nums[right] > nums[i])
                {
                    ret += right - left;
                    right--;
                }
                else
                    left++;
            }
        }

        return ret;
    }

    bool vis[7][7];
    int m, n;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    string aim;
    bool exist(vector<vector<char>> &board, string word)
    {
        aim = word;
        m = board.size(), n = board[0].size();
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (board[i][j] == word[0])
                {
                    vis[i][j] = true;
                    if (dfs(board, i, j, 1))
                        return true;
                    vis[i][j] = false;
                }
        return false;
    }

    bool dfs(vector<vector<char>> &board, int i, int j, int pos)
    {
        if (pos == aim.size())
            return true;

        for (int k = 0; k < 4; k++)
        {
            int x = i + dx[k], y = j + dy[k];
            if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && board[x][y] == aim[pos])
            {
                vis[x][y] = true;
                if (dfs(board, x, y, pos + 1))
                    return true;
                vis[x][y] = false;
            }
        }
        return false;
    }

    string decodeString(string s)
    {
        stack<int> nums;
        stack<string> st;
        string ret;
        int n = 0;

        for (auto &ch : s)
        {
            if (isdigit(ch))
                n = n * 10 + (ch - '0');
            else if (ch == '[')
            {
                st.push(ret);
                ret = "";
                nums.push(n), n = 0;
            }
            else if (ch == ']')
            {
                int k = nums.top();
                nums.pop();
                string tmp = st.top();
                st.pop();
                while (k--)
                    tmp += ret;
                ret = tmp;
            }
            else
                ret += ch;
        }

        return ret;
    }
};

class KthLargest
{
private:
    int _k;
    priority_queue<int> q;

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
};