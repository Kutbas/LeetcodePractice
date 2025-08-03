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
    // 1
    int lengthOfLIS(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> ret;
        ret.push_back(nums[0]);

        for (int i = 1; i < n; i++)
        {
            if (nums[i] > ret.back())
                ret.push_back(nums[i]);
            else
            {
                int left = 0, right = ret.size() - 1;
                int mid = left + (right - left) / 2;
                while (left < right)
                {
                    if (nums[i] < ret[left])
                        left = mid + 1;
                    else
                        right = mid;
                }

                ret[mid] = nums[i];
            }
        }

        return ret.size();
    }

    // 2
    string hash[10] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    vector<string> ret;
    string path;
    vector<string> letterCombinations(string digits)
    {
        if (digits.empty())
            return ret;
        dfs(digits, 0);
        return ret;
    }

    void dfs(string &digits, int pos)
    {
        if (pos == digits.size())
        {
            ret.push_back(path);
            return;
        }

        for (int i = 0; i < hash[digits[pos] - '0'].size(); i++)
        {
            path.push_back(hash[digits[pos] - '0'][i]);
            dfs(digits, i + 1);
            path.pop_back();
        }
    }

    // 3
    vector<string> res;
    string pa;
    int N;
    int left = 0, right = 0;
    vector<string> generateParenthesis(int n)
    {
        N = n;
        dfs();
        return res;
    }

    void dfs()
    {
        if (right == N)
        {
            res.push_back(pa);
            return;
        }

        if (left < N)
        {
            pa.push_back('(');
            left++;
            dfs();
            pa.pop_back();
            left--;
        }

        if (right < left)
        {
            pa.push_back(')');
            right++;
            dfs();
            pa.pop_back();
            right--;
        }
    }

    // 4
    int tmp[50010];
    int reversePairs(vector<int> &nums)
    {
        return mergeSort(nums, 0, nums.size() - 1);
    }

    int mergeSort(vector<int> &nums, int left, int right)
    {
        if (left >= right)
            return 0;

        int mid = left + (right - left) / 2, ret = 0;
        ret += mergeSort(nums, left, mid);
        ret += mergeSort(nums, mid + 1, right);

        int i = 0, cur1 = left, cur2 = mid + 1;
        while (cur1 < mid)
        {
            if (cur2 < right && nums[cur1] <= 2.0 * nums[cur2])
                cur2++;
            else
            {
                ret += right - cur2 + 1;
                cur1++;
            }
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

    // 5
    int prev = INT_MIN;
    bool isValidBST(TreeNode *root)
    {
        if (root == nullptr)
            return true;

        bool left = isValidBST(root->left);
        if (!left)
            return false;

        bool cur = false;
        if (prev < root->val)
            cur = true;
        if (!cur)
            return false;

        prev = root->val;

        bool right = isValidBST(root->right);
        return right;
    }

    // 6
    int memo[101][101];
    int uniquePaths(int m, int n)
    {
        return dfs(m, n);
    }

    int dfs(int m, int n)
    {
        if (memo[m][n] != 0)
            return memo[m][n];

        if (m == 0 || n == 0)
        {
            memo[m][n] = 1;
            return 1;
        }

        memo[m][n] = memo[m - 1][n] + memo[m][n - 1];
        return memo[m][n];
    }

    // 7
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    vector<vector<int>> pacificAtlantic(vector<vector<int>> &heights)
    {
        vector<vector<int>> ret;
        m = heights.size(), n = heights[0].size();
        vector<vector<bool>> pac(m, vector<bool>(n));
        vector<vector<bool>> atl(m, vector<bool>(n));

        // 处理太平洋
        for (int i = 0; i < n; i++)
            dfs(heights, 0, i, pac);
        for (int i = 0; i < m; i++)
            dfs(heights, i, 0, pac);
        // 处理大西洋
        for (int i = 0; i < n; i++)
            dfs(heights, m - 1, i, atl);
        for (int i = 0; i < m; i++)
            dfs(heights, i, n - 1, atl);

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (pac[i][j] && atl[i][j])
                    ret.push_back({i, j});

        return ret;
    }

    void dfs(vector<vector<int>> &heights, int i, int j, vector<vector<bool>> &vis)
    {
        vis[i][j] = true;
        for (int k = 0; k < 4; k++)
        {
            int x = i + dx[k], y = j + dy[k];
            if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && heights[x][y] >= heights[i][j])
                dfs(heights, x, y, vis);
        }
    }
};