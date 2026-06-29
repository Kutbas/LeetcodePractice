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
    unordered_map<char, int> in;
    unordered_map<char, unordered_set<char>> edges;
    bool check = false;
    string alienOrder(vector<string> &words)
    {
        for (auto &word : words)
            for (auto &ch : word)
                in[ch] = 0;

        int n = words.size();
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
            {
                add(words[i], words[j]);
                if (check)
                    return "";
            }

        queue<char> q;
        string ret;

        for (auto [a, b] : in)
            if (b == 0)
                q.push(a);

        while (q.size())
        {
            auto t = q.front();
            q.pop();
            ret += t;

            for (auto a : edges[t])
                if (--in[a] == 0)
                    q.push(a);
        }

        for (auto [a, b] : in)
            if (b)
                return "";

        return ret;
    }

    void add(const string &s1, const string &s2)
    {
        int n = min(s1.size(), s2.size()), i = 0;

        for (; i < n; i++)
        {
            if (s1[i] != s2[i])
            {
                char a = s1[i], b = s2[i];
                if (!edges.count(a) || !edges[a].count(b))
                {
                    in[b]++;
                    edges[a].insert(b);
                }
                break;
            }
        }

        if (i < s1.size() && i == s2.size())
            check = true;
    }

    // 2
    bool validateStackSequences(vector<int> &pushed, vector<int> &popped)
    {
        stack<int> st;
        int n = pushed.size(), i = 0;

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

    // 3
    int maxArea(vector<int> &height)
    {
        int n = height.size(), ret = 0;

        int left = 0, right = n - 1;
        while (left < right)
        {
            int v = (right - left) * min(height[left], height[right]);
            ret = max(ret, v);

            if (height[left] < height[right])
                left++;
            else
                right--;
        }

        return ret;
    }

    // 4
    int m, n;
    int dx[8] = {0, 0, 1, -1, 1, 1, -1, -1};
    int dy[8] = {1, -1, 0, 0, 1, -1, 1, -1};
    vector<vector<char>> updateBoard(vector<vector<char>> &board,
                                     vector<int> &click)
    {
        m = board.size(), n = board[0].size();

        int bx = click[0], by = click[1];
        if (board[bx][by] == 'M')
            board[bx][by] = 'X';
        else
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

    // 5
    int memo[201][201];
    int getMoneyAmount(int n)
    {
        return dfs(1, n);
    }

    int dfs(int left, int right)
    {
        if (left >= right)
            return 0;

        if (memo[left][right])
            return memo[left][right];

        int ret = INT_MAX;
        for (int head = left; head <= right; head++)
        {
            int tmp1 = dfs(left, head - 1);
            int tmp2 = dfs(head + 1, right);
            ret = min(ret, head + max(tmp1, tmp2));
        }

        memo[left][right] = ret;
        return ret;
    }

    // 6
    ListNode *swapPairs(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *tmp = swapPairs(head->next->next);
        ListNode *newhead = head->next;
        newhead->next = head;
        head->next = tmp;

        return newhead;
    }

    // 7
    vector<vector<int>> ret;
    vector<int> path;
    bool vis[9] = {0};
    vector<vector<int>> permuteUnique(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
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
            if (vis[i] || (i != 0 && nums[i - 1] == nums[i] && !vis[i - 1]))
                continue;

            vis[i] = true;
            path.push_back(nums[i]);
            dfs(nums);
            path.pop_back();
            vis[i] = false;
        }
    }

    // 8
    vector<vector<int>> merge(vector<vector<int>> &intervals)
    {
        sort(intervals.begin(), intervals.end());

        int n = intervals.size(), left = intervals[0][0],
            right = intervals[0][1];
        vector<vector<int>> ret;

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

    // 9
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

    // 10
    int deleteAndEarn(vector<int> &nums)
    {
        const int N = 10001;
        int arr[N] = {0};

        for (auto n : nums)
            arr[n] += n;

        vector<int> f(N), g(N);
        for (int i = 1; i < N; i++)
        {
            f[i] = g[i - 1] + arr[i];
            g[i] = max(f[i - 1], g[i - 1]);
        }

        return max(f[N - 1], g[N - 1]);
    }
};