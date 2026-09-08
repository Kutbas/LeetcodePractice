#include <mutex>
#include <vector>
#include <algorithm>
#include <climits>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <iostream>
#include <sstream>
#include <regex>
#include <map>
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
    int m, n;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    vector<vector<int>> pacificAtlantic(vector<vector<int>> &heights)
    {
        m = heights.size(), n = heights[0].size();
        vector<vector<bool>> pac(m, vector<bool>(n));
        auto atl = pac;

        for (int i = 0; i < n; i++)
        {
            dfs(heights, 0, i, pac);
            dfs(heights, m - 1, i, atl);
        }
        for (int i = 0; i < m; i++)
        {
            dfs(heights, i, 0, pac);
            dfs(heights, i, n - 1, atl);
        }

        vector<vector<int>> ret;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (pac[i][j] && atl[i][j])
                    ret.push_back({i, j});
            }

        return ret;
    }

    void dfs(vector<vector<int>> &heights, int i, int j, vector<vector<bool>> &vis)
    {
        vis[i][j] = true;
        queue<pair<int, int>> q;
        q.push({i, j});

        while (q.size())
        {

            auto [a, b] = q.front();
            q.pop();
            for (int k = 0; k < 4; k++)
            {
                int x = a + dx[k], y = b + dy[k];
                if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && heights[x][y] >= heights[a][b])
                {
                    q.push({x, y});
                    vis[x][y] = true;
                }
            }
        }
    }

    // 2
    int largestSumAfterKNegations(vector<int> &nums, int k)
    {
        sort(nums.begin(), nums.end());
        int count = 0, minElem = INT_MAX;

        for (auto n : nums)
        {
            minElem = min(minElem, abs(n));
            if (n < 0)
                count++;
        }

        int sum = 0;
        if (count >= k)
        {
            for (int i = 0; i < k; i++)
                sum += -nums[i];
            for (int i = k; i < nums.size(); i++)
                sum += nums[i];
        }
        else
        {
            for (auto n : nums)
                sum += abs(n);

            if ((k - count) % 2 == 1)
                sum -= 2 * minElem;
        }

        return sum;
    }

    // 3
    class MyStack
    {
    private:
        queue<int> q;

    public:
        MyStack()
        {
        }

        void push(int x)
        {
            int n = q.size();
            q.push(x);

            for (int i = 0; i < n; i++)
            {
                q.push(q.front());
                q.pop();
            }
        }

        int pop()
        {
            int r = q.front();
            q.pop();
            return r;
        }

        int top()
        {
            return q.front();
        }

        bool empty()
        {
            return q.empty();
        }
    };

    // 4
    bool IsPopOrder(vector<int> &pushV, vector<int> &popV)
    {
        stack<int> st;
        int n = pushV.size(), i = 0;

        for (auto num : pushV)
        {
            st.push(num);
            while (st.size() && st.top() == popV[i])
            {
                st.pop();
                i++;
            }
        }

        return i == n;
    }

    // 5
    vector<int> ret;
    vector<int> inorderTraversal(TreeNode *root)
    {
        if (root == nullptr)
            return ret;

        dfs(root);

        return ret;
    }

    void dfs(TreeNode *root)
    {
        if (root == nullptr)
            return;

        dfs(root->left);
        ret.push_back(root->val);
        dfs(root->right);
    }
};

// 6
string change(string &s)
{
    if (s[0] >= 'A' && s[0] <= 'Z')
        s[0] = tolower(s[0]);
    return s;
}

int main()
{
    string s;
    getline(cin, s);

    regex re{"([a-zA-Z]+)"};
    sregex_token_iterator begin(s.begin(), s.end(), re, 0);
    sregex_token_iterator end;

    vector<string> words(begin, end);
    map<string, int> hash;

    for (auto &word : words)
    {
        string tmp = change(word);
        hash[tmp]++;
    }

    for (auto [a, b] : hash)
        cout << a << ":" << b << endl;

    return 0;
}