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
    // 1
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    void solve(vector<vector<char>> &board)
    {
        m = board.size(), n = board[0].size();

        for (int i = 0; i < m; i++)
        {
            if (board[i][0] == 'O')
                dfs(board, i, 0);
            if (board[i][n - 1] == 'O')
                dfs(board, i, n - 1);
        }

        for (int i = 0; i < n; i++)
        {
            if (board[0][i] == 'O')
                dfs(board, 0, i);
            if (board[m - 1][i] == 'O')
                dfs(board, m - 1, i);
        }

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (board[i][j] == 'O')
                    board[i][j] = 'X';
                else if (board[i][j] == '.')
                    board[i][j] = 'O';
    }

    void dfs(vector<vector<char>> &board, int i, int j)
    {
        queue<pair<int, int>> q;
        q.push({i, j});
        board[i][j] = '.';

        while (q.size())
        {
            auto [a, b] = q.front();
            q.pop();

            for (int k = 0; k < 4; k++)
            {
                int x = a + dx[k], y = b + dy[k];
                if (x >= 0 && x < m && y >= 0 && y < n && board[x][y] == 'O')
                {
                    q.push({x, y});
                    board[x][y] = '.';
                }
            }
        }
    }

    // 2
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
        for (auto n : nums1)
        {
            if (n > nums2[index2[left]])
                ret[index2[left++]] = n;
            else
                ret[index2[right--]] = n;
        }

        return ret;
    }

    // 3
    int lengthOfLongestSubstring(string s)
    {
        int n = s.size(), ret = 0;
        int hash[128] = {0};

        for (int left = 0, right = 0; right < n; right++)
        {
            char in = s[right];
            ++hash[in];
            while (hash[in] > 1)
            {
                char out = s[left++];
                --hash[out];
            }
            ret = max(ret, right - left + 1);
        }

        return ret;
    }

    // 4
    string longestCommonPrefix(vector<string> &strs)
    {
        for (int i = 0; i < strs[0].size(); i++)
            for (int j = 1; j < strs.size(); j++)
                if (i == strs[j].size() || strs[0][i] != strs[j][i])
                    return strs[0].substr(0, i);
        return strs[0];
    }

    // 5
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost)
    {
        int n = gas.size();

        for (int i = 0; i < n; i++)
        {
            int rest = 0, step = 0;
            for (; step < n; step++)
            {
                int index = (i + step) % n;
                rest += gas[index] - cost[index];
                if (rest < 0)
                    break;
            }

            if (rest >= 0)
                return i;

            i = i + step;
        }
        return -1;
    }

    // 6
    int jump(vector<int> &nums)
    {
        int n = nums.size(), ret = 0, cur = 0, far = 0;

        for (int i = 0; i < n - 1; i++)
        {
            far = max(far, i + nums[i]);

            if (i == cur)
            {
                cur = far;
                ret++;

                if (cur >= n - 1)
                    break;
            }
        }

        return ret;
    }

    // 7
    int hammingDistance(int x, int y)
    {
        int ret = 0;
        for (int i = 0; i < 32; i++)
        {
            int bitX = (x >> i) & 1;
            int bitY = (y >> i) & 1;
            if (bitX != bitY)
                ret++;
        }
        return ret;
    }
};