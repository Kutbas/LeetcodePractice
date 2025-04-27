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
        string ret;
        vector<int> tmp(m + n - 1);

        for (int i = m - 1; i >= 0; i--)
            for (int j = n - 1; j >= 0; j--)
                tmp[i + j] += (num1[i] - '0') * (num2[j] - '0');

        int t = 0, cur = m + n - 2;
        while (t || cur >= 0)
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

    bool containsDuplicate(vector<int> &nums)
    {
        unordered_map<int, int> hash;
        for (auto n : nums)
            if (++hash[n] >= 2)
                return true;
        return false;
    }

    int tmp[50010];
    vector<int> sortArray(vector<int> &nums)
    {
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
            tmp[i++] = nums[cur1] <= nums[cur2] ? nums[cur1++] : nums[cur2++];

        while (cur1 <= mid)
            tmp[i++] = nums[cur1++];
        while (cur2 <= right)
            tmp[i++] = nums[cur2++];

        for (int j = left; j <= right; j++)
            nums[j] = tmp[j - left];

        return;
    }

    string addBinary(string a, string b)
    {
        int m = a.size(), n = b.size();
        string ret;

        int t = 0, cur1 = m - 1, cur2 = n - 1;
        while (cur1 >= 0 || cur2 >= 0 || t)
        {
            if (cur1 >= 0)
                t += (a[cur1--] - '0');
            if (cur2 >= 0)
                t += (b[cur2--] - '0');
            ret += (t % 2 + '0');
            t /= 2;
        }

        reverse(ret.begin(), ret.end());
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

    vector<int> largestValues(TreeNode *root)
    {
        vector<int> ret;
        if (root == nullptr)
            return ret;

        queue<TreeNode *> q;
        q.push(root);

        while (q.size())
        {
            int sz = q.size();
            int tmp = INT_MIN;
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

    string longestPalindrome(string s)
    {
        int n = s.size(), begin = 0, maxlen = 1;
        vector<vector<int>> dp(n, vector<int>(n));

        for (int i = 0; i < n; i++)
            dp[i][i] = true;

        for (int L = 2; L <= n; L++)
        {
            for (int i = 0; i < n; i++)
            {
                int j = i + L - 1;
                if (j >= n)
                    break;

                if (s[i] != s[j])
                    dp[i][j] = false;
                else
                {
                    if (L == 2)
                        dp[i][j] = true;
                    else
                        dp[i][j] = dp[i + 1][j - 1];
                }

                if (dp[i][j] && j - i + 1 > maxlen)
                {
                    begin = i;
                    maxlen = j - i + 1;
                }
            }
        }

        return s.substr(begin, maxlen);
    }

    vector<int> twoSum(vector<int> &nums, int target)
    {
        unordered_map<int, int> hash;

        int sum = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            int x = target - nums[i];
            if (hash.count(x))
                return {i, hash[x]};
            hash[nums[i]] = i;
        }
        return {-1, -1};
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
            return quickSort(nums, l, left, k - rRange - mRange);
    }

    vector<int> ret;
    int index[500010];
    int tmp[500010];
    int tmpIndex[500010];
    vector<int> countSmaller(vector<int> &nums)
    {
        int n = nums.size();
        ret.resize(n);
        for (int i = 0; i < nums.size(); i++)
            index[i] = i;
        mergesort(nums, 0, nums.size() - 1);
        return ret;
    }

    void mergesort(vector<int> &nums, int left, int right)
    {
        if (left >= right)
            return ;

        int mid = left + (right - left) / 2;
        // int ret = 0;

        mergesort(nums, left, mid);
        mergesort(nums, mid + 1, right);

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
};