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
    string longestPalindrome(string s)
    {
        int n = s.size(), begin = 0, maxlen = 1;
        vector<vector<bool>> dp(n, vector<bool>(n));

        for (int i = 0; i < n; i++)
            dp[i][i] = true;

        for (int L = 2; L <= n; L++)
        {
            for (int i = 0; i < n; i++)
            {
                int j = i + L - 1;
                if (j >= n)
                    continue;

                if (s[i] != s[j])
                    dp[i][j] = false;
                else
                {
                    if (L == 2)
                        dp[i][j] = true;
                    else
                        dp[i][j] = dp[i + 1][j - 1];
                }

                int len = j - i + 1;
                if (dp[i][j] && len > maxlen)
                {
                    begin = i;
                    maxlen = len;
                }
            }
        }

        return s.substr(begin, maxlen);
    }

    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        priority_queue<ListNode *, vector<ListNode *>, cmp> q;

        for (auto &l : lists)
            if (l)
                q.push(l);

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

    vector<int> missingTwo(vector<int> &nums)
    {
        int xorsum = 0;
        for (auto n : nums)
            xorsum ^= n;

        for (int i = 1; i <= nums.size() + 2; i++)
            xorsum ^= i;

        int lsb = xorsum == INT_MIN ? xorsum : xorsum & (-xorsum);

        int x = 0, y = 0;
        for (auto n : nums)
        {
            if (n & lsb)
                x ^= n;
            else
                y ^= n;
        }

        for (int i = 1; i <= nums.size() + 2; i++)
        {
            if (i & lsb)
                x ^= i;
            else
                y ^= i;
        }

        return {x, y};
    }

    int findKthLargest(vector<int> &nums, int k)
    {
        srand(time(NULL));
        return quickSort(nums, 0, nums.size() - 1, k);
    }

    int getRandom(vector<int> &nums, int left, int right)
    {
        int r = rand();
        return nums[r % (right - left + 1) + left];
    }

    int quickSort(vector<int> &nums, int l, int r, int k)
    {
        if (l >= r)
            return nums[l];

        int key = getRandom(nums, l, r);
        int i = l, left = l - 1, right = r + 1;

        while (i < right)
        {
            if (nums[i] < key)
                swap(nums[i++], nums[++left]);
            else if (nums[i] == key)
                i++;
            else
                swap(nums[i], nums[--right]);
        }

        int rRange = r - right + 1, mRange = (right - 1) - (left + 1) + 1;
        if (rRange >= k)
            return quickSort(nums, right, r, k);
        else if (rRange + mRange >= k)
            return key;
        else
            return quickSort(nums, right, r, k - rRange - mRange);
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

        mergeSort(nums, 0, nums.size() - 1);
        return nums;
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

    int mySqrt(int x)
    {
        if (x < 1)
            return 0;
        int left = 1, right = x;
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
};