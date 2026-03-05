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
    bool evaluateTree(TreeNode *root)
    {
        if (root->left == nullptr && root->right == nullptr)
            return root->val == 0 ? false : true;

        bool left = evaluateTree(root->left);
        bool right = evaluateTree(root->right);

        return root->val == 2 ? left | right : left & right;
    }

    // 2
    int N;
    double myPow(double x, int n)
    {
        N = n;
        if (N < 0)
        {
            x = 1 / x;
            N = -N;
        }
        return pow(x, N);
    }

    double pow(double x, int n)
    {
        if (n == 0)
            return 1;

        double tmp = pow(x, n / 2);
        return n % 2 == 0 ? tmp * tmp : tmp * tmp * x;
    }

    // 3
    vector<vector<int>> ret;
    vector<int> path;
    int N, K;
    bool vis[21];
    vector<vector<int>> combine(int n, int k)
    {
        N = n, K = k;
        dfs(1);
        return ret;
    }

    void dfs(int pos)
    {
        if (path.size() == K)
        {
            ret.push_back(path);
            return;
        }

        for (int i = pos; i <= N; i++)
        {
            if (!vis[i])
            {
                vis[i] = true;
                path.push_back(i);
                dfs(pos + 1);
                path.pop_back();
                vis[i] = false;
            }
        }
    }

    // 4
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    bool check[7][7];
    bool exist(vector<vector<char>> &board, string word)
    {
        m = board.size(), n = board[0].size();
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (board[i][j] == word[0])
                {
                    check[i][j] = true;
                    if (dfs(board, i, j, word, 1))
                        return true;
                    else
                        check[i][j] = false;
                }
            }
        return false;
    }

    bool dfs(vector<vector<char>> &board, int i, int j, string &word, int pos)
    {
        if (pos == word.size())
            return true;

        for (int k = 0; k < 4; k++)
        {
            int x = i + dx[k], y = j + dy[k];
            if (x >= 0 && x < m && y >= 0 && y < n && !check[x][y] &&
                board[x][y] == word[pos])
            {
                check[x][y] = true;
                if (dfs(board, x, y, word, pos + 1))
                    return true;
                check[x][y] = false;
            }
        }

        return false;
    }

    // 5
    vector<int> findAnagrams(string s, string p)
    {
        int hash1[128], hash2[128];
        int m = p.size();
        vector<int> ret;
        for (auto ch : p)
            hash1[ch]++;

        for (int left = 0, right = 0, count = 0; right < s.size(); right++)
        {
            char in = s[right];
            if (++hash2[in] <= hash1[in])
                count++;
            while (right - left + 1 > m)
            {
                char out = s[left++];
                if (hash2[out]-- <= hash1[out])
                    count--;
            }
            if (count == m)
                ret.push_back(left);
        }

        return ret;
    }

    // 6
    vector<int> res;
    vector<int> tmp;
    vector<int> index;
    vector<int> tmpIndex;
    vector<int> countSmaller(vector<int> &nums)
    {
        int n = nums.size();
        res.resize(n);
        tmp.resize(n);
        index.resize(n);
        tmpIndex.resize(n);

        for (int i = 0; i < nums.size(); i++)
            index[i] = i;

        mergeSort(nums, 0, nums.size() - 1);
        return res;
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
                res[index[cur1]] += right - cur2 + 1;
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