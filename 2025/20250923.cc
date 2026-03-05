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
    const int INF = 0x3f3f3f;
    int maxProfit(int k, vector<int> &prices)
    {
        int n = prices.size();
        k = min(k, n / 2);

        vector<vector<int>> f(n, vector<int>(k + 1, -INF));
        auto g = f;

        f[0][0] = -prices[0], g[0][0] = 0;

        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j <= k; j++)
            {
                f[i][j] = max(f[i - 1][j], g[i - 1][j] - prices[i]);
                g[i][j] = g[i - 1][j];
                if (j >= 1)
                    g[i][j] = max(g[i][j], f[i - 1][j - 1] + prices[i]);
            }
        }

        int ret = 0;
        for (int i = 0; i <= k; i++)
            ret = max(ret, g[n - 1][i]);
        return ret;
    }

    // 1
    string decodeString(string s)
    {
        stack<string> st;
        stack<int> nums;

        int n = 0;
        string ret;
        for (auto ch : s)
        {
            if (isdigit(ch))
            {
                n = n * 10 + (ch - '0');
                continue;
            }
            else if (ch == '[')
            {
                nums.push(n);
                n = 0;
                st.push(ret);
                ret = "";
            }
            else if (ch == ']')
            {
                int k = nums.top();
                nums.pop();
                string tmp = st.top();
                while (k--)
                {
                    tmp += ret;
                }
                st.top() = ret;
            }
            else
                ret += ch;
        }

        return st.top();
    }

    // 2
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

        for (auto [a, b] : hash)
        {
            ret.push_back(b);
        }

        return ret;
    }

    // 3
    vector<vector<int>> matrixBlockSum(vector<vector<int>> &mat, int k)
    {
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1] + mat[i - 1][j - 1];

        vector<vector<int>> ret(m, vector<int>(n));
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                int x1 = max(0, i - k) + 1, y1 = max(0, j - k) + 1;
                int x2 = min(m - 1, i + k) + 1, y2 = min(n - 1, j + k) + 1;
                ret[i][j] = dp[x2][y2] - dp[x1 - 1][y2] - dp[x2][y1 - 1] + dp[x1 - 1][y1 - 1];
            }

        return ret;
    }

    // 4
    int tmp[50010];
    int reversePairs(vector<int> &record)
    {
        return mergeSort(record, 0, record.size() - 1);
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

    // 5
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
    {
        if (l1 == nullptr)
            return l2;
        if (l2 == nullptr)
            return l1;

        if (l1->val <= l2->val)
        {
            l1->next = mergeTwoLists(l1->next, l2);
            return l1;
        }
        else
        {
            l2->next = mergeTwoLists(l1, l2->next);
            return l2;
        }
    }

    // 6
    bool vis[16];
    int ret = 0, N;
    int countArrangement(int n)
    {
        N = n;
        dfs(1);
        return ret;
    }

    void dfs(int pos)
    {
        if (pos == N + 1)
        {
            ret++;
            return;
        }

        for (int i = 1; i <= N; i++)
        {
            if (!vis[i] && (i % pos == 0 || pos % i == 0))
            {
                vis[i] = true;
                dfs(pos + 1);
                vis[i] = false;
            }
        }
    }
};