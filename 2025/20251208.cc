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
    ListNode *swapPairs(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *ret = new ListNode(0);
        ListNode *prev = ret;
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

        prev = ret->next;
        delete ret;
        return prev;
    }

    // 2
    bool Row[9][10], Col[9][10], Grid[3][3][10];
    bool isValidSudoku(vector<vector<char>> &board)
    {
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
            {
                if (board[i][j] != '.')
                {
                    int num = board[i][j] - '0';
                    if (!Row[i][num] && !Col[j][num] && !Grid[i / 3][j / 3][num])
                        Row[i][num] = Col[j][num] = Grid[i / 3][j / 3][num] = true;
                    else
                        return false;
                }
            }
        return true;
    }

    // 3
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    int maxDistance(vector<vector<int>> &grid)
    {
        m = grid.size(), n = grid[0].size();
        vector<vector<int>> dist(m, vector<int>(n, -1));

        queue<pair<int, int>> q;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j])
                {
                    dist[i][j] = 0;
                    q.push({i, j});
                }

        int ret = -1;
        while (q.size())
        {
            int sz = q.size();
            while (sz--)
            {
                auto [a, b] = q.front();
                q.pop();
                for (int k = 0; k < 4; k++)
                {
                    int x = a + dx[k], y = b + dy[k];
                    if (x >= 0 && x < m && y >= 0 && y < n && dist[x][y] == -1)
                    {
                        dist[x][y] = dist[a][b] + 1;
                        q.push({x, y});
                        ret = max(ret, dist[x][y]);
                    }
                }
            }
        }
        return ret;
    }

    // 4
    class cmp
    {
        bool operator()(ListNode *l1, ListNode *l2) const
        {
            return l1->val > l2->val;
        }
    };

    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        priority_queue<ListNode *, vector<ListNode *>, cmp> q;

        for (auto &list : lists)
            if (list)
                q.push(list);

        ListNode *ret = new ListNode(0);
        ListNode *prev = ret;

        while (q.size())
        {
            auto t = q.top();
            q.pop();

            prev->next = t;
            prev = prev->next;

            if (t->next)
                q.push(t->next);
        }

        prev = ret->next;
        delete ret;
        return prev;
    }

    // 5
    vector<int> twoSum(vector<int> &nums, int target)
    {
        unordered_map<int, int> hash;
        for (int i = 0; i < nums.size(); i++)
        {
            int x = target - nums[i];
            if (hash.count(x))
                return {i, hash[x]};
            else
                hash[nums[i]] = i;
        }
        return {-1, -1};
    }

    // 6
    string largestNumber(vector<int> &nums)
    {
        vector<string> strs;
        for (auto n : nums)
            strs.push_back(to_string(n));

        sort(strs.begin(), strs.end(), [&](string &s1, string &s2)
             { return s1 + s2 > s2 + s1; });

        string ret;
        for (auto s : strs)
            ret += s;

        return ret[0] == '0' ? "0" : ret;
    }

    // 7
    bool checkCol[10], Dig1[20], Dig2[20];
    int N;
    vector<vector<string>> ret;
    vector<string> path;
    vector<vector<string>> solveNQueens(int n)
    {
        N = n;
        path.resize(N);
        for (int i = 0; i < N; i++)
            path[i].append(N, '.');

        dfs(0);

        return ret;
    }

    void dfs(int row)
    {
        if (row == N)
        {
            ret.push_back(path);
            return;
        }

        for (int col = 0; col < N; col++)
        {
            if (!checkCol[col] && !Dig1[row + col] && !Dig2[row - col + N])
            {
                path[row][col] = 'Q';
                checkCol[col] = Dig1[row + col] = Dig2[row - col + N] = true;
                dfs(row + 1);
                path[row][col] = '.';
                checkCol[col] = Dig1[row + col] = Dig2[row - col + N] = false;
            }
        }
    }
};