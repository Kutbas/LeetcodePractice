#include <mutex>
#include <vector>
#include <algorithm>
#include <climits>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <iostream>
#include <sstream>
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
    int lengthOfLongestSubstring(string s)
    {
        int n = s.size(), ret = 0;
        int hash[128] = {0};

        for (int left = 0, right = 0; right < n; right++)
        {
            char in = s[right];
            ++hash[in];
            while (hash[in] > 1)
            {
                char out = s[left++];
                --hash[out];
            }
            ret = max(ret, right - left + 1);
        }

        return ret;
    }

    // 2
    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        return mergeSort(lists, 0, lists.size() - 1);
    }

    ListNode *mergeSort(vector<ListNode *> &lists, int left, int right)
    {
        if (left > right)
            return nullptr;
        if (left == right)
            return lists[left];

        int mid = left + (right - left) / 2;
        ListNode *l1 = mergeSort(lists, left, mid);
        ListNode *l2 = mergeSort(lists, mid + 1, right);

        return merge2Lists(l1, l2);
    }

    ListNode *merge2Lists(ListNode *l1, ListNode *l2)
    {
        ListNode *ret = new ListNode(0);
        ListNode *prev = ret;
        ListNode *cur1 = l1, *cur2 = l2;
        while (cur1 && cur2)
        {
            if (cur1->val < cur2->val)
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

        prev = ret->next;
        delete ret;
        return prev;
    }

    // 3
    int m, n;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    vector<vector<int>> updateMatrix(vector<vector<int>> &mat)
    {
        m = mat.size(), n = mat[0].size();
        vector<vector<int>> dist(m, vector<int>(n, -1));

        queue<pair<int, int>> q;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (mat[i][j] == 0)
                {
                    dist[i][j] = 0;
                    q.push({i, j});
                }
            }

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
                        q.push({x, y});
                        dist[x][y] = dist[a][b] + 1;
                    }
                }
            }
        }

        return dist;
    }
};