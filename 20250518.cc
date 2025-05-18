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

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    bool vis[1001][1001] = {0};
    int m, n;
    vector<vector<int>> highestPeak(vector<vector<int>> &isWater)
    {
        m = isWater.size(), n = isWater[0].size();
        vector<vector<int>> ret(m, vector<int>(n, -1));

        queue<pair<int, int>> q;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (isWater[i][j])
                {
                    ret[i][j] = 0;
                    q.push({i, j});
                    vis[i][j] = true;
                }

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
                    if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && ret[x][y] == -1)
                    {
                        ret[x][y] = ret[a][b] + 1;
                        q.push({x, y});
                        vis[x][y] = true;
                    }
                }
            }
        }

        return ret;
    }

    string decodeString(string s)
    {
        stack<int> nums;
        stack<string> st;
        st.push("");

        int i = 0, n = s.size();
        while (i < n)
        {
            if (s[i] >= '0' && s[i] <= '9')
            {
                int tmp = 0;
                while (i < n && s[i] >= '0' && s[i] <= '9')
                    tmp = tmp * 10 + (s[i++] - '0');
                nums.push(tmp);
            }
            if (s[i] == '[')
            {
                i++;
                string tmp;
                while (i < n && s[i] >= 'a' && s[i] <= 'z')
                    tmp += s[i++];
                st.push(tmp);
            }
            if (s[i] == ']')
            {
                int k = nums.top();
                nums.pop();
                string tmp = st.top();
                st.pop();
                while (k--)
                    st.top() += tmp;
                i++;
            }
            if (s[i] >= 'a' && s[i] <= 'z')
            {
                string tmp;
                while (i < n && s[i] >= 'a' && s[i] <= 'z')
                    tmp += s[i++];
                st.top() += tmp;
            }
        }

        return st.top();
    }

    string decodeString(string s)
    {
        stack<int> nums;
        stack<string> st;
        string ret;
        int k = 0;
        for (char c : s)
        {
            if (isdigit(c))
            {
                k = k * 10 + c - '0';
            }
            else if (c == '[')
            {
                nums.push(k);
                st.push(ret);
                k = 0;
                ret = "";
            }
            else if (c == ']')
            {
                string tmp = st.top();
                st.pop();
                int k = nums.top();
                nums.pop();
                while (k--)
                    tmp += ret;
                ret = tmp;
            }
            else
            {
                ret += c;
            }
        }
        return ret;
    }

    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        return mergeLists(lists, 0, lists.size() - 1);
    }

    ListNode *mergeLists(vector<ListNode *> &lists, int left, int right)
    {
        if (left > right)
            return nullptr;
        if (left == right)
            return lists[left];

        int mid = left + (right - left) / 2;
        ListNode *l1 = mergeLists(lists, left, mid);
        ListNode *l2 = mergeLists(lists, mid + 1, right);

        return merge2lists(l1, l2);
    }

    ListNode *merge2lists(ListNode *l1, ListNode *l2)
    {
        if (l1 == nullptr)
            return l2;
        if (l2 == nullptr)
            return l1;

        ListNode *head = new ListNode(0);
        ListNode *prev = head;
        ListNode *cur1 = l1, *cur2 = l2;

        while (cur1 && cur2)
        {
            if (cur1->val < cur2->val)
            {
                prev->next = cur1;
                prev = prev->next;
                cur1 = cur1->next;
            }
            else
            {
                prev->next = cur2;
                prev = prev->next;
                cur2 = cur2->next;
            }
        }

        if (cur1)
            prev->next = cur1;
        if (cur2)
            prev->next = cur2;

        prev = head->next;
        delete head;
        return prev;
    }

    bool containsNearbyDuplicate(vector<int> &nums, int k)
    {
        unordered_map<int, int> hash;
        for (int i = 0; i < nums.size(); i++)
        {
            if (hash.count(nums[i]) && i - hash[nums[i]] <= k)
                return true;
            else
                hash[nums[i]] = i;
        }
        return false;
    }

    ListNode *swapPairs(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *newhead = new ListNode(0);
        ListNode *prev = newhead;
        ListNode *cur = head, *next = cur->next, *nnext = next->next;

        while (cur && next)
        {
            prev->next = next;
            next->next = cur;
            cur->next = nnext;

            prev = cur;
            cur = nnext;

            if (cur)
                next = cur->next;
            if (next)
                nnext = next->next;
        }

        prev = newhead->next;
        delete newhead;
        return prev;
    }

    vector<int> productExceptSelf(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> f(n), g(n), ret(n);
        f[0] = g[n - 1] = 1;
        for (int i = 1; i < n; i++)
            f[i] = f[i - 1] * nums[i - 1];
        for (int i = n - 2; i >= 0; i--)
            g[i] = g[i + 1] * nums[i + 1];
        for (int i = 0; i < n; i++)
            ret[i] = f[i] * g[i];
        return ret;
    }
};