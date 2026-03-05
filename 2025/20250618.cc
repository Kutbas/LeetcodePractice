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
    string hash[10] = {
        "",
        "",
        "abc",
        "def",
        "ghi",
        "jkl",
        "mno",
        "pqrs",
        "tuv",
        "wxyz",
    };
    vector<string> ret;
    string path;
    vector<string> letterCombinations(string digits)
    {
        if (digits.empty())
            return ret;
        dfs(digits, 0);
        return ret;
    }

    void dfs(string &digits, int pos)
    {
        if (pos == digits.size())
        {
            ret.push_back(path);
            return;
        }

        for (auto ch : hash[digits[pos] - '0'])
        {
            path.push_back(ch);
            dfs(digits, pos + 1);
            path.pop_back();
        }
    }

    int minSubArrayLen(int target, vector<int> &nums)
    {
        int ret = INT_MAX;
        for (int left = 0, right = 0, tmp = 0; right < nums.size(); right++)
        {
            tmp += nums[right];
            while (tmp >= target)
            {
                ret = min(ret, right - left + 1);
                tmp -= nums[left++];
            }
        }
        return ret == INT_MAX ? 0 : ret;
    }

    int sum = 0;
    int sumNumbers(TreeNode *root)
    {
        dfs(root, 0);
        return sum;
    }

    void dfs(TreeNode *root, int tmp)
    {
        tmp = tmp * 10 + root->val;

        if (root->left == nullptr && root->right == nullptr)
        {
            sum += tmp;
            return;
        }

        if (root->left)
            dfs(root->left, tmp);
        if (root->right)
            dfs(root->right, tmp);
    }

    vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
    {
        vector<vector<int>> edges(numCourses);
        vector<int> in(numCourses);
        vector<int> ret;

        for (auto &e : prerequisites)
        {
            int a = e[0], b = e[1]; // b->a
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

        return ret.size() == numCourses ? ret : vector<int>{};
    }

    struct cmp
    {
        bool operator()(const ListNode &l1, const ListNode &l2)
        {
            return l1.val > l2.val;
        }
    };

    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        priority_queue<ListNode *, vector<ListNode *>, cmp> q;
        for (auto list : lists)
            if (list)
                q.push(list);

        ListNode *head = new ListNode(0);
        ListNode *prev = head;

        while (q.size())
        {
            auto t = q.top();
            q.pop();
            prev->next = t;
            prev = prev->next;

            if (t->next)
                q.push(t->next);
        }

        prev = head->next;
        delete head;
        return prev;
    }

    typedef pair<string, int> PSI;

    struct cmp
    {
        bool operator()(const PSI &p1, const PSI &p2)
        {
            if (p1.second == p2.second)
                return p1.first > p2.first;
            return p1.second < p2.second;
        }
    };

    vector<string> topKFrequent(vector<string> &words, int k)
    {
        vector<string> ret;
        unordered_map<string, int> hash;
        for (auto &word : words)
            hash[word]++;

        priority_queue<PSI, vector<PSI>, cmp> q;
        for (auto pair : hash)
            q.push(pair);

        while (k--)
        {
            auto [a, b] = q.top();
            q.pop();
            ret.push_back(a);
        }

        return ret;
    }

    ListNode *reverseList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *newhead = reverseList(head->next);
        newhead->next = head;
        head->next = nullptr;
        return newhead;
    }

    int left, right, N;
    string path;
    vector<string> ret;
    vector<string> generateParenthesis(int n)
    {

        N = n;
        dfs();
        return ret;
    }

    void dfs()
    {
        if (right == N)
        {
            ret.push_back(path);
            return;
        }

        if (left < N)
        {
            path.push_back('(');
            left++;
            dfs();
            path.pop_back();
            left--;
        }

        if (right < left)
        {
            path.push_back(')');
            right++;
            dfs();
            path.pop_back();
            right--;
        }
    }

    vector<vector<int>> ret2;
    vector<int> path2;
    int N, K;
    vector<vector<int>> combine(int n, int k)
    {
        N = n, K = k;
        dfs(1);
        return ret2;
    }

    void dfs(int pos)
    {
        if (path2.size() == K)
        {
            ret2.push_back(path2);
            return;
        }

        for (int i = pos; i <= N; i++)
        {
            path2.push_back(i);
            dfs(i + 1);
            path2.pop_back();
        }
    }
};