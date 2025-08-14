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
    bool canJump(vector<int> &nums)
    {
        int left = 0, right = 0, maxPos = 0, n = nums.size();

        while (left <= right)
        {
            if (maxPos >= n - 1)
                return true;

            for (int i = left; i <= right; i++)
            {
                maxPos = max(maxPos, nums[i] + 1);
            }

            left = right + 1;
            right = maxPos;
        }

        return false;
    }

    // 1
    long prev = LONG_MIN;
    bool isValidBST(TreeNode *root)
    {
        if (root == nullptr)
            return true;

        bool left = isValidBST(root->left);
        if (!left)
            return false;

        bool cur = false;
        if (root->val > prev)
            cur = true;
        if (!cur)
            return false;

        prev = root->val;
        bool right = isValidBST(root->right);
        return right;
    }

    // 2
    int subarraySum(vector<int> &nums, int k)
    {
        unordered_map<int, int> hash;
        hash[0] = 1;

        int sum = 0, ret = 0;

        for (auto n : nums)
        {
            sum += n;
            if (hash.count(sum - k))
                ret += hash[sum - k];
            hash[sum]++;
        }

        return ret;
    }

    // 3
    bool containsDuplicate(vector<int> &nums)
    {
        unordered_map<int, int> hash;
        for (auto n : nums)
            if (++hash[n] >= 2)
                return true;

        return false;
    }

    // 4
    int memo[201][201];
    int getMoneyAmount(int n)
    {
        return dfs(1, n);
    }

    int dfs(int left, int right)
    {
        if (left >= right)
            return 0;

        if (memo[left][right])
            return memo[left][right];

        int ret = INT_MAX;
        for (int head = left; head <= right; head++)
        {
            int x = dfs(left, head - 1);
            int y = dfs(head + 1, right);

            ret = min(ret, head + max(x, y));
        }

        memo[left][right] = ret;
        return ret;
    }

    // 5
    vector<int> ret;
    vector<int> tmp;
    vector<int> index;
    vector<int> tmpindex;
    vector<int> countSmaller(vector<int> &nums)
    {
        int n = nums.size();
        ret.resize(n);
        tmp.resize(n);
        index.resize(n);
        tmpindex.resize(n);

        for (int i = 0; i < n; i++)
            index[i] = i;

        mergeSort(nums, 0, nums.size() - 1);
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
                tmpindex[i++] = index[cur2++];
            }
            else
            {
                ret[index[cur1]] += right - cur2 + 1;
                tmp[i] = nums[cur1];
                tmpindex[i++] = index[cur1++];
            }
        }
        while (cur1 <= mid)
        {
            tmp[i] = nums[cur1];
            tmpindex[i++] = index[cur1++];
        }
        while (cur2 <= right)
        {
            tmp[i] = nums[cur2];
            tmpindex[i++] = index[cur2++];
        }

        for (int j = left; j <= right; j++)
        {
            nums[j] = tmp[j - left];
            index[j] = tmpindex[j - left];
        }
    }

    // 6
    string hash[10] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    vector<string> res;
    string path;
    vector<string> letterCombinations(string digits)
    {
        dfs(digits, 0);
        return res;
    }

    void dfs(string &digits, int pos)
    {
        if (pos == digits.size())
        {
            res.push_back(path);
            return;
        }

        for (char ch : hash[digits[pos] - '0'])
        {
            path.push_back(ch);
            dfs(digits, pos + 1);
            path.pop_back();
        }
    }
};