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
    double myPow(double x, int n)
    {
        long long N = n;
        if (N < 0)
        {
            N = -N;
            x = 1 / x;
        }

        return pow(x, N);
    }

    double pw(double x, long long n)
    {
        if (n == 0)
            return 1;

        double tmp = pow(x, n / 2);

        return n % 2 == 0 ? tmp * tmp : tmp * tmp * x;
    }

    // 2
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
            hash[r]++;
        }

        return ret;
    }

    // 3
    vector<vector<int>> ret;
    vector<int> path;
    bool vis[9] = {0};
    vector<vector<int>> permuteUnique(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        dfs(nums);
        return ret;
    }

    void dfs(vector<int> &nums)
    {
        if (path.size() == nums.size())
        {
            ret.push_back(path);
            return;
        }

        for (int i = 0; i < nums.size(); i++)
        {
            if (vis[i] || (i != 0 && nums[i - 1] == nums[i] && !vis[i - 1]))
                continue;

            vis[i] = true;
            path.push_back(nums[i]);
            dfs(nums);
            path.pop_back();
            vis[i] = false;
        }
    }

    // 4
    int halveArray(vector<int> &nums)
    {
        priority_queue<double> q;
        double sum = 0;

        for (auto n : nums)
        {
            sum += n;
            q.push(n);
        }

        int ret = 0;
        double aim = sum / 2.0;
        while (sum > aim)
        {
            auto t = q.top() / 2.0;
            q.pop();
            sum -= t;
            q.push(t);
            ret++;
        }

        return ret;
    }

    // 5
    int memo[201][201];
    int getMoneyAmount(int n)
    {
        return dfs(1, n);
    }

    int dfs(int left, int right)
    {
        if (left >= right)
            return 0;

        if (memo[left][right])
            return memo[left][right];

        int ret = INT_MAX;
        for (int head = left; head <= right; head++)
        {
            int x = dfs(left, head - 1);
            int y = dfs(head + 1, right);

            ret = min(ret, head + max(x, y));
        }

        memo[left][right] = ret;
        return ret;
    }

    // 6
    long prev = LONG_MIN;
    bool isValidBST(TreeNode *root)
    {
        if (root == nullptr)
            return true;

        bool left = isValidBST(root->left);
        if (!left)
            return false;

        bool cur = false;
        if (prev < root->val)
            cur = true;
        if (!cur)
            return false;

        prev = root->val;
        bool right = isValidBST(root->right);
        return right;
    }

    // 7
    ListNode *reverseList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *tmp = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;

        return tmp;
    }
};