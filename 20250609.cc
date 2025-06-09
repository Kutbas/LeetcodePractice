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
    void hanota(vector<int> &A, vector<int> &B, vector<int> &C)
    {
        dfs(A, B, C, A.size());
    }

    void dfs(vector<int> &from, vector<int> &buffer, vector<int> &to, int n)
    {
        if (n == 1)
        {
            to.push_back(from.back());
            from.pop_back();
            return;
        }

        dfs(from, to, buffer, n - 1);
        to.push_back(from.back());
        from.pop_back();
        dfs(buffer, from, to, n - 1);
    }

    bool containsDuplicate(vector<int> &nums)
    {
        unordered_map<int, int> hash;
        for (auto num : nums)
            if (++hash[num] >= 2)
                return true;
        return false;
    }

    bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
    {
        unordered_map<int, vector<int>> edges(numCourses);
        vector<int> in(numCourses);

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

            for (auto a : edges[t])
                if (--in[a] == 0)
                    q.push(a);
        }

        for (int i = 0; i < numCourses; i++)
            if (in[i])
                return false;
        return true;
    }

    void hanota(vector<int> &A, vector<int> &B, vector<int> &C)
    {
        dfs(A, B, C, A.size());
    }

    void dfs(vector<int> &from, vector<int> &buffer, vector<int> &to, int n)
    {
        if (n == 1)
        {
            to.push_back(from.back());
            from.pop_back();
            return;
        }

        dfs(from, to, buffer, n - 1);
        to.push_back(from.back());
        from.pop_back();
        dfs(buffer, from, to, n - 1);
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
            if (n & lsb)
                x ^= n;
            else
                y ^= n;
        }

        for (int i = 1; i <= nums.size() + 2; i++)
        {
            if (i & lsb)
                x ^= i;
            else
                y ^= i;
        }

        return {x, y};
    }

    vector<vector<int>> threeSum(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        vector<vector<int>> ret;

        int n = nums.size();
        int i = 0;
        while (i < n - 2)
        {
            int left = i + 1, right = n - 1;
            while (left < right)
            {
                if (nums[i] + nums[left] + nums[right] > 0)
                    right--;
                else if (nums[i] + nums[left] + nums[right] < 0)
                    left++;
                else
                {
                    ret.push_back({nums[i], nums[left], nums[right]});
                    do
                    {
                        left++;
                    } while (nums[left] == nums[left - 1] && left < right);

                    do
                    {
                        right--;
                    } while (nums[right] == nums[right + 1] && left < right);
                }
            }

            do
            {
                i++;
            } while (nums[i] == nums[i - 1] && i < n - 2);
        }

        return ret;
    }

    typedef pair<int, int> PIR;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    int cutOffTree(vector<vector<int>> &forest)
    {
        m = forest.size(), n = forest[0].size();
        vector<PIR> trees;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (forest[i][j] > 1)
                    trees.push_back({i, j});

        sort(trees.begin(), trees.end(), [&](const PIR &p1, const PIR &p2)
             { return forest[p1.first][p1.second] < forest[p2.first][p2.second]; });

        int bx = 0, by = 0, ret = 0;
        for (auto [a, b] : trees)
        {
            int step = DFS(forest, bx, by, a, b);
            if (step == -1)
                return -1;
            ret += step;
            bx = a, by = b;
        }

        return ret;
    }

    int DFS(vector<vector<int>> &forest, int bx, int by, int ex, int ey)
    {
        if (bx == ex && by == ey)
            return 0;

        bool vis[51][51] = {0};
        queue<PIR> q;
        q.push({bx, by});
        vis[bx][by] = true;
        int ret = 0;

        while (q.size())
        {
            ret++;
            int sz = q.size();
            while (sz--)
            {
                auto [a, b] = q.front();
                q.pop();
                for (int k = 0; k < 4; k++)
                {
                    int x = a + dx[k], y = b + dy[k];
                    if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && forest[x][y])
                    {
                        if (x == ex && y == ey)
                            return ret;
                        q.push({x, y});
                        vis[x][y] = true;
                    }
                }
            }
        }

        return -1;
    }

    bool containsNearbyDuplicate(vector<int> &nums, int k)
    {
        unordered_map<int, int> hash;
        for (int i = 0; i < nums.size(); i++)
        {
            if (hash.count(nums[i]) && i - hash[nums[i]] <= k)
                return true;
            hash[nums[i]] = i;
        }
        return false;
    }

    double mypow(double x, int n)
    {
        long long N = n; // 防止 -2^31 溢出
        if (N < 0)
        {
            x = 1 / x;
            N = -N;
        }
        return pow(x, N);
    }

    double pow(double x, long long n)
    {
        if (n == 0)
            return 1.0;
        double half = pow(x, n / 2);
        return n % 2 == 0 ? half * half : half * half * x;
    }
};