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
    vector<int> smallestK(vector<int> &arr, int k)
    {
        srand(time(NULL));
        quickSort(arr, 0, arr.size() - 1, k);
        return {arr.begin(), arr.begin() + k};
    }

    int getRandom(vector<int> &arr, int left, int right)
    {
        int r = rand();
        return arr[r % (right - left + 1) + left];
    }

    void quickSort(vector<int> &arr, int l, int r, int k)
    {
        if (l >= r)
            return;

        int key = getRandom(arr, l, r);
        int i = l, left = l - 1, right = r + 1;
        while (i < right)
        {
            if (arr[i] < key)
                swap(arr[i++], arr[++left]);
            else if (arr[i] == key)
                i++;
            else
                swap(arr[i], arr[--right]);
        }

        int lRange = left - l + 1, mRange = (right - 1) - (left + 1) + 1;
        if (lRange >= k)
            return quickSort(arr, l, left, k);
        else if (lRange + mRange >= k)
            return;
        else
            return quickSort(arr, right, r, k - lRange - mRange);
    }

    bool isPalindrome(string s)
    {
        string tmp;
        for (char ch : s)
            if (isalnum(ch))
                tmp += tolower(ch);
        for (int left = 0, right = tmp.size() - 1; left < right; left++, right--)
            if (tmp[left] != tmp[right])
                return false;

        return true;
    }

    struct cmp
    {
        bool operator()(const ListNode &l1, const ListNode &l2)
        {
            return l1.val > l2.val;
        }
    };

    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        priority_queue<ListNode *, vector<ListNode *>, cmp> q;
        for (auto list : lists)
            if (list)
                q.push(list);

        ListNode *head = new ListNode(0);
        ListNode *prev = head;

        while (q.size())
        {
            auto t = q.top();
            q.pop();
            prev->next = t;
            prev = prev->next;

            if (t->next)
                q.push(t->next);
        }

        prev = head->next;
        delete head;
        return prev;
    }

    // 4
    int widthOfBinaryTree(TreeNode *root)
    {
        vector<pair<TreeNode *, unsigned int>> q;
        q.push_back({root, 1});

        unsigned int ret = 0;
        while (q.size())
        {
            auto [x1, y1] = q[0];
            auto [x2, y2] = q.back();
            ret = max(ret, y2 - y1 + 1);

            vector<pair<TreeNode *, unsigned int>> tmp;
            for (auto [x, y] : q)
            {
                if (x->left)
                    tmp.push_back({x->left, 2 * y});
                if (x->right)
                    tmp.push_back({x->right, 2 * y + 1});
            }
            q = tmp;
        }

        return ret;
    }

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    bool vis[101][101] = {0};
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
                    vis[i][j] = 1;
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
                    if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && dist[x][y] == -1)
                    {
                        dist[x][y] = dist[a][b] + 1;
                        q.push({x, y});
                        vis[x][y] = true;
                        ret = max(ret, dist[x][y]);
                    }
                }
            }
        }

        return ret;
    }

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

    ListNode *reverseList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *newhead = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;

        return newhead;
    }

    ListNode *swapPairs(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *tmp = swapPairs(head->next->next);
        ListNode *ret = head->next;
        head->next->next = head;
        head->next = tmp;

        return ret;
    }
};