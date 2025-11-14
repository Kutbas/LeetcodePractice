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
    bool increasingTriplet(vector<int> &nums)
    {
        int a = INT_MAX, b = nums[0], n = nums.size();

        for (int i = 1; i < n; i++)
        {
            if (nums[i] > a)
                return true;
            else if (nums[i] > b)
                a = nums[i];
            else
                b = nums[i];
        }

        return false;
    }

    // 2
    ListNode *swapPairs(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *ret = swapPairs(head->next->next);
        head->next->next = head;
        head->next = ret;

        return head;
    }

    // 3
    int memo[101][101];
    int uniquePaths(int m, int n)
    {
        return dfs(m, n);
    }

    int dfs(int m, int n)
    {
        if (memo[m][n])
            return memo[m][n];

        if (m == 0 || n == 0)
            return 0;

        if (m == 1 && n == 1)
        {
            memo[m][n] = 1;
            return 1;
        }

        int ret = dfs(m - 1, n) + dfs(m, n - 1);
        memo[m][n] = ret;
        return ret;
    }

    // 4
    vector<vector<int>> threeSum(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        vector<vector<int>> ret;
        int n = nums.size();

        int i = 0;
        while (i < n - 1)
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
                    } while (left < right && nums[left] == nums[left - 1]);
                    do
                    {
                        right--;
                    } while (left < right && nums[right] == nums[right + 1]);
                }
            }

            do
            {
                i++;
            } while (i < n - 1 && nums[i] == nums[i - 1]);
        }

        return ret;
    }

    // 5
    vector<string> res;
    string path;
    int N, left = 0, right = 0;
    vector<string> generateParenthesis(int n)
    {
        N = n;
        dfs();
        return res;
    }

    void dfs()
    {
        if (right == N)
        {
            res.push_back(path);
            return;
        }

        if (left < N)
        {
            path += "(";
            left++;
            dfs();
            path.pop_back();
            left--;
        }

        if (right < left)
        {
            path += ")";
            right++;
            dfs();
            path.pop_back();
            right--;
        }
    }

    // 6
    vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
    {
        vector<vector<int>> edges(numCourses);
        vector<int> in(numCourses);

        for (auto &e : prerequisites)
        {
            int a = e[0], b = e[1]; // b->a
            edges[b].push_back(a);
            in[a]++;
        }

        vector<int> ret;
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

        for (int i = 0; i < numCourses; i++)
            if (in[i])
                return {};
        return ret;
    }

    // 7
    int jump(vector<int> &nums)
    {
        int n = nums.size(), ret = 0, cur = 0, far = 0;

        for (int i = 0; i < n - 1; i++)
        {
            far = max(far, i + nums[i]);

            if (i == cur)
            {
                ret++;
                cur = far;

                if (cur >= n - 1)
                    break;
            }
        }

        return ret;
    }
};