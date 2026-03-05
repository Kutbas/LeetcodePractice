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
    string convert(string s, int numRows)
    {
        if (numRows == 1)
            return s;

        string ret;
        int n = s.size(), d = 2 * n - 2;
        for (int i = 0; i < n; i += d)
            ret += s[i];

        for (int k = 1; k < numRows - 1; k++)
            for (int i = k, j = d - k; i < n || j < n; i += d, j += d)
            {
                if (i < n)
                    ret += s[i];
                if (j < n)
                    ret += s[j];
            }

        for (int i = numRows - 1; i < n; i += d)
            ret += s[i];

        return ret;
    }

    vector<vector<int>> threeSum(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        vector<vector<int>> ret;
        int i = 0, n = nums.size();
        while (i < n - 2)
        {
            int left = i + 1, right = n - 1;
            while (left < right)
            {
                if (nums[left] + nums[right] < -nums[i])
                    left++;
                else if (nums[left] + nums[right] > -nums[i])
                    right--;
                else
                {
                    ret.push_back({nums[i], nums[left], nums[right]});

                    do
                    {
                        left++;
                    } while (nums[left] == nums[left - 1] && left < right);

                    do
                    {
                        right--;
                    } while (nums[right] == nums[right + 1] && left < right);
                }
            }

            do
            {
                i++;
            } while (nums[i] == nums[i - 1] && i < n - 2);
        }

        return ret;
    }

    string minWindow(string s, string t)
    {
        int begin = -1, minlen = INT_MAX, m = t.size();
        int hash1[128] = {0};
        int hash2[128] = {0};
        for (auto ch : t)
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
                    minlen = right - left + 1;
                    begin = left;
                }
                char out = s[left++];
                if (hash2[out]-- <= hash1[out])
                    count--;
            }
        }

        return begin == -1 ? "" : s.substr(begin, minlen);
    }

    vector<int> largestValues(TreeNode *root)
    {
        vector<int> ret;
        if (root == nullptr)
            return ret;

        queue<TreeNode *> q;
        q.push(root);

        while (q.size())
        {
            int tmp = INT_MIN;
            int sz = q.size();

            while (sz--)
            {
                auto t = q.front();
                q.pop();

                tmp = max(tmp, t->val);

                if (t->left)
                    q.push(t->left);
                if (t->right)
                    q.push(t->right);
            }

            ret.push_back(tmp);
        }

        return ret;
    }

    void reorderList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr || head->next->next == nullptr)
            return;

        ListNode *slow = head, *fast = head;
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode *head2 = new ListNode(0);
        ListNode *cur = slow->next;
        slow->next = nullptr;

        while (cur)
        {
            ListNode *next = cur->next;
            cur->next = head2->next;
            head2->next = cur;
            cur = next;
        }

        ListNode *newhead = new ListNode(0);
        ListNode *prev = newhead;
        ListNode *cur1 = head, *cur2 = head2->next;

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

        delete head2, newhead;
        return;
    }

    vector<vector<string>> groupAnagrams(vector<string> &strs)
    {
        unordered_map<string, vector<string>> hash;
        vector<vector<string>> ret;

        for (auto &s : strs)
        {
            string tmp = s;
            sort(tmp.begin(), tmp.end());
            hash[tmp].push_back(s);
        }

        for (auto &[a, b] : hash)
            ret.push_back(b);

        return ret;
    }

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

    void duplicateZeros(vector<int> &arr)
    {
        int cur = 0, dest = -1, n = arr.size();
        while (cur < n)
        {
            if (arr[cur])
                dest++;
            else
                dest += 2;
            if (dest >= n - 1)
                break;
            cur++;
        }

        if (dest == n)
        {
            arr[n - 1] = 0;
            dest -= 2;
            cur--;
        }

        while (cur >= 0)
        {
            if (arr[cur])
                arr[dest--] = arr[cur--];
            else
            {
                arr[dest--] = 0;
                arr[dest--] = 0;
                cur--;
            }
        }
        return;
    }

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    bool vis[51][51] = {0};
    int m, n;
    int maxAreaOfIsland(vector<vector<int>> &grid)
    {
        m = grid.size(), n = grid[0].size();
        int ret = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (!vis[i][j] && grid[i][j] == 1)
                {
                    ret = max(ret, bfs(grid, i, j));
                }
            }
        return ret;
    }

    int bfs(vector<vector<int>> &grid, int i, int j)
    {
        int ret = 1;
        queue<pair<int, int>> q;
        q.push({i, j});
        vis[i][j] = true;

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
                    if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && grid[x][y] == 1)
                    {
                        ret++;
                        vis[x][y] = true;
                        q.push({x, y});
                    }
                }
            }
        }
        return ret;
    }

    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        return mergeSort(lists, 0, lists.size() - 1);
    }

    ListNode *mergeSort(vector<ListNode *> &lists, int left, int right)
    {
        if (left == right)
            return lists[left];
        if (left > right)
            return nullptr;

        int mid = left + (right - left) / 2;
        ListNode *l1 = mergeSort(lists, left, mid);
        ListNode *l2 = mergeSort(lists, mid + 1, right);

        return merge2Lists(l1, l2);
    }

    ListNode *merge2Lists(ListNode *l1, ListNode *l2)
    {
        if (l1 == nullptr)
            return l2;
        if (l2 == nullptr)
            return l1;

        ListNode *head = new ListNode(0);
        ListNode *prev = head;
        ListNode *cur1 = l1, *cur2 = l2;

        while (cur1 && cur2)
        {
            if (cur1->val <= cur2->val)
            {
                prev->next = cur1;
                prev = prev->next;
                cur1 = cur1->next;
            }
            else
            {
                prev->next = cur2;
                prev = prev->next;
                cur2 = cur2->next;
            }
        }

        if (cur1)
            prev->next = cur1;
        if (cur2)
            prev->next = cur2;

        prev = head->next;
        delete head;
        return prev;
    }

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    bool vis[301][301] = {0};
    int m, n;
    int numIslands(vector<vector<char>> &grid)
    {
        m = grid.size(), n = grid[0].size();
        int ret = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (!vis[i][j] && grid[i][j] == '1')
                {
                    ret++;
                    BFS(grid, i, j);
                }
            }
        return ret;
    }

    void BFS(vector<vector<char>> &grid, int i, int j)
    {
        queue<pair<int, int>> q;
        q.push({i, j});
        vis[i][j] = true;

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
                    if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && grid[x][y] == '1')
                    {
                        q.push({x, y});
                        vis[x][y] = true;
                    }
                }
            }
        }
    }

    vector<int> largestValues(TreeNode *root)
    {
        vector<int> ret;
        if (root == nullptr)
            return ret;

        queue<TreeNode *> q;
        q.push(root);

        while (q.size())
        {
            int tmp = INT_MIN;
            int sz = q.size();
            while (sz--)
            {
                auto t = q.front();
                q.pop();

                tmp = max(tmp, t->val);
                if (t->left)
                    q.push(t->left);
                if (t->right)
                    q.push(t->right);
            }
            ret.push_back(tmp);
        }

        return ret;
    }
};