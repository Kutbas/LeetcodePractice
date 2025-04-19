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
    string multiply(string num1, string num2)
    {
        int m = num1.size(), n = num2.size();
        vector<int> tmp(m + n - 1);
        string ret;

        for (int i = m - 1; i >= 0; i--)
            for (int j = n - 1; j >= 0; j--)
                tmp[i + j] += (num1[i] - '0') * (num2[j] - '0');

        int t = 0, cur = m + n - 2;
        while (cur >= 0 || t)
        {
            if (cur >= 0)
                t += tmp[cur--];
            ret += (t % 10 + '0');
            t /= 10;
        }

        reverse(ret.begin(), ret.end());

        while (ret.size() > 1 && *ret.begin() == '0')
            ret.erase(0, 1);

        return ret;
    }

    vector<vector<int>> generate(int numRows)
    {
        vector<vector<int>> ret;
        ret.resize(numRows);
        for (int i = 0; i < numRows; i++)
        {
            ret[i].resize(i + 1);
            ret[i][0] = ret[i][i] = 1;
            for (int j = 1; j < i; j++)
                ret[i][j] = ret[i - 1][j] + ret[i - 1][j - 1];
        }

        return ret;
    }

    int pivotIndex(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> f(n), g(n);
        for (int i = 1; i < n; i++)
            f[i] = f[i - 1] + nums[i - 1];
        for (int i = n - 2; i >= 0; i--)
            g[i] = g[i + 1] + nums[i + 1];
        for (int i = 0; i < n; i++)
            if (f[i] == g[i])
                return i;

        return -1;
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

        ListNode *newhead = new ListNode(0);
        ListNode *cur = slow->next;
        slow->next = nullptr;

        while (cur)
        {
            ListNode *next = cur->next;
            cur->next = newhead->next;
            newhead->next = cur;
            cur = next;
        }

        ListNode *ret = new ListNode(0);
        ListNode *prev = ret;
        ListNode *cur1 = head, *cur2 = newhead->next;

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
        delete newhead, ret;
        return;
    }

    vector<vector<int>> zigzagLevelOrder(TreeNode *root)
    {
        vector<vector<int>> ret;
        if (root == nullptr)
            return ret;

        int level = 1;
        queue<TreeNode *> q;
        q.push(root);

        while (q.size())
        {
            int sz = q.size();
            vector<int> tmp;
            for (int i = 0; i < sz; i++)
            {
                auto t = q.front();
                q.pop();
                tmp.push_back(t->val);

                if (t->left)
                    q.push(t->left);
                if (t->right)
                    q.push(t->right);
            }

            if (level++ % 2 == 0)
                reverse(tmp.begin(), tmp.end());
            ret.push_back(tmp);
        }

        return ret;
    }

    int tmp[50010];
    int reversePairs(vector<int> &nums)
    {
        return mergeSort(nums, 0, nums.size() - 1);
    }

    int mergeSort(vector<int> &nums, int left, int right)
    {
        if (left >= right)
            return 0;

        int ret = 0;
        int mid = left + (right - left) / 2;
        ret += mergeSort(nums, left, mid);
        ret += mergeSort(nums, mid + 1, right);

        int i = 0, cur1 = left, cur2 = mid + 1;
        while (cur1 <= mid)
        {
            while (cur2 <= right && nums[cur1] <= 2.0 * nums[cur2])
                cur2++;
            if (cur2 > right)
                break;

            ret += right - cur2 + 1;
            cur1++;
        }

        cur1 = left, cur2 = mid + 1;
        while (cur1 <= mid && cur2 <= right)
            tmp[i++] = nums[cur1] <= nums[cur2] ? nums[cur2++] : nums[cur1++];
        while (cur1 <= mid)
            tmp[i++] = nums[cur1++];
        while (cur2 <= right)
            tmp[i++] = nums[cur2++];
        for (int j = left; j <= right; j++)
            nums[j] = tmp[j - left];

        return ret;
    }

    vector<vector<int>> matrixBlockSum(vector<vector<int>> &mat, int k)
    {
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1] + mat[i - 1][j - 1];

        vector<vector<int>> ret(m, vector<int>(n));
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                int x1 = max(0, i - k) + 1, y1 = max(0, j - k) + 1;
                int x2 = min(m - 1, i + k) + 1, y2 = min(n - 1, j + k) + 1;
                ret[i][j] = dp[x2][y2] - dp[x1 - 1][y2] - dp[x2][y1 - 1] + dp[x1 - 1][y1 - 1];
            }

        return ret;
    }

    ListNode *swapPairs(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *newhead = new ListNode(0);
        ListNode *prev = newhead, *cur = head, *next = cur->next, *nnext = next->next;

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

    string changestr(string s)
    {
        string ret;
        for (auto ch : s)
        {
            if (ch != '#')
                ret += ch;
            else if (ret.size())
                ret.pop_back();
        }
        return ret;
    }

    bool backspaceCompare(string s, string t)
    {
        return changestr(s) == changestr(t);
    }

    string addBinary(string a, string b)
    {
        string ret;

        int cur1 = a.size() - 1, cur2 = b.size() - 1, t = 0;
        while (cur1 >= 0 || cur2 >= 0 || t)
        {
            if (cur1 >= 0)
                t += a[cur1--] - '0';
            if (cur2 >= 0)
                t += b[cur2--] - '0';
            ret += t % 2 + '0';
            t /= 2;
        }

        reverse(ret.begin(), ret.end());

        return ret;
    }

    bool validateStackSequences(vector<int> &pushed, vector<int> &popped)
    {
        int i = 0, n = popped.size();
        stack<int> st;

        for (auto num : pushed)
        {
            st.push(num);
            while (st.size() && st.top() == popped[i])
            {
                st.pop();
                i++;
            }
        }

        return i == n;
    }

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};

    int nearestExit(vector<vector<char>> &maze, vector<int> &e)
    {
        int m = maze.size(), n = maze[0].size();

        bool vis[m][n];
        memset(vis, 0, sizeof(vis));

        queue<pair<int, int>> q;
        q.push({e[0], e[1]});
        vis[e[0]][e[1]] = true;

        int step = 0;
        while (q.size())
        {
            step++;
            int sz = q.size();
            for (int i = 0; i < sz; i++)
            {
                auto [a, b] = q.front();
                q.pop();

                for (int j = 0; j < 4; j++)
                {
                    int x = a + dx[j], y = b + dy[j];
                    if (x >= 0 && x < m && y >= 0 && y < n && maze[x][y] == '.' && !vis[x][y])
                    {
                        // 判断是否达到出口
                        if (x == 0 || x == m - 1 || y == 0 || y == n - 1)
                            return step;
                        q.push({x, y});
                        vis[x][y] = true;
                    }
                }
            }
        }

        return -1;
    }

    int minMutation(string startGene, string endGene, vector<string> &bank)
    {
        unordered_set<string> vis; // 标记已经搜索过的状态
        unordered_set<string> hash(bank.begin(), bank.end());
        string change = "ACGT";

        if (startGene == endGene)
            return 0;
        if (!hash.count(endGene))
            return -1;

        queue<string> q;
        q.push(startGene);
        vis.insert(startGene);

        int ret = 0;
        while (q.size())
        {
            ret++;
            int sz = q.size();
            while (sz--)
            {
                string t = q.front();
                q.pop();
                for (int i = 0; i < 8; i++)
                {
                    string tmp = t;
                    for (int j = 0; j < 4; j++)
                    {
                        tmp[i] = change[j];
                        if (hash.count(tmp) && !vis.count(tmp))
                        {
                            if (tmp == endGene)
                                return ret;
                            q.push(tmp);
                            vis.insert(tmp);
                        }
                    }
                }
            }
        }
        return -1;
    }
};