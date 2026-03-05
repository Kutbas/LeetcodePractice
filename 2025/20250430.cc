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
    int findMaxLength(vector<int> &nums)
    {
        unordered_map<int, int> hash;
        hash[0] = -1;

        int sum = 0, ret = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            sum += nums[i] == 0 ? -1 : 1;
            if (hash.count(sum))
                ret = max(ret, i - hash[sum]);
            else
                hash[sum] = i;
        }
        return ret;
    }

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    bool vis[51][51];
    int m, n;
    vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int color)
    {
        int m = image.size(), n = image[0].size();
        BFS(image, sr, sc, color);
        return image;
    }

    void BFS(vector<vector<int>> &image, int i, int j, int color)
    {
        int origin = image[i][j];
        queue<pair<int, int>> q;
        q.push({i, j});
        vis[i][j] = true;
        image[i][j] = color;

        while (q.size())
        {
            int sz = q.size();
            while (sz--)
            {
                auto [a, b] = q.front();
                q.pop();
                for (int k = 0; k < 4; k++)
                {
                    int x = a + dx[k], y = b + dy[k];
                    if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && image[x][y] == origin)
                    {
                        q.push({x, y});
                        vis[x][y] = true;
                        image[x][y] = color;
                    }
                }
            }
        }
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
            q.push(x - y);
        }

        return q.top();
    }

    unordered_map<char, unordered_set<char>> edges;
    unordered_map<char, int> in;
    bool check;
    string alienOrder(vector<string> &words)
    {
        int m = words.size();
        for (auto s : words)
            for (auto ch : s)
                in[ch] = 0;

        for (int i = 0; i < m; i++)
            for (int j = i + 1; j < m; j++)
            {
                add(words[i], words[j]);
                if (check)
                    return "";
            }

        string ret;
        queue<char> q;
        for (auto &[a, b] : in)
            if (b == 0)
                q.push(a);

        while (q.size())
        {
            int sz = q.size();
            while (sz--)
            {
                char t = q.front();
                q.pop();
                ret += t;

                for (auto a : edges[t])
                    if (--in[a] == 0)
                        q.push(a);
            }
        }

        for (auto &[a, b] : in)
            if (b != 0)
                return "";

        return ret;
    }

    void add(string &s1, string &s2)
    {
        int n = min(s1.size(), s2.size());
        int i = 0;

        for (int i = 0; i < n; i++)
        {
            if (s1[i] != s2[i])
            {
                int a = s1[i], b = s2[i];
                if (!edges.count(a) || !edges[a].count(b))
                {
                    edges[a].insert(b);
                    in[b]++;
                }

                break;
            }
        }

        if (i == s2.size() && i < s1.size())
            check = true;

        return;
    }

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    int origin;
    vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int color)
    {
        origin = image[sr][sc];
        if (origin == color)
            return image;

        m = image.size(), n = image[0].size();

        BFS(image, sr, sc, color);

        return image;
    }

    void BFS(vector<vector<int>> &image, int i, int j, int color)
    {
        queue<pair<int, int>> q;
        q.push({i, j});
        image[i][j] = color;

        while (q.size())
        {
            int sz = q.size();
            while (sz--)
            {
                auto [a, b] = q.front();
                q.pop();
                for (int k = 0; k < 4; k++)
                {
                    int x = a + dx[k], y = b + dy[k];
                    if (x >= 0 && x < m && y >= 0 && y < n && image[x][y] == origin)
                    {
                        q.push({x, y});
                        image[x][y] = color;
                    }
                }
            }
        }
        return;
    }

    vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
    {
        vector<vector<int>> edges(numCourses);
        vector<int> in(numCourses);
        vector<int> ret;

        for (auto &v : prerequisites)
        {
            int a = v[0], b = v[1];
            edges[b].push_back(a);
            in[a]++;
        }

        queue<int> q;
        for (int i = 0; i < numCourses; i++)
            if (in[i] == 0)
                q.push(i);

        while (q.size())
        {
            auto t = q.front();
            q.pop();
            ret.push_back(t);

            for (auto a : edges[t])
                if (--in[a] == 0)
                    q.push(a);
        }

        return ret;
    }

    int subarraysDivByK(vector<int> &nums, int k)
    {
        unordered_map<int, int> hash;
        hash[0] = 1;

        int sum = 0, ret = 0;

        for (auto n : nums)
        {
            sum += n;
            int r = (sum % k + k) % k;
            if (hash.count(r))
                ret += hash[r];
            hash[sum]++;
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
            int sz = q.size();
            while (sz--)
            {
                auto t = q.front();
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
                            ret++;
                        }
                    }
                }
            }
        }

        return 0;
    }

    int subarraySum(vector<int> &nums, int k)
    {
        unordered_map<int, int> hash;
        hash[0] = 1;

        int sum = 0, ret = 0;
        for (auto n : nums)
        {
            sum += n;
            if (hash.count(k))
                ret += hash[k];
            hash[sum]++;
        }

        return ret;
    }

    void reorderList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr || head->next->next == nullptr)
            return;

        ListNode *slow = head, *fast = head;
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode *head2 = new ListNode(0);
        ListNode *cur = slow->next;
        slow->next = nullptr;

        while (cur)
        {
            ListNode *next = cur->next;
            cur->next = head2->next;
            head2->next = cur;
            cur = next;
        }

        ListNode *newhead = new ListNode(0);
        ListNode *prev = newhead;
        ListNode *cur1 = head, *cur2 = head2->next;

        while (cur1)
        {
            prev->next = cur1;
            prev = prev->next;
            cur1 = cur1->next;

            if (cur2)
            {
                prev->next = cur2;
                prev = prev->next;
                cur2 = cur2->next;
            }
        }

        prev = newhead->next;
        delete head2, newhead;
        return;
    }
};