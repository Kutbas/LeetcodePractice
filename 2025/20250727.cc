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
    string addBinary(string a, string b)
    {
        string ret;
        int m = a.size(), n = b.size(), t = 0;
        int cur1 = m - 1, cur2 = n - 1;
        while (t || cur1 >= 0 || cur2 >= 0)
        {
            if (cur1 >= 0)
                t += a[cur1--] - '0';
            if (cur2 >= 0)
                t += b[cur2--] - '0';
            ret += to_string(t % 2);
            t /= 2;
        }

        reverse(ret.begin(), ret.end());
        return ret;
    }

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n, step = 0, ret = 0;
    bool vis[21][21];
    int uniquePathsIII(vector<vector<int>> &grid)
    {
        m = grid.size(), n = grid[0].size();
        step += 2;

        int bx = 0, by = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == 1)
                {
                    bx = i;
                    by = j;
                }
                else if (grid[i][j] == 0)
                    step++;
            }

        vis[bx][by] = true;
        dfs(grid, bx, by, 1);

        return ret;
    }

    void dfs(vector<vector<int>> &grid, int i, int j, int count)
    {
        if (grid[i][j] == 2)
        {
            if (count == step)
                ret++;
            return;
        }

        for (int k = 0; k < 4; k++)
        {
            int x = i + dx[k], y = j + dy[k];
            if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && grid[x][y])
            {

                vis[x][y] = true;
                dfs(grid, x, y, count + 1);
                vis[x][y] = false;
            }
        }
    }

    int path;
    int sum;
    bool check[13];
    int subsetXORSum(vector<int> &nums)
    {
        dfs(nums, 0);
        return sum;
    }

    void dfs(vector<int> &nums, int pos)
    {
        sum += path;
        for (int i = pos; i < nums.size(); i++)
        {
            if (!check[i])
            {
                check[i] = true;
                path ^= nums[i];
                dfs(nums, i);
                path ^= nums[i];
                check[i] = false;
            }
        }
    }

    vector<vector<int>> res;
    vector<int> pa;
    bool checked[9];
    vector<vector<int>> permuteUnique(vector<int> &nums)
    {
        dfs1(nums, 0);
        return res;
    }

    void dfs1(vector<int> &nums, int pos)
    {
        if (pos == nums.size())
        {
            res.push_back(pa);
            return;
        }

        for (int i = 0; i < nums.size(); i++)
        {
            if (!checked[i])
            {
                checked[i] = true;
                pa.push_back(nums[i]);
                dfs1(nums, i + 1);
                pa.pop_back();
                checked[i] = false;
            }
        }
    }

    vector<int> ret1;
    vector<int> tmp;
    vector<int> index;
    vector<int> tmpIndex;
    vector<int> countSmaller(vector<int> &nums)
    {
        int n = nums.size();
        ret1.resize(n);
        tmp.resize(n);
        index.resize(n);
        tmpIndex.resize(n);

        for (int i = 0; i < n; i++)
            index[i] = i;

        mergeSort(nums, 0, nums.size() - 1);

        return ret1;
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
                ret1[index[cur1]] += right - cur2 + 1;
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