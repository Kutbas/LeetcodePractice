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
    bool check[16] = {0};
    int ret = 0;
    int countArrangement(int n)
    {
        dfs(1, n);
        return ret;
    }

    void dfs(int pos, int n)
    {
        if (pos == n + 1)
        {
            ret++;
            return;
        }

        for (int i = 1; i <= n; i++)
            if (!check[i] && (pos % i == 0 || i % pos == 0))
            {
                check[i] = true;
                dfs(pos + 1, n);
                check[i] = false;
            }
    }

    bool checkCol[10], checkDig1[20], checkDig2[20];
    vector<vector<string>> ret;
    vector<string> path;
    int N;
    vector<vector<string>> solveNQueens(int n)
    {
        N = n;
        path.resize(n);
        for (int i = 0; i < n; i++)
            path[i].append(n, '.');

        dfs(0);
        return ret;
    }

    void dfs(int row)
    {
        if (row == N)
        {
            ret.push_back(path);
            return;
        }

        for (int col = 0; col < N; col++)
        {
            if (!checkCol[col] && !checkDig1[row - col + N] && !checkDig2[row + col])
            {
                path[row][col] = 'Q';
                checkCol[col] = checkDig1[row - col + N] = checkDig2[row + col] = true;
                dfs(row + 1);
                path[row][col] = '.';
                checkCol[col] = checkDig1[row - col + N] = checkDig2[row + col] = false;
            }
        }
    }

    bool validateStackSequences(vector<int> &pushed, vector<int> &popped)
    {
        stack<int> nums;
        int i = 0, n = popped.size();

        for (auto num : pushed)
        {
            nums.push(num);
            while (nums.size() && nums.top() == popped[i])
            {
                nums.pop();
                i++;
            }
        }

        return i == n;
    }

    int findPeakElement(vector<int> &nums)
    {
        int left = 0, right = nums.size() - 1;
        while (left < right)
        {
            int mid = left + (right - left + 1) / 2;
            if (nums[mid] >= nums[mid - 1])
                left = mid;
            else
                right = mid - 1;
        }

        return left;
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
            while (cur2 <= right && nums[cur1] <= 2 * nums[cur2])
                cur2++;
            if (cur2 == right)
                break;
            ret += mid - cur1 + 1;
            cur1++;
        }

        cur1 = left, cur2 = mid + 1;

        while (cur1 <= mid && cur2 <= right)
            tmp[i++] = nums[cur1] <= nums[cur2] ? nums[cur1++] : nums[cur2++];
        while (cur1 <= mid)
            tmp[i++] = nums[cur1++];
        while (cur2 <= right)
            tmp[i++] = nums[cur2++];

        for (int j = left; j <= right; j++)
            nums[j] = tmp[j - left];

        return ret;
    }

    bool evaluateTree(TreeNode *root)
    {
        if (root->left == nullptr && root->right == nullptr)
            return root->val == 0 ? false : true;

        bool left = evaluateTree(root->left);
        bool right = evaluateTree(root->right);
        return root->val == 2 ? left | right : left & right;
    }

    TreeNode *pruneTree(TreeNode *root)
    {
        if (root == nullptr)
            return nullptr;

        root->left = pruneTree(root->left);
        root->right = pruneTree(root->right);
        if (root->left == nullptr && root->right == nullptr && root->val==0)
            return nullptr;

        return root;
    }
};