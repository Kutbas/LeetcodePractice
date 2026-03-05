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
    vector<vector<int>> ret;
    vector<int> path;
    vector<vector<int>> subsets(vector<int> &nums)
    {
        dfs(path, 0);
        return ret;
    }

    void dfs(vector<int> &nums, int pos)
    {
        ret.push_back(path);

        for (int i = pos; i < nums.size(); i++)
        {
            path.push_back(nums[i]);
            dfs(nums, i + 1);
            path.pop_back();
        }
    }

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    vector<vector<int>> updateMatrix(vector<vector<int>> &mat)
    {
        m = mat.size(), n = mat[0].size();
        vector<vector<int>> dist(m, vector<int>(n, -1));
        queue<pair<int, int>> q;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (mat[i][j] == 0)
                {
                    dist[i][j] = 0;
                    q.push({i, j});
                }

        while (q.size())
        {
            auto [a, b] = q.front();
            q.pop();
            for (int k = 0; k < 4; k++)
            {
                int x = a + dx[k], y = b + dy[k];
                if (x >= 0 && x < m && y >= 0 && y < n && dist[x][y] == -1)
                {
                    dist[x][y] = dist[a][b] + 1;
                    q.push({x, y});
                }
            }
        }

        return dist;
    }

    vector<int> smallestK(vector<int> &arr, int k)
    {
        srand(time(NULL));
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

    vector<vector<int>> generate(int numRows)
    {
        vector<vector<int>> ret(numRows);

        for (int i = 0; i < numRows; i++)
        {
            ret[i].resize(i + 1);
            ret[i][0] = ret[i][i] = 1;
            for (int j = 1; j < i + 1; j++)
                ret[i][j] = ret[i - 1][j - 1] + ret[i - 1][j];
        }

        return ret;
    }

    int sum;
    int path1;
    int subsetXORSum(vector<int> &nums)
    {
        dfs2(nums, 0);
        return sum;
    }

    void dfs2(vector<int> &nums, int pos)
    {
        sum += path1;

        for (int i = pos; i < nums.size(); i++)
        {
            path1 ^= nums[i];
            dfs2(nums, i + 1);
            path1 ^= nums[i];
        }
    }

    int findMaxLength(vector<int> &nums)
    {
        unordered_map<int, int> hash;
        hash[0] = -1;
        int ret = 0, sum = 0;

        for (int i = 0; i < nums.size(); i++)
        {
            sum += nums[i] == 0 ? -1 : 1;
            if (hash.count(sum))
                ret = max(ret, i - hash[sum]);
            else
                hash[sum] = i;
        }

        return ret;
    }

    int calculate(string s)
    {
        int ret = 0;
        vector<int> nums;
        char op = '+';
        for (int i = 0; i < s.size();)
        {
            int tmp = 0;

            if (s[i] != ' ')
                continue;

            if (isdigit(s[i]))
            {
                while (i < s.size() && isdigit(s[i]))
                    tmp = tmp * 10 + (s[i++] - '0');
            }
            else
                op = s[i];

            if (op == '+')
                nums.push_back(tmp);
            else if (op == '-')
                nums.push_back(-tmp);
            else if (op == '*')
                nums.back() *= tmp;
            else
                nums.back() /= tmp;
        }

        for (auto n : nums)
            ret += n;

        return ret;
    }

    vector<vector<int>> ret;
    vector<int> path;
    bool check[9] = {0};
    vector<vector<int>> permuteUnique(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        dfs(nums, 0);
        return ret;
    }

    void dfs(vector<int> &nums, int pos)
    {
        if (pos == nums.size())
        {
            ret.push_back(path);
            return;
        }

        for (int i = pos; i < nums.size(); i++)
        {
            // 剪枝
            if (check[i] || (i != 0 && nums[i] == nums[i - 1] && !check[i - 1]))
                continue;
            path.push_back(nums[i]);
            check[i] = true;
            dfs(nums, pos + 1);
            path.pop_back();
            check[i] = false;
        }
    }

    string hash[10] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    string path2;
    vector<string> ret2;
    vector<string> letterCombinations(string digits)
    {
        if (digits.empty())
            return ret2;
        dfs(digits, 0);
        return ret2;
    }

    void dfs(string &digits, int pos)
    {
        if (pos == digits.size())
        {
            ret2.push_back(path2);
            return;
        }

        for (auto ch : hash[digits[pos] - '0'])
        {
            path2.push_back(ch);
            dfs(digits, pos + 1);
            path2.pop_back();
        }
    }
};