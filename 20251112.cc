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
    bool validateStackSequences(vector<int> &pushed, vector<int> &popped)
    {
        stack<int> st;
        int n = pushed.size(), i = 0;

        for (auto n : pushed)
        {
            st.push(n);
            while (st.size() && st.top() == popped[i])
            {
                st.pop();
                i++;
            }
        }

        return i == n;
    }

    // 3
    vector<string> ret;
    string path;
    vector<string> letterCasePermutation(string s)
    {
        dfs(s, 0);
        return ret;
    }

    void dfs(string &s, int pos)
    {
        if (pos == s.size())
        {
            ret.push_back(path);
            return;
        }

        path.push_back(s[pos]);
        dfs(s, pos + 1);
        path.pop_back();

        if (!isdigit(s[pos]))
        {
            char tmp = change(s[pos]);
            path.push_back(tmp);
            dfs(s, pos + 1);
            path.pop_back();
        }
    }

    char change(char ch)
    {
        if (ch >= 'a' && ch <= 'z')
            ch -= 32;
        else
            ch += 32;
        return ch;
    }

    // 4
    int findContentChildren(vector<int> &g, vector<int> &s)
    {
        int m = g.size(), n = s.size();
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());

        int ret = 0;
        for (int i = 0, j = 0; i < m && j < n; i++)
        {
            while (s[j] < g[i] && j < n)
                j++;
            if (s[j] >= g[i])
                ret++;
        }

        return ret;
    }

    // 5
    void reorderList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
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

        ListNode *ret = new ListNode(0);
        ListNode *prev = ret, *cur1 = head, *cur2 = head2->next;
        while (cur1 || cur2)
        {
            if (cur1)
            {
                prev->next = cur1;
                prev = prev->next;
                cur1 = cur1->next;
            }
            if (cur2)
            {
                prev->next = cur2;
                prev = prev->next;
                cur2 = cur2->next;
            }
        }

        prev = ret->next;
        delete ret, cur;
    }

    // 6
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    bool vis[51][51];
    vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int color)
    {
        m = image.size(), n = image[0].size();

        int origin = image[sr][sc];
        if (origin == color)
            return image;

        queue<pair<int, int>> q;
        q.push({sr, sc});
        image[sr][sc] = color;
        vis[sr][sc] = true;

        while (q.size())
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

        return image;
    }

    // 7
    bool Vis[16];
    int N, res = 0;
    int countArrangement(int n)
    {
        N = n;
        dfs(1);
        return res;
    }

    void dfs(int pos)
    {
        if (pos == N + 1)
        {
            res++;
            return;
        }

        for (int i = 1; i <= N; i++)
        {
            if (!Vis[i] && (i % pos == 0 || pos % i == 0))
            {
                Vis[i] = true;
                dfs(pos + 1);
                Vis[i] = false;
            }
        }
    }
};