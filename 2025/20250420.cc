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
    string longestPalindrome(string s)
    {
        int begin = 0, maxlen = 1, n = s.size();
        vector<vector<int>> dp(n, vector<int>(n));
        for (int i = 0; i < n; i++)
            dp[i][i] = true;

        for (int L = 2; L < n; L++)
        {
            for (int i = 0; i < n; i++)
            {
                int j = i + L - 1;
                if (j > n)
                    break;

                if (s[i] != s[j])
                    dp[i][j] = false;
                else
                {
                    if (L == 2)
                        dp[i][j] = true;
                    else
                        dp[i][j] = dp[i + 1][j - 1];
                }

                if (dp[i][j] && j - i + 1 > maxlen)
                {
                    maxlen = j - i + 1;
                    begin = i;
                }
            }
        }

        return s.substr(begin, maxlen);
    }

    vector<int> missingTwo(vector<int> &nums)
    {
        int xorsum = 0;
        for (auto n : nums)
            xorsum ^= n;
        for (int i = 1; i <= nums.size() + 2; i++)
            xorsum ^= i;

        int lsb = xorsum == INT_MIN ? xorsum : xorsum & (-xorsum);
        int x = 0, y = 0;

        for (auto n : nums)
        {
            if (lsb & n)
                x ^= n;
            else
                y ^= n;
        }

        for (int i = 1; i <= nums.size() + 2; i++)
        {
            if (lsb & i)
                x ^= i;
            else
                y ^= i;
        }

        return {x, y};
    }

    string longestPalindrome(string s)
    {
        int begin = 0, maxlen = 0, n = s.size();
        for (int i = 0; i < n; i++)
        {
            int left = i, right = i;
            while (left >= 0 && right < n && s[left] == s[right])
            {
                left--;
                right++;
            }
            int len = (right - 1) - (left + 1) + 1;
            if (len > maxlen)
            {
                begin = left + 1;
                maxlen = len;
            }

            left = i, right = i + 1;
            while (left >= 0 && right < n && s[left] == s[right])
            {
                left--;
                right++;
            }
            len = (right - 1) - (left + 1) + 1;
            if (len > maxlen)
            {
                begin = left + 1;
                maxlen = len;
            }
        }

        return s.substr(begin, maxlen);
    }

    string convert(string s, int numRows)
    {
        if (numRows == 1)
            return s;

        int n = s.size(), d = 2 * numRows - 2;
        string ret;
        for (int i = 0; i < n; i += d)
            ret += s[i];

        for (int k = 1; k < numRows - 1; k++)
            for (int i = k, j = d - k; i < n || j < n; i += d, j += d)
            {
                if (i < n)
                    ret += s[i];
                if (j < n)
                    ret += s[j];
            }

        for (int i = numRows - 1; i < n; i += d)
            ret += s[i];

        return ret;
    }

    bool isValid(string s)
    {
        stack<char> st;
        for (auto ch : s)
        {
            if (ch == '(' || ch == '[' || ch == '{')
                st.push(ch);
            else if (st.empty())
                return false;
            else
            {
                if (ch == ')' && st.top() != '(')
                    return false;
                else if (ch == ']' && st.top() != '[')
                    return false;
                else if (ch == '}' && st.top() != '{')
                    return false;
                else
                    st.pop();
            }
        }

        return st.empty();
    }

    string longestPalindrome(string s)
    {
        int begin = 0, maxlen = 1, n = s.size();
        for (int i = 0; i < n; i++)
        {
            int left = i, right = i;
            while (left >= 0 && right < n && s[left] == s[right])
            {
                left--;
                right++;
            }
            int len = (right - 1) - (left + 1) + 1;
            if (len > maxlen)
            {
                begin = left + 1;
                maxlen = len;
            }
            left = i, right = i + 1;
            while (left >= 0 && right < n && s[left] == s[right])
            {
                left--;
                right++;
            }
            len = (right - 1) - (left + 1) + 1;
            if (len > maxlen)
            {
                begin = left + 1;
                maxlen = len;
            }
        }

        return s.substr(begin, maxlen);
    }

    bool isPalindrome(string s)
    {
        string tmp;
        for (auto ch : s)
            if (isalnum(ch))
                tmp += tolower(ch);

        int left = 0, right = tmp.size() - 1;
        while (left <= right)
        {
            if (tmp[left] == tmp[right])
                left++, right--;
            else
                return false;
        }

        return true;
    }

    vector<int> singleNumber(vector<int> &nums)
    {
        int xorsum = 0;
        for (auto n : nums)
            xorsum ^= n;

        int lsb = xorsum == INT_MIN ? xorsum : xorsum & (-xorsum);
        int x = 0, y = 0;
        for (auto n : nums)
        {
            if (n & lsb)
                x ^= n;
            else
                y ^= n;
        }

        return {x, y};
    }

    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        ListNode *head = new ListNode(0);
        ListNode *prev = head;
        ListNode *cur1 = l1, *cur2 = l2;

        int t = 0;
        while (cur1 || cur2 || t)
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

    vector<vector<string>> groupAnagrams(vector<string> &strs)
    {
        vector<vector<string>> ret;
        unordered_map<string, vector<string>> hash;

        for (auto s : strs)
        {
            string tmp = s;
            sort(tmp.begin(), tmp.end());
            hash[tmp].push_back(s);
        }

        for (auto &[a, b] : hash)
            ret.push_back(b);

        return ret;
    }

    int lastStoneWeight(vector<int> &stones)
    {
        priority_queue<int> q;
        for (auto n : stones)
            q.push(n);

        while (q.size())
        {
            int x = q.top();
            q.pop();
            int y = q.top();
            q.pop();
            if (x != y)
                q.push(x - y);
        }

        return q.empty() ? 0 : q.top();
    }

    int ladderLength(string beginWord, string endWord, vector<string> &wordList)
    {
        unordered_set<string> hash(wordList.begin(), wordList.end());
        unordered_set<string> vis; // 标记已经搜索过的单词

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

    int m, n;
    int cutOffTree(vector<vector<int>> &f)
    {
        m = f.size(), n = f[0].size();
        // 找出砍树的顺序
        vector<pair<int, int>> trees;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (f[i][j] > 1)
                    trees.push_back({i, j});
            }

        sort(trees.begin(), trees.end(), [&](const pair<int, int> &p1, const pair<int, int> &p2)
             { return f[p1.first][p1.second] < f[p2.first][p2.second]; });

        // 按照顺序砍树
        int bx = 0, by = 0;
        int ret = 0;
        for (auto &[a, b] : trees)
        {
            int step = bfs(f, bx, by, a, b);
            if (step == -1)
                return -1;
            ret += step;
            bx = a, by = b;
        }
        return ret;
    }

    bool vis[51][51];
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int bfs(vector<vector<int>> &f, int bx, int by, int ex, int ey)
    {
        if (bx == ex && by == ey)
            return 0;

        queue<pair<int, int>> q;
        memset(vis, 0, sizeof vis); // 清空之前的遍历数组
        q.push({bx, by});
        vis[bx][by] = true;

        int step = 0;
        while (q.size())
        {
            step++;
            int sz = q.size();
            while (sz--)
            {
                auto [a, b] = q.front();
                q.pop();
                for (int i = 0; i < 4; i++)
                {
                    int x = a + dx[i], y = b + dy[i];
                    if (x >= 0 && x < m && y >= 0 && y < n && f[x][y] && !vis[x][y])
                    {
                        if (x == ex && y == ey)
                            return step;
                        q.push({x, y});
                        vis[x][y] = true;
                    }
                }
            }
        }
        return -1;
    }
};