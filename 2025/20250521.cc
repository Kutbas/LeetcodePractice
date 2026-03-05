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
    ListNode *reverseKGroup(ListNode *head, int k)
    {
        ListNode *cur = head;
        int n = 0;
        while (cur)
        {
            cur = cur->next;
            n++;
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
                // prev = prev->next;
            }
            prev = tmp;
        }

        prev->next = cur;

        prev = newhead->next;
        delete newhead;
        return prev;
    }

    int mySqrt(int x)
    {
        int left = 0, right = x;
        while (left < right)
        {
            int mid = left + (right - left + 1) / 2;
            if (mid * mid <= x)
                left = mid;
            else
                right = mid - 1;
        }
        return left;
    }

    ListNode *reverseKGroup(ListNode *head, int k)
    {
        int n = 0;
        ListNode *cur = head;
        while (cur)
        {
            cur = cur->next;
            n++;
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

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    int maxDistance(vector<vector<int>> &grid)
    {
        m = grid.size(), n = grid[0].size();
        int ret = -1;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j] == 0)
                    ret = max(ret, BFS(grid, i, j));

        return ret;
    }

    int BFS(vector<vector<int>> &grid, int i, int j)
    {
        queue<pair<int, int>> q;
        bool vis[101][101] = {0};
        q.push({i, j});
        vis[i][j] = true;
        int ret = 0;

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
                    if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && grid[x][y] == 0)
                    {
                        q.push({x, y});
                        vis[x][y] = true;
                        ret++;
                    }
                }
            }
        }

        return ret;
    }

    bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
    {
        unordered_map<int, vector<int>> edges;
        vector<int> in(numCourses);

        for (auto &e : prerequisites)
        {
            int a = e[0], b = e[1]; // b->a
            edges[b].push_back(a);
            in[a]++;
        }

        vector<int> ret;
        queue<int> q;
        for (int i = 0; i < numCourses; i++)
            if (in[i] == 0)
                q.push(i);

        while (q.size())
        {
            int t = q.front();
            q.pop();
            ret.push_back(t);

            for (auto a : edges[t])
                if (--in[a] == 0)
                    q.push(a);
        }

        return ret.size() == numCourses;
    }

    vector<int> ret;
    vector<int> tmp;
    vector<int> index;
    vector<int> tmpIndex;
    vector<int> countSmaller(vector<int> &nums)
    {
        int n = nums.size();
        ret.resize(n);
        tmp.resize(n);
        index.resize(n);
        tmpIndex.resize(n);
        for (int i = 0; i < n; i++)
            index[i] = i;
        mergeSort(nums, 0, n - 1);
        return ret;
    }

    void mergeSort(vector<int> &nums, int left, int right)
    {
        if (left >= right)
            return;

        int mid = left + (right - left) / 2;
        mergeSort(nums, left, mid);
        mergeSort(nums, mid + 1, right);

        int i = 0, cur1 = left, cur2 = mid + 1;

        while (cur1 <= mid && cur2 <= right)
        {
            if (nums[cur1] <= nums[cur2])
            {
                tmp[i] = nums[cur2];
                tmpIndex[i++] = index[cur2++];
            }
            else
            {
                ret[index[cur1]] += right - cur2 + 1;
                tmp[i] = nums[cur1];
                tmpIndex[i++] = index[cur1++];
            }
        }

        while (cur1 <= mid)
        {
            tmp[i] = nums[cur1];
            tmpIndex[i++] = index[cur1++];
        }
        while (cur2 <= right)
        {
            tmp[i] = nums[cur2];
            tmpIndex[i++] = index[cur2++];
        }
        for (int j = left; j <= right; j++)
        {
            nums[j] = tmp[j - left];
            index[j] = tmpIndex[j - left];
        }
    }

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
                if (grid[i][j] == 1)
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
};