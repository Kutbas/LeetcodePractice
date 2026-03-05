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
    int longestArithSeqLength(vector<int> &nums)
    {
        unordered_map<int, int> hash;
        hash[nums[0]] = 0;

        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(n, 2));

        int ret = 2;
        for (int i = 1; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                int a = 2 * nums[i] - nums[j];
                if (hash.count(a))
                    dp[i][j] = dp[hash[a]][i] + 1;
                ret = max(ret, dp[i][j]);
            }
            hash[nums[i]] = i;
        }
        return ret;
    }

    int numberOfArithmeticSlices(vector<int> &nums)
    {
        int n = nums.size();
        unordered_map<long long, vector<int>> hash;
        for (int i = 0; i < n; i++)
            hash[nums[i]].push_back(i);

        vector<vector<int>> dp(n, vector<int>(n));
        int sum = 0;
        for (int j = 2; j < n; j++)
        {
            for (int i = 1; i < j; i++)
            {
                long long a = (long long)2 * nums[i] - nums[j];
                if (hash.count(a))
                {
                    for (auto k : hash[a])
                        if (k < i)
                            dp[i][j] += dp[k][i] + 1;
                }
                sum += dp[i][j];
            }
        }

        return sum;
    }

    // 1
    int ret = 0, N;
    bool vis[16];
    int countArrangement(int n)
    {
        N = n;
        dfs(1);
        return ret;
    }

    void dfs(int pos)
    {
        if (pos == N + 1)
        {
            ret++;
            return;
        }

        for (int i = 1; i <= N; i++)
        {
            if (!vis[i] && (i % pos == 0 || pos % i == 0))
            {
                vis[i] = true;
                dfs(pos + 1);
                vis[i] = false;
            }
        }
    }

    // 2
    int findLengthOfLCIS(vector<int> &nums)
    {
        int ret = 0, n = nums.size();
        for (int i = 0; i < n;)
        {
            int j = i + 1;
            while (j < n && nums[j] > nums[j - 1])
                j++;
            ret = max(ret, j - i);
            i = j;
        }
        return ret;
    }

    // 3
    int subarraySum(vector<int> &nums, int k)
    {
        unordered_map<int, int> hash;
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
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    int memo[201][201];
    int longestIncreasingPath(vector<vector<int>> &matrix)
    {
        m = matrix.size(), n = matrix[0].size();

        int ret = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                ret = max(ret, 1 + dfs(matrix, i, j));

        return ret;
    }

    int dfs(vector<vector<int>> &matrix, int i, int j)
    {
        if (memo[i][j])
            return memo[i][j];

        int ret = 0;
        for (int k = 0; k < 4; k++)
        {
            int x = i + dx[k], y = j + dy[k];
            if (x >= 0 && x < m && y >= 0 && y < n && matrix[x][y] > matrix[i][j])
                ret = max(ret, 1 + dfs(matrix, x, y));
        }

        memo[i][j] = ret;
        return ret;
    }

    // 5
    vector<string> res;
    vector<string> binaryTreePaths(TreeNode *root)
    {
        dfs(root, "");
        return res;
    }

    void dfs(TreeNode *root, string path)
    {
        path += to_string(root->val);

        if (root->left == nullptr && root->right == nullptr)
        {
            res.push_back(path);
            return;
        }

        path += "->";
        if (root->left)
            dfs(root->left, path);
        if (root->right)
            dfs(root->right, path);
    }

    // 6
    vector<int> smallestK(vector<int> &arr, int k)
    {
        srand(time(nullptr));
        quickSort(arr, 0, arr.size() - 1, k);
        return {arr.begin(), arr.begin() + k};
    }

    int getRandom(vector<int> &nums, int left, int right)
    {
        int r = rand();
        return nums[r % (right - left + 1) + left];
    }

    void quickSort(vector<int> &nums, int l, int r, int k)
    {
        if (l >= r)
            return;

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

        int lRange = left - l + 1, mRange = (right - 1) - (left + 1) + 1;
        if (lRange >= k)
            quickSort(nums, l, left, k);
        else if (lRange + mRange >= k)
            return;
        else
            quickSort(nums, right, r, k - lRange - mRange);
    }

    // 7
    int jump(vector<int> &nums)
    {
        int left = 0, right = 0, maxPos = 0, ret = 0, n = nums.size();

        while (left <= right)
        {
            if (maxPos >= n - 1)
                return ret;

            for (int i = left; i <= right; i++)
                maxPos = max(maxPos, i + nums[i]);

            left = right + 1;
            right = maxPos;
            ret++;
        }

        return -1;
    }
};