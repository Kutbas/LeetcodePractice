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
    string changeStr(string s)
    {
        string ret;
        for (auto ch : s)
        {
            if (ch != '#')
                ret += ch;
            else if (ret.size())
                ret.pop_back();
        }
        return ret;
    }

    bool backspaceCompare(string s, string t)
    {
        return changeStr(s) == changeStr(t);
    }

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    void solve(vector<vector<char>> &board)
    {
        m = board.size(), n = board[0].size();

        for (int i = 0; i < m; i++)
        {
            if (board[i][0] == 'O')
                bfs(board, i, 0);
            if (board[i][n - 1] == 'O')
                bfs(board, i, n - 1);
        }

        for (int j = 0; j < n; j++)
        {
            if (board[0][j] == 'O')
                bfs(board, 0, j);
            if (board[m - 1][j] == 'O')
                bfs(board, m - 1, j);
        }

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (board[i][j] == 'O')
                    board[i][j] = 'X';
                else if (board[i][j] == '.')
                    board[i][j] = 'O';
            }
    }

    void bfs(vector<vector<char>> &board, int i, int j)
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
    vector<int> twoSum(vector<int> &nums, int target)
    {
        unordered_map<int, int> hash;
        // hash[0]=1;

        int sum = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            int x = target - nums[i];
            if (hash.count(x))
                return {i, hash[x]};
            hash[nums[i]] = i;
        }
        return {-1, -1};
    }

    int mySqrt(int x)
    {
        if (x <= 1)
            return x;
        int left = 1, right = x;
        while (left < right)
        {
            long long mid = left + (right - left + 1) / 2;
            if (mid * mid <= x)
                left = mid;
            else
                right = mid - 1;
        }
        return left;
    }

    int tmp[50010];
    int reversePairs(vector<int> &nums)
    {
        return mergeSort(nums, 0, nums.size() - 1);
    }

    int mergeSort(vector<int> &nums, int left, int right)
    {
        if (left >= right)
            return 0;

        int mid = left + (right - left) / 2;
        int ret = 0;
        ret += mergeSort(nums, left, mid);
        ret += mergeSort(nums, mid + 1, right);

        int i = 0, cur1 = left, cur2 = mid + 1;
        while (cur1 <= mid && cur2 <= right)
        {
            if (nums[cur1] <= nums[cur2])
                tmp[i++] = nums[cur2++];
            else
            {
                ret += right - cur2 + 1;
                tmp[i++] = nums[cur1++];
            }
        }
        while (cur1 <= mid)
            tmp[i++] = nums[cur1++];
        while (cur2 <= right)
            tmp[i++] = nums[cur2++];

        for (int j = left; j <= right; j++)
            nums[j] = tmp[j - left];
        return ret;
    }

    int tmp[50010];
    int reversePairs(vector<int> &nums)
    {
        return mergesort(nums, 0, nums.size() - 1);
    }

    int mergesort(vector<int> &nums, int left, int right)
    {
        if (left >= right)
            return 0;

        int mid = left + (right - left) / 2;
        int ret = 0;
        int i = 0, cur1 = left, cur2 = mid + 1;
        ret += mergesort(nums, left, mid);
        ret += mergesort(nums, mid + 1, right);

        while (cur1 <= mid)
        {
            while (cur2 <= right && nums[cur1] <= 2.0 * nums[cur2])
                cur2++;
            ret += right - cur2 + 1;
            cur1++;
        }

        cur1 = left, cur2 = mid + 1;
        while (cur1 <= mid && cur2 <= right)
            tmp[i++] = nums[cur1] <= nums[cur2] ? nums[cur2++] : nums[cur1++];
        while (cur1 <= mid)
            tmp[i++] = nums[cur1++];
        while (cur2 <= right)
            tmp[i++] = nums[cur2++];

        for (int j = left; j <= right; j++)
            nums[j] = tmp[j - left];

        return ret;
    }

    int ladderLength(string beginWord, string endWord, vector<string> &wordList)
    {
        unordered_set<string> hash(wordList.begin(), wordList.end());
        unordered_set<string> vis;

        if (!hash.count(endWord))
            return 0;

        queue<string> q;
        q.push(beginWord);
        vis.insert(beginWord);
        int ret = 1;

        while (q.size())
        {
            ret++;
            int sz = q.size();
            while (sz--)
            {
                string t = q.front();
                q.pop();
                for (int i = 0; i < t.size(); i++)
                {
                    string tmp = t;
                    for (char ch = 'a'; ch <= 'z'; ch++)
                    {
                        tmp[i] = ch;
                        if (hash.count(tmp) && !vis.count(tmp))
                        {
                            if (tmp == endWord)
                                return ret;
                            q.push(tmp);
                            vis.insert(tmp);
                        }
                    }
                }
            }
        }

        return ret;
    }

    int findMin(vector<int> &nums)
    {
        int n = nums.size();
        int left = 0, right = n - 1;
        while (left < right)
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] > nums[n - 1])
                left = mid + 1;
            else
                right = mid;
        }
        return nums[left];
    }

    bool CheckPermutation(string s1, string s2)
    {
        if (s1.size() != s2.size())
            return false;
        int hash[128] = {0};
        for (auto ch : s1)
            hash[ch]++;

        for (auto ch : s2)
            if (--hash[ch] < 0)
                return false;

        return true;
    }

    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        ListNode *head = new ListNode(0);
        ListNode *prev = head;
        ListNode *cur1 = l1, *cur2 = l2;

        int t = 0;
        while (t || cur1 || cur2)
        {
            if (cur1)
            {
                t += cur1->val;
                cur1 = cur1->next;
            }
            if (cur2)
            {
                t += cur2->val;
                cur2 = cur2->next;
            }
            prev->next = new ListNode(t % 10);
            prev = prev->next;
            t /= 10;
        }

        prev = head->next;
        delete head;
        return prev;
    }

    int ladderLength(string beginWord, string endWord, vector<string> &wordList)
    {
        unordered_set<string> hash(wordList.begin(), wordList.end());
        unordered_set<string> vis;

        if (!hash.count(endWord))
            return 0;

        queue<string> q;
        q.push(beginWord);
        vis.insert(beginWord);
        int ret = 1;

        while (q.size())
        {
            ret++;
            int sz = q.size();
            while (sz--)
            {
                string s = q.front();
                q.pop();
                for (int i = 0; i < s.size(); i++)
                {
                    string tmp = s;
                    for (char ch = 'a'; ch <= 'z'; ch++)
                    {
                        tmp[i] = ch;
                        if (!vis.count(tmp) && hash.count(tmp))
                        {
                            if (tmp == endWord)
                                return ret;
                            q.push(tmp);
                            vis.insert(tmp);
                        }
                    }
                }
            }
        }

        return 0;
    }

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    void solve(vector<vector<char>> &board)
    {
        m = board.size(), n = board[0].size();

        for (int i = 0; i < m; i++)
        {
            if (board[i][0] == 'O')
                BFS(board, i, 0);
            if (board[i][n - 1] == 'O')
                BFS(board, i, n - 1);
        }

        for (int j = 0; j < n; j++)
        {
            if (board[0][j] == 'O')
                BFS(board, 0, j);
            if (board[m - 1][j] == 'O')
                BFS(board, m - 1, j);
        }

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (board[i][j] == 'O')
                    board[i][j] = 'X';
                else if (board[i][j] == '.')
                    board[i][j] = 'O';
            }
    }

    void BFS(vector<vector<char>> &board, int i, int j)
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
};