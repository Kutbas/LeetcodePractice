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
    int jewelleryValue(vector<vector<int>> &grid)
    {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + grid[i - 1][j - 1];

        return dp[m][n];
    }

    // 1
    int missingNumber(vector<int> &nums)
    {
        int xorsum = 0;
        for (auto n : nums)
            xorsum ^= n;
        for (int i = 1; i <= nums.size(); i++)
            xorsum ^= i;

        return xorsum;
    }

    // 2
    int fib(int n)
    {
        if (n < 2)
            return n;

        return fib(n - 1) + fib(n - 2);
    }

    // 3
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

    // 4
    TreeNode *pruneTree(TreeNode *root)
    {
        if (root == nullptr)
            return nullptr;

        root->left = pruneTree(root->left);
        root->right = pruneTree(root->right);

        if (root->left == nullptr && root->val == 0 && root->right == nullptr)
            return nullptr;

        return root;
    }

    // 5
    vector<vector<int>> threeSum(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        vector<vector<int>> ret;

        int i = 0;
        while (i < n - 2)
        {
            int left = i + 1, right = n - 1;
            while (left < right)
            {

                if (nums[i] + nums[left] + nums[right] > 0)
                    right--;
                else if (nums[i] + nums[left] + nums[right] < 0)
                    left++;
                else
                {
                    ret.push_back({nums[i], nums[left], nums[right]});
                    do
                    {
                        left++;
                    } while (left < right && nums[left] == nums[left - 1]);
                    do
                    {
                        right--;
                    } while (left < right && nums[right] == nums[right + 1]);
                }
            }

            do
            {
                i++;
            } while (i < n - 2 && nums[i] == nums[i - 1]);
        }

        return ret;
    }

    // 6
    int dx[8] = {0, 0, 1, -1, 1, 1, -1, -1};
    int dy[8] = {1, -1, 0, 0, 1, -1, 1, -1};
    int m, n;
    vector<vector<char>> updateBoard(vector<vector<char>> &board, vector<int> &click)
    {
        m = board.size(), n = board[0].size();

        int bx = click[0], by = click[1];
        if (board[bx][by] == 'M')
        {
            board[bx][by] = 'X';
            return board;
        }

        dfs(board, bx, by);

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
        {
            board[i][j] = count + '0';
            return;
        }
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
};