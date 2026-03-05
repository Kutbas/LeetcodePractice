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
    string countAndSay(int n)
    {
        string ret = "1";
        for (int i = 1; i < n; i++)
        {
            string tmp;
            int len = ret.size();
            for (int left = 0, right = 0; right < len;)
            {
                while (right < len && ret[left] == ret[right])
                    right++;
                tmp += to_string(right - left) + ret[left];
                left = right;
            }
            ret = tmp;
        }

        return ret;
    }

    int triangleNumber(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        int ret = 0;
        int n = nums.size();
        for (int i = n - 1; i >= 2; i--)
        {
            int left = 0, right = i - 1;
            while (left < right)
            {
                if (nums[left] + nums[right] > nums[i])
                {
                    ret += right - left;
                    right--;
                }
                else
                    left++;
            }
        }

        return ret;
    }

    string longestPalindrome(string s)
    {
        int n = s.size(), begin = 0, maxlen = 1;
        for (int i = 0; i < n; i++)
        {
            int left = i, right = i;
            while (left >= 0 && right < n && s[left] == s[right])
                left--, right++;

            int len = (right - 1) - (left + 1) + 1;
            if (len > maxlen)
            {
                maxlen = len;
                begin = left + 1;
            }

            left = i, right = i + 1;
            while (left >= 0 && right < n && s[left] == s[right])
                left--, right++;
            len = (right - 1) - (left + 1) + 1;
            if (len > maxlen)
            {
                maxlen = len;
                begin = left + 1;
            }
        }

        return s.substr(begin, maxlen);
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

    vector<vector<int>> zigzagLevelOrder(TreeNode *root)
    {
        vector<vector<int>> ret;
        if (root == nullptr)
            return ret;
        queue<TreeNode *> q;
        q.push(root);
        int level = 1;

        while (q.size())
        {
            int sz = q.size();

            vector<int> tmp;
            while (sz--)
            {
                auto t = q.front();
                q.pop();

                tmp.push_back(t->val);
                if (t->left)
                    q.push(t->left);
                if (t->right)
                    q.push(t->right);
            }

            if (level % 2 == 0)
            {
                reverse(tmp.begin(), tmp.end());
            }

            ret.push_back(tmp);
            level++;
        }

        return ret;
    }

    int lastStoneWeight(vector<int> &stones)
    {
        priority_queue<int> q;
        for (auto n : stones)
            q.push(n);

        while (q.size() > 1)
        {
            int x = q.top();
            q.pop();
            int y = q.top();
            q.pop();
            if (x != y)
                q.push(x - y);
        }
        return q.top();
    }

    bool validateStackSequences(vector<int> &pushed, vector<int> &popped)
    {
        int i = 0, n = popped.size();
        stack<int> st;

        for (auto num : pushed)
        {
            st.push(num);
            while (!st.empty() && st.top() == popped[i])
            {
                st.pop();
                i++;
            }
        }

        return i == n;
    }

    int findKthLargest(vector<int> &nums, int k)
    {
        srand(time(NULL));
        return quickSort(nums, 0, nums.size() - 1, k);
    }

    int getRandom(vector<int> &nums, int left, int right)
    {
        int r = rand();
        return nums[r % (right - left + 1) + left];
    }

    int quickSort(vector<int> &nums, int l, int r, int k)
    {
        if (l >= r)
            return nums[l];

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

        int rRange = r - right + 1, mRange = (right - 1) - (left + 1) + 1;
        if (rRange >= k)
            return quickSort(nums, right, r, k);
        else if (rRange + mRange >= k)
            return key;
        else
            return quickSort(nums, l, left, k - rRange - mRange);
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

        int ret = 0;
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

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int maxDistance(vector<vector<int>> &grid)
    {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dist(m, vector<int>(n, -1));
        queue<pair<int, int>> q;

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j])
                {
                    dist[i][j] = 0;
                    q.push({i, j});
                }

        int ret = -1;
        while (q.size())
        {
            auto [a, b] = q.front();
            q.pop();
            for (int i = 0; i < 4; i++)
            {
                int x = a + dx[i], y = b + dy[i];
                if (x >= 0 && x < m && y >= 0 && y < n && dist[x][y] == -1)
                {
                    dist[x][y] = dist[a][b] + 1;
                    q.push({x, y});
                    ret = max(ret, dist[x][y]);
                }
            }
        }

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
            string t = q.front();
            q.pop();

            while (sz--)
            {
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

    bool canFinish(int n, vector<vector<int>> &prerequisites)
    {
        // 准备工作
        unordered_map<int, vector<int>> edges; // 邻接表存图
        vector<int> in(n);                     // 标记每个顶点的入度

        // 建图
        for (auto &e : prerequisites)
        {
            int a = e[0], b = e[1]; // b指向a的一条边
            edges[b].push_back(a);

            in[a]++;
        }

        // 拓扑排序
        // 把所有入度为0的点加入队列
        queue<int> q;
        for (int i = 0; i < n; i++)
            if (in[i] == 0)
                q.push(i);

        // BFS
        while (q.size())
        {
            int t = q.front();
            q.pop();

            for (int a : edges[t])
            {
                if (--in[a] == 0)
                    q.push(a);
            }
        }

        // 判断是否有环
        for (int i = 0; i < n; i++)
            if (in[i])
                return false;
        return true;
    }
};