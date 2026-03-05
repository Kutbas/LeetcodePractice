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
    bool validateStackSequences(vector<int> &pushed, vector<int> &popped)
    {
        int n = pushed.size(), i = 0;
        stack<int> st;

        for (auto num : pushed)
        {
            st.push(num);

            while (st.size() && st.top() == popped[i])
            {
                st.pop();
                i++;
            }
        }

        return i == n;
    }

    // 2
    int brokenCalc(int startValue, int target)
    {
        int ret = 0;
        while (target > startValue)
        {
            if (target % 2 == 0)
                target /= 2;
            else
                target++;
            ret++;
        }
        return ret + startValue - target;
    }

    // 3
    int firstUniqChar(string s)
    {
        unordered_map<char, int> hash;
        for (char ch : s)
            hash[ch]++;

        for (int i = 0; i < s.size(); i++)
            if (hash[s[i]] == 1)
                return i;
        return -1;
    }

    // 4
    int m, n;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    bool vis[7][7] = {0};
    bool exist(vector<vector<char>> &board, string word)
    {
        m = board.size(), n = board[0].size();

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (board[i][j] == word[0])
                {
                    vis[i][j] = true;
                    if (dfs(board, word, 1, i, j))
                        return true;
                    vis[i][j] = false;
                }
            }

        return false;
    }

    bool dfs(vector<vector<char>> &board, string &word, int pos, int i, int j)
    {
        if (pos == word.size())
            return true;

        for (int k = 0; k < 4; k++)
        {
            int x = i + dx[k], y = j + dy[k];
            if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && board[x][y] == word[pos])
            {
                vis[x][y] = true;
                if (dfs(board, word, pos + 1, x, y))
                    return true;
                vis[x][y] = false;
            }
        }

        return false;
    }

    // 5
    vector<vector<int>> ret;
    vector<int> path;
    int aim;
    vector<vector<int>> combinationSum(vector<int> &candidates, int target)
    {
        aim = target;
        dfs(candidates, 0, 0);
        return ret;
    }

    void dfs(vector<int> &nums, int pos, int sum)
    {
        if (sum > aim)
            return;

        if (sum == aim)
        {
            ret.push_back(path);
            return;
        }

        for (int i = pos; i < nums.size(); i++)
        {
            path.push_back(nums[i]);
            dfs(nums, i, sum + nums[i]);
            path.pop_back();
        }
    }

    // 6
    int massage(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 0)
            return 0;

        vector<int> f(n), g(n);
        f[0] = nums[0];

        for (int i = 1; i < nums.size(); i++)
        {
            f[i] = g[i - 1] + nums[i];
            g[i] = max(f[i - 1], g[i - 1]);
        }

        return max(f[n - 1], g[n - 1]);
    }

    // 7
    int lengthOfLIS(vector<int> &nums)
    {
        vector<int> ret;
        ret.push_back(nums[0]);

        for (int i = 1; i < nums.size(); i++)
        {
            if (nums[i] > ret.back())
                ret.push_back(nums[i]);
            else
            {
                int left = 0, right = ret.size() - 1;
                while (left < right)
                {
                    int mid = left + (right - left) / 2;
                    if (nums[i] > ret[mid])
                        left = mid + 1;
                    else
                        right = mid;
                }
                ret[left] = nums[i];
            }
        }

        return ret.size();
    }
};