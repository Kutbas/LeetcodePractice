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
    string minWindow(string s, string t)
    {
        int begin = -1, minlen = INT_MAX, m = t.size();
        int hash1[128] = {0};
        int hash2[129] = {0};

        for (char ch : t)
            hash1[ch]++;

        for (int left = 0, right = 0, count = 0; right < s.size(); right++)
        {
            char in = s[right];
            if (++hash2[in] <= hash1[in])
                count++;
            while (count == m)
            {
                if (right - left + 1 < minlen)
                {
                    begin = left;
                    minlen = right - left + 1;
                }

                char out = s[left++];
                if (hash2[out]-- <= hash1[out])
                    count--;
            }
        }

        return begin == -1 ? "" : s.substr(begin, minlen);
    }

    // 2
    vector<vector<int>> ret;
    vector<int> path;
    bool vis[9];
    vector<vector<int>> permuteUnique(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        dfs(nums, 0);
        return ret;
    }

    void dfs(vector<int> &nums, int pos)
    {
        if (path.size() == nums.size())
        {
            ret.push_back(path);
            return;
        }

        for (int i = pos; i < nums.size(); i++)
        {
            if (vis[i] || (i != 0 && vis[i] && !vis[i - 1]))
                continue;
            vis[i] = true;
            path.push_back(nums[i]);
            dfs(nums, i);
            vis[i] = false;
            path.pop_back();
        }
    }

    // 3
    ListNode *swapPairs(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *newhead = new ListNode(0);
        ListNode *prev = newhead;
        ListNode *cur = head, *next = cur->next, *nnext = next->next;

        while (cur && next)
        {
            prev->next = next;
            next->next = cur;
            cur->next = nnext;

            prev = cur;
            cur = nnext;
            if (cur)
                next = cur->next;
            if (next)
                nnext = next->next;
        }

        prev = newhead->next;
        delete newhead;
        return prev;
    }

    // 4
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
    {
        if (l1 == nullptr)
            return l2;
        if (l2 == nullptr)
            return l1;

        if (l1->val <= l2->val)
        {
            l1->next = mergeTwoLists(l1->next, l2);
            return l1;
        }
        else
        {
            l2->next = mergeTwoLists(l1, l2->next);
            return l2;
        }
    }

    // 5
    vector<vector<string>> Ret;
    vector<string> Path;
    int N;
    bool checkCol[10], checkDig1[20], checkDig2[20];
    vector<vector<string>> solveNQueens(int n)
    {
        N = n;
        Path.resize(n);
        for (int i = 0; i < n; i++)
            Path[i].append(n, '.');

        dfs(0);

        return Ret;
    }

    void dfs(int row)
    {
        if (row == N)
        {
            Ret.push_back(Path);
            return;
        }

        for (int col = 0; col < N; col++)
        {
            if (!checkCol[col] && !checkDig1[row + col] && !checkDig2[row - col + N])
            {
                checkCol[col] = checkDig1[row + col] = checkDig2[row - col + N] = true;
                Path[row][col] = 'Q';
                dfs(row + 1);
                Path[row][col] = '.';
                checkCol[col] = checkDig1[row + col] = checkDig2[row - col + N] = false;
            }
        }
    }

    // 6
    int memo[201][201];
    int getMoneyAmount(int n)
    {
        return dfs(1, n);
    }

    int dfs(int left, int right)
    {
        if (left <= right)
            return 0;
        if (memo[left][right])
            return memo[left][right];

        int ret = INT_MAX;
        for (int head = left; head <= right; head++)
        {
            int x = dfs(left, head - 1);
            int y = dfs(head + 1, right);

            ret = min(ret, head + max(x, y));
        }

        memo[left][right] = ret;
        return ret;
    }

    // 7
    vector<vector<int>> res;
    vector<int> tmp;
    vector<vector<int>> subsets(vector<int> &nums)
    {
        DFS(nums, 0);
        return res;
    }

    void DFS(vector<int> &nums, int pos)
    {
        res.push_back(tmp);

        if (pos == nums.size())
        {
            return;
        }

        for (int i = pos; i < nums.size(); i++)
        {
            tmp.push_back(nums[i]);
            DFS(nums, i + 1);
            tmp.pop_back();
        }
    }
};