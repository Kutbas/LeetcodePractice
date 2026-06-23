#include <mutex>
#include <vector>
#include <algorithm>
#include <climits>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
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
    int m, n;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int ret = 0, step = 0;
    bool vis[21][21] = {0};
    int uniquePathsIII(vector<vector<int>> &grid)
    {
        m = grid.size(), n = grid[0].size();

        int bx = 0, by = 0;
        step += 2;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == 0)
                    step++;
                else if (grid[i][j] == 1)
                    bx = i, by = j;
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
            if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && grid[x][y] != -1)
            {
                vis[x][y] = true;
                dfs(grid, x, y, count + 1);
                vis[x][y] = false;
            }
        }
    }

    // 2
    int K;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    bool vis[101][101] = {0};
    int wardrobeFinishing(int m, int n, int cnt)
    {
        K = cnt;

        queue<pair<int, int>> q;
        q.push({0, 0});
        vis[0][0] = true;
        int ret = 1;

        while (q.size())
        {
            auto [a, b] = q.front();
            q.pop();
            for (int k = 0; k < 4; k++)
            {
                int x = a + dx[k], y = b + dy[k];
                if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && Check(x, y))
                {
                    q.push({x, y});
                    vis[x][y] = true;
                    ret++;
                }
            }
        }

        return ret;
    }

    bool Check(int i, int j)
    {
        int tmp = 0;

        while (i || j)
        {
            tmp += i % 10;
            i /= 10;

            tmp += j % 10;
            j /= 10;
        }

        return tmp <= K;
    }

    // 3
    int longestPalindrome(string s)
    {
        int hash[128] = {0};

        for (char ch : s)
            hash[ch]++;

        int ret = 0;
        for (int i : hash)
            ret += i / 2 * 2;

        return ret < s.size() ? ret + 1 : ret;
    }

    // 4
    vector<vector<int>> merge(vector<vector<int>> &intervals)
    {
        sort(intervals.begin(), intervals.end());

        vector<vector<int>> ret;
        int n = intervals.size(), left = intervals[0][0], right = intervals[0][1];

        for (int i = 1; i < n; i++)
        {
            int a = intervals[i][0], b = intervals[i][1];
            if (a <= right)
                right = max(right, b);
            else
            {
                ret.push_back({left, right});
                left = a;
                right = b;
            }
        }

        ret.push_back({left, right});

        return ret;
    }
};

// 5
class MinStack
{
private:
    stack<long> st;
    long minVal;

public:
    MinStack()
    {
    }

    void push(int value)
    {
        if (st.empty())
        {
            st.push(0);
            minVal = value;
        }
        else
        {
            long diff = value - minVal;

            if (diff < 0)
                minVal = value;

            st.push(diff);
        }
    }

    void pop()
    {
        long diff = st.top();
        st.pop();

        if (diff < 0)
            minVal = minVal - diff;
    }

    int top()
    {
        long diff = st.top();

        if (diff > 0)
            return minVal + diff;

        return minVal;
    }

    int getMin()
    {
        return minVal;
    }
};