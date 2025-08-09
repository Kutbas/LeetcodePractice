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
    }

    // 2
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
    {
        if (l1 == nullptr)
            return l2;
        if (l2 == nullptr)
            return l1;

        if (l1->val <= l2->val)
        {
            l1->next = mergeTwoLists(l1->next, l2);
            return l1;
        }
        else
        {
            l2->next = mergeTwoLists(l1, l2->next);
            return l2;
        }
    }

    // 3
    int longestOnes(vector<int> &nums, int k)
    {
        int ret = 0;
        for (int left = 0, right = 0, count = 0; right < nums.size(); right++)
        {
            if (nums[right] == 0)
                count++;
            while (count > k)
                if (nums[left++] == 0)
                    count--;
            ret = max(ret, right - left + 1);
        }

        return ret;
    }

    // 4
    vector<vector<int>> ret;
    vector<int> path;
    bool vis[7];
    vector<vector<int>> permute(vector<int> &nums)
    {
        dfs(nums);
        return ret;
    }

    void dfs(vector<int> &nums)
    {
        if (path.size() == nums.size())
        {
            ret.push_back(path);
            return;
        }

        for (int i = 0; i < nums.size(); i++)
        {
            if (!vis[i])
            {
                path.push_back(nums[i]);
                vis[i] = true;
                dfs(nums);
                vis[i] = false;
                path.pop_back();
            }
        }
    }

    // 5
    int dx[8] = {0, 0, 1, -1, 1, 1, -1, -1};
    int dy[8] = {1, -1, 0, 0, 1, -1, 1, -1};
    int m, n;
    vector<vector<char>> updateBoard(vector<vector<char>> &board, vector<int> &click)
    {
        m = board.size(), n = board[0].size();

        int x = click[0], y = click[1];
        if (board[x][y] == 'M')
        {
            board[x][y] = 'X';
            return board;
        }

        dfs(board, x, y);
        return board;
    }

    void dfs(vector<vector<char>> &board, int i, int j)
    {
        int count = 0;
        for (int k = 0; k < 8; k++)
        {
            int x = i + dx[k], y = j + dy[k];
            if (x >= 0 && x < m && y >= 0 && y < n && board[x][y] == 'M')
                count++;
        }

        if (count)
            board[i][j] = count + '0';
        else
        {
            board[i][j] = 'B';
            for (int k = 0; k < 8; k++)
            {
                int x = i + dx[k], y = j + dy[k];
                if (x >= 0 && x < m && y >= 0 && y < n && board[x][y] == 'E')
                    dfs(board, x, y);
            }
        }
    }

    // 6
    vector<vector<string>> Ret;
    vector<string> Path;
    int N;
    bool checkRow[10], checkCol[10], checkDig1[20], checkDig2[20];
    vector<vector<string>> solveNQueens(int n)
    {
        N = n;
        Path.resize(n);
        for (int i = 0; i < n; i++)
            Path[i].append(n, '.');

        dfs(0);

        return Ret;
    }

    void dfs(int row)
    {
        if (row == N)
        {
            Ret.push_back(Path);
            return;
        }

        for (int col = 0; col < N; col++)
        {
            if (!checkRow[row] && !checkCol[col] && !checkDig1[row + col] && !checkDig2[row - col + N])
            {
                Path[row][col] = 'Q';
                checkRow[row] = checkCol[col] = checkDig1[row + col] = checkDig2[row - col + N] = true;
                dfs(row + 1);
                checkRow[row] = checkCol[col] = checkDig1[row + col] = checkDig2[row - col + N] = false;
                Path[row][col] = '.';
            }
        }
    }

    // 7
    bool check[16];
    int res = 0;
    vector<int> TMP;
    int N;
    int countArrangement(int n)
    {
        N = n;
        DFS(1);
        return res;
    }

    void DFS(int pos)
    {
        if (TMP.size() == N)
        {
            res++;
            return;
        }

        for (int i = 1; i <= N; i++)
        {
            if (!check[i])
            {
                if (i % pos == 0 && pos % i == 0)
                {
                    TMP.push_back(i);
                    check[i] = true;
                    DFS(i + 1);
                    check[i] = false;
                    TMP.pop_back();
                }
            }
        }
    }

    // 8
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
        for (auto x : nums1)
        {
            if (x > nums2[index2[left]])
                ret[index2[left++]] = x;
            else
                ret[index2[right--]] = x;
        }

        return ret;
    }
};