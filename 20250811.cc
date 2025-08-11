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
    int longestPalindrome(string s)
    {
        int hash[127] = {0};
        for (char ch : s)
            hash[ch]++;

        int ret = 0;
        for (int x : hash)
        {
            ret += x / 2 * 2;
        }

        return ret < s.size() ? ret + 1 : ret;
    }

    vector<int> diStringMatch(string s)
    {
        int left = 0, right = s.size() - 1;
        vector<int> ret;

        for (char ch : s)
        {
            if (ch == 'I')
                ret.push_back(left++);
            else
                ret.push_back(right--);
        }

        ret.push_back(left);
        return ret;
    }

    // 1
    bool row[9][10];
    bool col[9][10];
    bool grid[3][3][10];
    int m, n;
    bool isValidSudoku(vector<vector<char>> &board)
    {
        m = board.size(), n = board[0].size();
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (board[i][j] != '.')
                {
                    int num = board[i][j] - '0';
                    if (!row[i][num] && !col[j][num] && !grid[i / 3][j / 3][num])
                        row[i][num] = col[j][num] = grid[i / 3][j / 3][num] = true;
                    else
                        return false;
                }

        return true;
    }

    // 2
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n, ret = 0;
    bool vis[16][16];
    int getMaximumGold(vector<vector<int>> &grid)
    {
        m = grid.size(), n = grid[0].size();

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j])
                {
                    vis[i][j] = true;
                    dfs(grid, i, j, grid[i][j]);
                    vis[i][j] = false;
                }

        return ret;
    }

    void dfs(vector<vector<int>> &grid, int i, int j, int sum)
    {
        ret = max(ret, sum);
        for (int k = 0; k < 4; k++)
        {
            int x = i + dx[k], y = j + dy[k];
            if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && grid[x][y])
            {
                vis[x][y] = true;
                dfs(grid, x, y, sum + grid[x][y]);
                vis[x][y] = false;
            }
        }
    }

    // 3
    int findKthLargest(vector<int> &nums, int k)
    {
        srand(time(nullptr));
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
            return 0;

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
        else if (mRange + rRange >= k)
            return key;
        else
            return quickSort(nums, l, left, k - mRange - rRange);
    }

    // 4
    int aim;
    vector<vector<int>> Ret;
    vector<int> Path;
    vector<vector<int>> combinationSum(vector<int> &candidates, int target)
    {
        aim = target;
        dfs(candidates, 0, 0);
        return Ret;
    }

    void dfs(vector<int> &nums, int sum, int pos)
    {
        if (sum > aim)
            return;

        if (sum == aim)
        {
            Ret.push_back(Path);
            return;
        }

        for (int i = pos; i < nums.size(); i++)
        {
            Path.push_back(nums[i]);
            dfs(nums, sum + nums[i], i);
            Path.pop_back();
        }
    }

    // 5
    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        return mergeLists(lists, 0, lists.size() - 1);
    }

    ListNode *mergeLists(vector<ListNode *> &lists, int left, int right)
    {
        if (left > right)
            return nullptr;
        if (left == right)
            return lists[left];

        int mid = left + (right - left) / 2;
        ListNode *cur1 = mergeLists(lists, left, mid);
        ListNode *cur2 = mergeLists(lists, mid + 1, right);

        return merge2lists(cur1, cur2);
    }

    ListNode *merge2lists(ListNode *l1, ListNode *l2)
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
            if (cur1->val <= cur2->val)
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

    // 6
    int wiggleMaxLength(vector<int> &nums)
    {
        int n = nums.size();
        if (n < 2)
            return n;

        int ret = 0, left = 0;
        for (int i = 1; i < n; i++)
        {
            int right = nums[i] - nums[i - 1];
            if (right == 0)
                continue;
            if (left * right <= 0)
                ret++;
            left = right;
        }

        return ret + 1;
    }
};