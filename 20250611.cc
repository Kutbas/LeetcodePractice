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
        unordered_map<string, int> hash;
        for (auto &word : words)
            hash[word]++;

        priority_queue<PSI, vector<PSI>, cmp> q;
        for (auto &[a, b] : hash)
            q.push({a, b});

        vector<string> ret;
        while (k--)
        {
            auto [a, b] = q.top();
            q.pop();
            ret.push_back(a);
        }

        return ret;
    }

    vector<int> smallestK(vector<int> &arr, int k)
    {
        vector<int> ret;

        priority_queue<int, vector<int>, greater<int>> q;
        for (auto n : arr)
            q.push(n);

        while (k--)
        {
            auto t = q.top();
            q.pop();
            ret.push_back(t);
        }

        return ret;
    }

    double myPow(double x, int n)
    {
        long long N = n;
        if (N < 0)
        {
            x = 1 / x;
            N = -N;
        }
        return pow(x, N);
    }

    double pow(double x, int n)
    {
        if (n == 0)
            return 1;

        double tmp = pow(x, n / 2);
        return n % 2 == 0 ? tmp * tmp : tmp * tmp * x;
    }

    bool validateStackSequences(vector<int> &pushed, vector<int> &popped)
    {
        int i = 0, n = popped.size();

        stack<int> num;
        for (auto &n : pushed)
        {
            num.push(n);
            while (num.size() && num.top() == popped[i])
            {
                i++;
                num.pop();
            }
        }

        return i == n;
    }

    double myPow(double x, int n)
    {
        long long N = n;
        if (N < 0)
        {
            x = 1 / x;
            N = -N;
        }
        return pow(x, N);
    }

    double pow(double x, int n)
    {
        if (n == 0)
            return 1;

        double tmp = pow(x, n / 2);
        return n % 2 == 0 ? tmp * tmp : tmp * tmp * x;
    }

    vector<int> twoSum(vector<int> &nums, int target)
    {
        unordered_map<int, int> hash;
        for (int i = 0; i < nums.size(); i++)
        {
            int x = target - nums[i];
            if (hash.count(x))
                return {i, hash[x]};
            else
                hash[nums[i]] = i;
        }
        return {-1, -1};
    }

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int color)
    {
        int origin = image[sr][sc];
        m = image.size(), n = image[0].size();
        if (origin == color)
            return image;

        queue<pair<int, int>> q;
        image[sr][sc] = color;
        q.push({sr, sc});
        while (q.size())
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

        return image;
    }
};