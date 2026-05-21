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
    int tmp[50010];
    int reversePairs(vector<int> &record)
    {
        return mergeSort(record, 0, record.size() - 1);
    }

    int mergeSort(vector<int> &nums, int left, int right)
    {
        if (left >= right)
            return 0;

        int ret = 0, mid = left + (right - left) / 2;
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

    // 2
    unordered_map<char, int> in;
    unordered_map<char, unordered_set<char>> edges;
    bool check = false;
    string alienOrder(vector<string> &words)
    {
        int n = words.size();
        for (auto &word : words)
            for (auto ch : word)
                in[ch] = 0;

        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
            {
                add(words[i], words[j]);
                if (check)
                    return "";
            }

        queue<char> q;
        for (auto [a, b] : in)
            if (b == 0)
                q.push(a);

        string ret;
        while (q.size())
        {
            auto t = q.front();
            q.pop();
            ret += t;

            for (auto ch : edges[t])
                if (--in[ch] == 0)
                    q.push(ch);
        }

        for (auto [a, b] : in)
            if (b)
                return "";

        return ret;
    }

    void add(string &s1, string &s2)
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

    // 3
    int m, n;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    bool vis[7][7];
    bool exist(vector<vector<char>> &board, string word)
    {
        m = board.size(), n = board[0].size();

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (board[i][j] == word[0])
                {
                    vis[i][j] = true;
                    if (dfs(board, i, j, word, 1))
                        return true;
                    vis[i][j] = false;
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
            if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && board[x][y] == word[pos])
            {
                vis[x][y] = true;
                if (dfs(board, x, y, word, pos + 1))
                    return true;
                vis[x][y] = false;
            }
        }

        return false;
    }

    // 4
    int myAtoi(string str)
    {
        int n = str.size(), cur = 0, sign = 1;

        while (str[cur] == ' ')
            if (++cur == n)
                break;

        if (str[cur] == '+' || str[cur] == '-')
        {
            if (str[cur] == '-')
                sign = -1;
            cur++;
        }

        int ret = 0;
        for (int i = cur; i < n; i++)
        {
            if (!isdigit(str[i]))
                break;

            if (ret > (INT_MAX - (str[i] - '0')) / 10)
                return sign == 1 ? INT_MAX : INT_MIN;

            ret = ret * 10 + (str[i] - '0');
        }

        return ret * sign;
    }

    // 5
    string addStrings(string num1, string num2)
    {
        int m = num1.size(), n = num2.size();
        int t = 0, cur1 = m - 1, cur2 = n - 1;
        string ret;

        while (t || cur1 >= 0 || cur2 >= 0)
        {
            if (cur1 >= 0)
                t += num1[cur1--] - '0';
            if (cur2 >= 0)
                t += num2[cur2--] - '0';

            ret += to_string(t % 10);
            t /= 10;
        }

        reverse(ret.begin(), ret.end());
        return ret[0] == '0' ? "0" : ret;
    }

    // 6
    int FindGreatestSumOfSubArray(vector<int> &nums)
    {
        int n = nums.size(), ret = INT_MIN;
        vector<int> dp(n + 1);

        for (int i = 1; i <= n; i++)
        {
            dp[i] = max(dp[i - 1] + nums[i - 1], nums[i - 1]);
            ret = max(ret, dp[i]);
        }

        return ret;
    }

    // 7
    vector<int> intersection(vector<int> &nums1, vector<int> &nums2)
    {
        vector<int> ret;
        int hash[1001] = {0};

        for (auto n : nums1)
            if (hash[n] == 0)
                hash[n]++;
        for (auto n : nums2)
            if (--hash[n] == 0)
                ret.push_back(n);

        return ret;
    }
};