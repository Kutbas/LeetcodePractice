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
    int dx[8] = {0, 0, 1, -1, 1, 1, -1, -1};
    int dy[8] = {1, -1, 0, 0, 1, -1, 1, -1};
    int m, n;
    vector<vector<char>> updateBoard(vector<vector<char>> &board, vector<int> &click)
    {
        m = board.size(), n = board[0].size();

        int x = click[0], y = click[1];
        if (board[x][y] == 'M')
        {
            board[x][y] = 'X';
            return board;
        }

        dfs(board, x, y);
        return board;
    }

    void dfs(vector<vector<char>> &board, int i, int j)
    {
        int count = 0;
        for (int k = 0; k < 8; k++)
        {
            int x = i + dx[k], y = j + dy[k];
            if (x >= 0 && x < m && y >= 0 && y < n && board[x][y] == 'M')
                count++;
        }

        // 周围有地雷
        if (count)
        {
            board[i][j] = count + '0';
            return;
        }
        else // 周围没地雷
        {
            board[i][j] = 'B';
            for (int k = 0; k < 8; k++)
            {
                int x = i + dx[k], y = j + dy[k];
                if (x >= 0 && x < m && y >= 0 && y < n && board[x][y] == 'E')
                    dfs(board, x, y);
            }
        }
    }

    int M, N, K;
    bool vis[101][101] = {0};
    int ret;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int wardrobeFinishing(int m, int n, int cnt)
    {
        M = m, N = n, K = cnt;
        dfs(0, 0);
        return ret;
    }

    void dfs(int i, int j)
    {
        ret++;
        vis[i][j] = true;

        for (int k = 0; k < 4; k++)
        {
            int x = i + dx[k], y = j + dy[k];
            if (x >= 0 && x < M && y >= 0 && y < N && !vis[x][y] && check(x, y))
                dfs(x, y);
        }
    }

    bool check(int i, int j)
    {
        int tmp = 0;
        while (i)
        {
            tmp += i % 10;
            i /= 10;
        }
        while (j)
        {
            tmp += j % 10;
            j /= 10;
        }
        return tmp <= K;
    }

    int memo[31] = {-1};

    int fib(int n)
    {
        return dfs(n);
    }

    int dfs(int n)
    {
        if (memo[n] != -1)
            return memo[n];

        if (n == 0 || n == -1)
        {
            memo[n] = n;
            return n;
        }

        memo[n] = dfs(n - 1) + dfs(n - 2);
        return memo[n];
    }

    vector<int> searchRange(vector<int> &nums, int target)
    {
        int begin = -1, left = 0, right = nums.size() - 1;

        while (left < right)
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] < target)
                left = mid + 1;
            else
                right = mid;
        }

        if (nums[left] != target)
            return {-1, -1};

        begin = left, left = 0, right = nums.size() - 1;
        while (left < right)
        {
            int mid = left + (right - left + 1) / 2;
            if (nums[mid] <= target)
                left = mid;
            else
                right = mid - 1;
        }

        return {begin, left};
    }

    typedef pair<string, int> PSI;

    struct cmp
    {
        bool operator()(const PSI &p1, const PSI &p2)
        {
            if (p1.second == p2.second)
                return p1.first > p2.first;
            return p1.second < p2.second;
        }
    };

    vector<string> topKFrequent(vector<string> &words, int k)
    {
        unordered_map<string, int> hash;
        for (auto &word : words)
            hash[word]++;

        priority_queue<PSI, vector<PSI>, cmp> q;
        for (auto &pir : hash)
            q.push(pir);

        vector<string> ret;

        while (k--)
        {
            auto [a, b] = q.top();
            q.pop();
            ret.push_back(a);
        }

        return ret;
    }

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    bool vis[101][101];
    int k;
    int wardrobeFinishing(int m, int n, int cnt)
    {
        k = cnt;
        queue<pair<int, int>> q;
        q.push({0, 0});
        vis[0][0] = true;

        int ret = 1;
        while (q.size())
        {
            auto [a, b] = q.front();
            q.pop();
            for (int k = 0; k < 4; k++)
            {
                int x = a + dx[k], y = b + dy[k];
                if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && check(x, y))
                {
                    ret++;
                    vis[x][y] = true;
                    q.push({x, y});
                }
            }
        }

        return ret;
    }

    bool check(int i, int j)
    {
        int tmp;
        while (i)
        {
            tmp += i % 10;
            i /= 10;
        }
        while (j)
        {
            tmp += j % 10;
            j /= 10;
        }
        return tmp <= k;
    }

    vector<vector<int>> ret1;
    vector<int> path;
    bool vis[9];
    vector<vector<int>> permuteUnique(vector<int> &nums)
    {
        dfs(nums, 0);
        return ret1;
    }

    void dfs(vector<int> &nums, int pos)
    {
        if (pos == nums.size())
        {
            ret1.push_back(path);
            return;
        }

        for (int i = pos; i < nums.size(); i++)
        {
            path.push_back(nums[i]);
            dfs(nums, i + 1);
            path.pop_back();
        }
    }

    vector<vector<int>> ret1;
    vector<int> path;
    int N, K;
    vector<vector<int>> combine(int n, int k)
    {
        N = n, K = k;
        dfs1(1);
        return ret1;
    }

    void dfs1(int pos)
    {
        if (path.size() == K)
        {
            ret1.push_back(path);
            return;
        }

        for (int i = pos; i <= N; i++)
        {
            path.push_back(i);
            dfs1(i + 1);
            path.pop_back();
        }
    }

    void reorderList(ListNode *head)
    {
        ListNode *slow = head, *fast = head;
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode *newhead = new ListNode(0);
        ListNode *prev = newhead;
        ListNode *cur = slow->next;
        slow->next = nullptr;

        while (cur)
        {
            ListNode *next = cur->next;
            cur->next = prev->next;
            prev->next = cur;
            cur = next;
        }

        ListNode *cur1 = head, *cur2 = newhead->next;
        ListNode *ret = new ListNode(0);
        prev = ret;

        while (cur1)
        {
            prev->next = cur1;
            prev = prev->next;
            cur1 = cur1->next;

            if (cur2)
            {
                prev->next = cur2;
                prev = prev->next;
                cur2 = cur2->next;
            }
        }

        head = ret->next;
        delete newhead;
    }

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n, step = 0, ret = 0;
    bool vis[21][21];
    int uniquePathsIII(vector<vector<int>> &grid)
    {
        m = grid.size(), n = grid[0].size();
        step += 2;

        int bx = 0, by = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j] == 0)
                    step++;
                else if (grid[i][j] == 1)
                {
                    bx = i;
                    by = j;
                }

        vis[bx][by] = true;
        dfs2(grid, bx, by, 1);
        return ret;
    }

    void dfs2(vector<vector<int>> &grid, int i, int j, int count)
    {
        if (grid[i][j] == 2)
            if (count == step)
            {
                ret++;
                return;
            }

        for (int k = 0; k < 4; k++)
        {
            int x = i + dx[k], y = j + dy[k];
            if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && grid[x][y] == 0)
            {
                count++;
                vis[x][y] = true;
                dfs2(grid, x, y, count);
            }
        }
    }
};