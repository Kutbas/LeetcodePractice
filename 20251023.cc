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
    string largestNumber(vector<int> &nums)
    {
        vector<string> strs;
        for (auto n : nums)
            strs.push_back(to_string(n));

        sort(strs.begin(), strs.end(), [&](const string &s1, const string &s2)
             { return s1 + s2 > s2 + s1; });

        string ret;
        for (auto s : strs)
            ret += s;

        return ret[0] == '0' ? "0" : ret;
    }

    // 2
    vector<int> missingTwo(vector<int> &nums)
    {
        int xorsum = 0, n = nums.size();
        for (int i = 1; i <= n + 2; i++)
            xorsum ^= i;
        for (auto n : nums)
            xorsum ^= n;

        int lsb = xorsum == INT_MIN ? xorsum : xorsum & (-xorsum);

        int x = 0, y = 0;
        for (int i = 1; i <= n + 2; i++)
        {
            if (i & lsb)
                x ^= i;
            else
                y ^= i;
        }
        for (auto n : nums)
        {
            if (n & lsb)
                x ^= n;
            else
                y ^= n;
        }
        return {x, y};
    }

    // 3
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    typedef pair<int, int> PIR;
    int cutOffTree(vector<vector<int>> &forest)
    {
        m = forest.size(), n = forest[0].size();

        vector<PIR> trees;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (forest[i][j] > 1)
                    trees.push_back({i, j});

        sort(trees.begin(), trees.end(), [&](const PIR &p1, const PIR &p2)
             { return forest[p1.first][p1.second] < forest[p2.first][p2.second]; });

        int bx = 0, by = 0, ret = 0;
        for (auto [a, b] : trees)
        {
            int step = dfs(forest, bx, by, a, b);
            if (step == -1)
                return -1;

            ret += step;
            bx = a, by = b;
        }

        return ret;
    }

    bool vis[51][51];
    int dfs(vector<vector<int>> &f, int bx, int by, int ex, int ey)
    {
        memset(vis, 0, sizeof vis);

        queue<PIR> q;
        q.push({bx, by});
        vis[bx][by] = true;

        int ret = 0;
        while (q.size())
        {
            int sz = q.size();
            ret++;
            while (sz--)
            {
                auto [a, b] = q.front();
                q.pop();
                for (int k = 0; k < 4; k++)
                {
                    int x = a + dx[k], y = b + dy[k];
                    if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && f[x][y])
                    {
                        if (x == ex && y == ey)
                            return ret;
                        q.push({x, y});
                        vis[x][y] = true;
                    }
                }
            }
        }

        return -1;
    }

    // 4
    // 5
    vector<int> advantageCount(vector<int> &nums1, vector<int> &nums2)
    {
        int n = nums1.size();
        sort(nums1.begin(), nums1.end());

        vector<int> index2(n);
        for (int i = 0; i < n; i++)
            index2[i] = i;

        sort(index2.begin(), index2.end(), [&](int i, int j)
             { return nums2[i] < nums2[j]; });

        vector<int> ret(n);
        int left = 0, right = n - 1;
        for (auto n : nums1)
        {
            if (n > nums2[index2[left]])
                ret[index2[left++]] = n;
            else
                ret[index2[right--]] = n;
        }

        return ret;
    }

    // 6
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

        return mergeList(l1, l2);
    }

    ListNode *mergeList(ListNode *l1, ListNode *l2)
    {
        if (l1 == nullptr)
            return l2;
        if (l2 == nullptr)
            return l1;

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

    // 7
    vector<int> findSubstring(string s, vector<string> &words)
    {
        int m = words.size(), len = words[0].size();
        unordered_map<string, int> hash1;
        for (auto &word : words)
            hash1[word]++;

        vector<int> ret;
        for (int i = 0; i < len; i++)
        {
            unordered_map<string, int> hash2;
            for (int left = i, right = i, count = 0; right + len <= s.size(); right += len)
            {
                string in = s.substr(right, len);
                ++hash2[in];
                if (hash1.count(in) && hash2[in] <= hash1[in])
                    count++;
                while (right - left + 1 > len * m)
                {
                    string out = s.substr(left, len);
                    if (hash1.count(out) && hash2[out] <= hash1[out])
                        count--;
                    hash2[out]--;
                    left += len;
                }
                if (count == m)
                    ret.push_back(left);
            }
        }

        return ret;
    }
};