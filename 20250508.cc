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

struct cmp
{
    bool operator()(const ListNode *l1, const ListNode *l2)
    {
        return l1->val > l2->val;
    }
};

class Solution
{
public:
    int singleNumber(vector<int> &nums)
    {
        int ret = 0;
        for (int i = 0; i < 32; i++)
        {
            int tmp = 0;
            for (auto n : nums)
                if ((n >> i) & 1 == 1)
                    tmp++;
            tmp %= 3;
            if (tmp == 1)
                ret |= (1 << i);
        }

        return ret;
    }

    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        priority_queue<ListNode *, vector<ListNode *>, cmp> q;

        for (auto &l : lists)
            if (l)
                q.push(l);

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

    int m, n;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    bool vis[51][51] = {0};
    vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int color)
    {
        int origin = image[sr][sc];
        if (origin == color)
            return image;

        m = image.size(), n = image[0].size();

        queue<pair<int, int>> q;
        q.push({sr, sc});
        vis[sr][sc] = true;
        image[sr][sc] = color;

        while (q.size())
        {
            auto [a, b] = q.front();
            q.pop();

            for (int k = 0; k < 4; k++)
            {
                int x = a + dx[k], y = b + dy[k];
                if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && image[x][y] == origin)
                {
                    q.push({x, y});
                    vis[x][y] = true;
                    image[x][y] = color;
                }
            }
        }

        return image;
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

        int mid = left + (right - left) / 2;
        int ret = 0;
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
        while (cur2 <= mid)
            tmp[i++] = nums[cur2++];

        for (int j = left; j <= right; j++)
            nums[j] = tmp[j - left];

        return ret;
    }

    typedef pair<string, int> PSI;

    struct cmp
    {
        bool operator()(const PSI &p1, const PSI &p2)
        {
            if (p1.second == p2.second)
                return p1.first < p2.first;
            return p1.second > p2.second;
        }
    };

    vector<string> topKFrequent(vector<string> &words, int k)
    {
        unordered_map<string, int> hash;
        for (auto &s : words)
            hash[s]++;

        priority_queue<PSI, vector<PSI>, cmp> q;

        for (auto &psi : hash)
        {
            q.push(psi);
            if (q.size() > k)
                q.pop();
        }

        vector<string> ret;
        while (k--)
        {
            ret.push_back(q.top().first);
            q.pop();
        }
        reverse(ret.begin(), ret.end());

        return ret;
    }

    int tmp[50010];
    int reversePairs(vector<int> &record)
    {
        return merge_sort(record, 0, record.size() - 1);
    }

    int merge_sort(vector<int> &nums, int left, int right)
    {
        if (left >= right)
            return 0;

        int mid = left + (right - left) / 2;
        int ret = 0;
        ret += merge_sort(nums, left, mid);
        ret += merge_sort(nums, mid + 1, right);

        int i = 0, cur1 = left, cur2 = mid + 1;
        while (cur1 <= mid && cur2 <= right)
        {
            if (nums[cur1] <= nums[cur2])
                tmp[i++] = nums[cur2++];
            else
            {
                ret += right - cur2 + 1;
                tmp[i++] = nums[cur1++];
            }
        }

        while (cur1 <= mid)
            tmp[i++] = nums[cur1++];
        while (cur2 <= right)
            tmp[i++] = nums[cur2++];
        for (int j = left; j <= right; j++)
            nums[j] = tmp[j - left];

        return ret;
    }

    vector<vector<int>> generate(int numRows)
    {
        vector<vector<int>> ret(numRows);

        for (int i = 0; i < numRows; i++)
        {
            ret[i].resize(i + 1);
            ret[i][0] = ret[i][i] = 1;
            for (int j = 1; j < i; j++)
                ret[i][j] = ret[i - 1][j] + ret[i - 1][j - 1];
        }

        return ret;
    }
};