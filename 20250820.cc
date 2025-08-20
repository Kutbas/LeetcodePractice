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
    int eraseOverlapIntervals(vector<vector<int>> &intervals)
    {
        sort(intervals.begin(), intervals.end());

        int ret = 0;
        int left = intervals[0][0], right = intervals[0][1];

        for (int i = 1; i < intervals.size(); i++)
        {
            int a = intervals[i][0], b = intervals[i][1];
            if (a < right)
            {
                ret++; // 删掉一个区间
                right = min(right, b);
            }
            else
                right = b;
        }

        return ret;
    }

    // 1
    vector<string> ret;
    vector<string> binaryTreePaths(TreeNode *root)
    {
        dfs(root, "");
        return ret;
    }

    void dfs(TreeNode *root, string path)
    {
        path += to_string(root->val);

        if (root->left == nullptr && root->right == nullptr)
        {
            ret.push_back(path);
            return;
        }

        path += "->";
        if (root->left)
            dfs(root->left, path);
        if (root->right)
            dfs(root->right, path);
    }

    // 2
    string decodeString(string s)
    {
        stack<string> st;
        stack<int> nums;
        string tmp = "";
        int k = 0;

        for (char ch : s)
        {
            if (isdigit(ch))
                k = k * 10 + ch - '0';
            else if (ch == '[')
            {
                nums.push(k);
                k = 0;
                st.push(tmp);
                tmp = "";
            }
            else if (ch == ']')
            {
                int n = nums.top();
                nums.pop();
                string ret = st.top();
                st.pop();
                while (n--)
                    ret += tmp;
                tmp = ret;
            }
            else
                tmp += ch;
        }

        return st.top();
    }

    // 3
    int cnt;
    int res = 0;
    int kthSmallest(TreeNode *root, int k)
    {
        cnt = k;
        dfs(root);
        return res;
    }

    void dfs(TreeNode *root)
    {
        if (root->left)
            dfs(root->left);

        if (--cnt == 0)
        {
            res = root->val;
            return;
        }

        if (root->right)
            dfs(root->right);
    }

    // 4
    int longestOnes(vector<int> &nums, int k)
    {
        int ret = 0;

        for (int left = 0, right = 0, tmp = 0; right < nums.size(); right++)
        {
            if (nums[right] == 0)
                tmp++;
            while (tmp > k)
                if (nums[left++] == 0)
                    tmp--;
            ret = max(ret, right - left + 1);
        }

        return ret;
    }

    // 5
    ListNode *reverseList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *ret = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;

        return ret;
    }

    // 6
    int Ret = 0, m, n;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
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

        return Ret;
    }

    void dfs(vector<vector<int>> &grid, int i, int j, int sum)
    {
        Ret = max(Ret, sum);

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
};