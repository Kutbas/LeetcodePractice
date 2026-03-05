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
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;

    vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int color)
    {
        int origin = image[sr][sc];
        if (origin == color)
            return image;
        m = image.size(), n = image[0].size();

        queue<pair<int, int>> q;
        q.push({sr, sc});
        image[sr][sc] = color;
        while (q.size())
        {
            auto [a, b] = q.front();
            q.pop();
            for (int k = 0; k < 4; k++)
            {
                int x = a + dx[k], y = b + dy[k];
                if (x >= 0 && x < m && y >= 0 && y < n && image[x][y] == origin)
                {
                    q.push({x, y});
                    image[x][y] = color;
                }
            }
        }

        return image;
    }

    // 2
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
        while (cur1 <= mid)
        {
            if (cur2 <= right && nums[cur1] <= 2.0 * nums[cur2])
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

    // 3
    int ret = 0;
    int sumNumbers(TreeNode *root)
    {
        dfs(root, 0);
        return ret;
    }

    void dfs(TreeNode *root, int path)
    {
        if (root->left == nullptr && root->right == nullptr)
        {
            ret += path;
            return;
        }

        path = path * 10 + root->val;
        dfs(root->left, path);
        dfs(root->right, path);
    }

    // 4
    ListNode *reverseList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *newhead = reverseList(head->next->next);
        head->next->next = head;
        head->next = nullptr;

        return newhead;
    }

    // 5
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

                ret[i][j] = dp[x2][y2] - dp[x2][y1 - 1] - dp[x1 - 1][y2] + dp[x1 - 1][y1 - 1];
            }

        return ret;
    }

    // 6
    void hanota(vector<int> &A, vector<int> &B, vector<int> &C)
    {
        dfs(A, B, C, A.size());
        return;
    }

    void dfs(vector<int> &from, vector<int> &buffer, vector<int> &to, int n)
    {
        if (n == 1)
        {
            to.push_back(from.back());
            from.pop_back();
        }

        dfs(from, to, buffer, n - 1);
        to.push_back(from.back());
        from.pop_back();
        dfs(buffer, from, to, n - 1);
    }

    ListNode *swapPairs(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *tmp = swapPairs(head->next->next);
        ListNode *ret = head->next;
        ret->next = head;
        head->next = tmp;

        return ret;
    }
};