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
    int findContentChildren(vector<int> &g, vector<int> &s)
    {
        sort(g.begin(), g.end());
        int ret = 0, m = g.size(), n = s.size();

        for (int i = 0, j = 0; i < m && j < n; i++, j++)
        {
            while (j < n && s[j] < s[i])
                j++;
            if (j < n)
                ret++;
        }

        return ret;
    }

    string optimalDivision(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 1)
            return to_string(nums[0]);
        if (n == 2)
            return to_string(nums[0]) + "/" + to_string(nums[1]);

        string ret = to_string(nums[0]) + "/" + to_string(nums[1]);
        for (int i = 2; i < n; i++)
        {
            ret += "/" + to_string(nums[i]);
        }
        ret += ")";

        return ret;
    }

    // 1
    int longestOnes(vector<int> &nums, int k)
    {
        int ret = 0;
        for (int left = 0, right = 0, count = 0; right < nums.size(); right++)
        {
            if (nums[right] == 0)
                count++;
            while (count > k)
                if (nums[left++] == 0)
                    count--;
            ret = max(ret, right - left + 1);
        }
        return ret;
    }

    // 2
    struct cmp
    {
        bool operator()(const ListNode *l1, const ListNode *l2)
        {
            return l1->val > l2->val;
        }
    };

    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        priority_queue<ListNode *, vector<ListNode *>, cmp> q;
        for (auto &list : lists)
            if (list)
                q.push(list);

        ListNode *ret = new ListNode(0);
        ListNode *prev = ret;

        while (q.size())
        {
            auto t = q.top();
            q.pop();

            prev->next = t;
            prev = prev->next;

            if (t->next)
                q.push(t->next);
        }

        prev = ret->next;
        delete ret;
        return prev;
    }

    // 4
    int wiggleMaxLength(vector<int> &nums)
    {
        int n = nums.size();
        int left = 0, ret = 0;

        for (int i = 1; i < n; i++)
        {
            int right = nums[i] - nums[i - 1];
            if (left * right == 0)
                continue;
            if (left * right < 0)
                ret++;
            left = right;
        }

        return ret + 1;
    }

    // 5
    void duplicateZeros(vector<int> &arr)
    {
        int n = arr.size(), cur = 0, dest = -1;
        while (cur < n)
        {
            if (arr[cur])
                dest++;
            else
                dest += 2;
            if (dest >= n - 1)
                break;
            cur++;
        }

        if (dest == n)
        {
            arr[n - 1] = 0;
            cur--;
            dest -= 2;
        }

        while (cur >= 0)
        {
            if (arr[cur])
                arr[dest--] = arr[cur--];
            else
            {
                arr[dest--] = 0;
                arr[dest--] = 0;
                cur--;
            }
        }
    }

    // 6
    ListNode *reverseList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *ret = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;

        return ret;
    }

    // 7
    bool row[9][10];
    bool col[9][10];
    bool grid[3][3][10];
    int m, n;
    void solveSudoku(vector<vector<char>> &board)
    {
        m = board.size(), n = board[0].size();
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (board[i][j] != '.')
                {
                    int num = board[i][j] - '0';
                    row[i][num] = col[j][num] = grid[i / 3][j / 3][num] = true;
                }

        dfs(board);
    }

    bool dfs(vector<vector<char>> &board)
    {
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (board[i][j] == '.')
                {
                    for (int num = 1; num <= 9; num++)
                    {
                        if (!row[i][num] && !col[j][num] && !grid[i / 3][j / 3][num])
                        {
                            row[i][num] = col[j][num] = grid[i / 3][j / 3][num] = true;
                            board[i][j] = num + '.';
                            if (dfs(board))
                                return true;
                            else
                            {
                                row[i][num] = col[j][num] = grid[i / 3][j / 3][num] = false;
                                board[i][j] = '.';
                            }
                        }
                    }
                    return false;
                }

        return true;
    }
};

// 3
int main()
{
    int n, m, q;
    cin >> n >> m >> q;

    vector<vector<int>> nums(n, vector<int>(m));
    vector<vector<int>> dp(n, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> nums[i][j];

    for (int i = 1; i < n; i++)
        for (int j = 1; j < m; j++)
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1] + nums[i - 1][j - 1];

    int x1, y1, x2, y2;
    while (q--)
    {
        cin >> x1 >> y1 >> x2 >> y2;
        cout << dp[x2][y2] - dp[x1 - 1][y2] - dp[x2][y1 - 1] + dp[x1 - 1][y1 - 1] << endl;
    }

    return 0;
}