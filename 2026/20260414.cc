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
    int m, n;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    vector<vector<int>> pacificAtlantic(vector<vector<int>> &heights)
    {
        m = heights.size(), n = heights[0].size();
        vector<vector<bool>> pac(m, vector<bool>(n)), atl(m, vector<bool>(n));

        for (int i = 0; i < m; i++)
        {
            dfs(heights, i, 0, pac);
            dfs(heights, i, n - 1, atl);
        }

        for (int i = 0; i < n; i++)
        {
            dfs(heights, 0, i, pac);
            dfs(heights, m - 1, i, atl);
        }

        vector<vector<int>> ret;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (pac[i][j] && atl[i][j])
                    ret.push_back({i, j});

        return ret;
    }

    void dfs(vector<vector<int>> &heights, int i, int j, vector<vector<bool>> &vis)
    {
        queue<pair<int, int>> q;
        vis[i][j] = true;
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
                    vis[x][y] = true;
                    q.push({x, y});
                }
            }
        }
    }

    // 2
    string tree2str(TreeNode *root)
    {
        if (root == nullptr)
            return "";

        string ret;
        ret += to_string(root->val);

        if (root->left || root->right)
        {
            ret += "(";
            ret += tree2str(root->left);
            ret += ")";
        }

        if (root->right)
        {
            ret += "(";
            ret += tree2str(root->right);
            ret += ")";
        }

        return ret;
    }

    // 3
    int m, n;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int memo[201][201];
    bool vis[201][201];
    int longestIncreasingPath(vector<vector<int>> &matrix)
    {
        m = matrix.size(), n = matrix[0].size();
        int ret = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                vis[i][j] = true;
                ret = max(ret, 1 + dfs(matrix, i, j));
                vis[i][j] = false;
            }

        return ret;
    }

    int dfs(vector<vector<int>> &matrix, int i, int j)
    {
        if (memo[i][j])
            return memo[i][j];

        int ret = 0;
        for (int k = 0; k < 4; k++)
        {
            int x = i + dx[k], y = j + dy[k];
            if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && matrix[x][y] > matrix[i][j])
            {
                vis[x][y] = true;
                ret = max(ret, 1 + dfs(matrix, x, y));
                vis[x][y] = false;
            }
        }

        memo[i][j] = ret;
        return ret;
    }

    // 4
    int MoreThanHalfNum_Solution(vector<int> &numbers)
    {
        int n = numbers.size(), ret = numbers[0], count = 1;

        for (int i = 1; i < n; i++)
        {
            if (ret == numbers[i])
                count++;
            else if (--count == 0)
            {
                ret = numbers[i];
                count = 1;
            }
        }

        return ret;
    }

    // 5
    ListNode *reverseList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *newhead = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;

        return newhead;
    }

    // 6
    vector<string> sortPeople(vector<string> &names, vector<int> &heights)
    {
        int n = names.size();
        vector<int> index(n);
        for (int i = 0; i < n; i++)
            index[i] = i;

        sort(index.begin(), index.end(), [&](const int i, const int j)
             { return heights[i] > heights[j]; });

        vector<string> ret;
        for (auto i : index)
            ret.push_back(names[i]);

        return ret;
    }

};

// 7
const int N=1010;
int n,v;
int V[N],W[N];
int dp[N][N];

int main() {
    cin>>n>>v;
    for(int i=1;i<=n;i++)
        cin>>V[i]>>W[i];

    memset(dp,0,sizeof dp);
    for(int i=1;i<=n;i++)
        for(int j=0;j<=v;j++)
        {
            dp[i][j]=dp[i-1][j];

            if(j>=V[i])
                dp[i][j]=max(dp[i][j],dp[i-1][j-V[i]]+W[i]);
        }

    cout<<dp[n][v]<<endl;

    memset(dp, 0, sizeof dp);
    for(int i=1;i<=v;i++)
        dp[0][i]=-1;

    for(int i=1;i<=n;i++)
        for(int j=0;j<=v;j++)
        {
            dp[i][j]=dp[i-1][j];

            if(j>=V[i]&&dp[i-1][j-V[i]]!=-1)
                dp[i][j]=max(dp[i][j],dp[i-1][j-V[i]]+W[i]);

        }

    cout<<(dp[n][v]==-1?0:dp[n][v])<<endl;

    return 0;
}