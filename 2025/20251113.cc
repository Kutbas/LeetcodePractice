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
    int ladderLength(string beginWord, string endWord, vector<string> &wordList)
    {
        unordered_set<string> hash(wordList.begin(), wordList.end());
        unordered_set<string> vis;

        if (!hash.count(endWord))
            return 0;

        int ret = 1;
        queue<string> q;
        q.push(beginWord);
        vis.insert(beginWord);
        while (q.size())
        {
            ret++;
            int sz = q.size();
            while (sz--)
            {
                auto t = q.front();
                q.pop();
                for (int i = 0; i < t.size(); i++)
                {
                    string tmp = t;
                    for (char ch = 'a'; ch <= 'z'; ch++)
                    {
                        tmp[i] = ch;
                        if (hash.count(tmp) && !vis.count(tmp))
                        {
                            if (tmp == endWord)
                                return ret;
                            q.push(tmp);
                            vis.insert(tmp);
                        }
                    }
                }
            }
        }

        return 0;
    }

    // 2
    int brokenCalc(int startValue, int target)
    {
        int count = 0;
        while (target > startValue)
        {
            if (target % 2 == 0)
                target /= 2;
            else
                target++;
            count++;
        }

        return count + startValue - target;
    }

    // 3
    int maxSumDivThree(vector<int> &nums)
    {
        const int INF = 0x3f3f3f;
        int x1 = INF, x2 = INF;
        int y1 = INF, y2 = INF;
        int sum = 0;

        for (auto n : nums)
        {
            sum += n;
            if (n % 3 == 1)
            {
                if (n < x1)
                    x2 = x1, x1 = n;
                else if (n < x2)
                    x2 = n;
            }
            else if (n % 3 == 2)
            {
                if (n < y1)
                    y2 = y1, y1 = n;
                else if (n < y2)
                    y2 = n;
            }
        }

        if (sum % 3 == 0)
            return sum;
        return sum % 3 == 1 ? max(sum - x1, sum - y1 - y2) : max(sum - y1, sum - x1 - x2);
    }

    // 4
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

    // 5
    string optimalDivision(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 1)
            return to_string(nums[0]);
        if (n == 2)
            return to_string(nums[0]) + "/" + to_string(nums[1]);

        string ret = to_string(nums[0]) + "/(" + to_string(nums[1]);
        for (int i = 2; i < n; i++)
            ret += "/" + to_string(nums[i]);
        ret += ")";
        return ret;
    }

    // 6
    int findLengthOfLCIS(vector<int> &nums)
    {
        int n = nums.size(), ret = 0;
        for (int left = 0, right = 0; right < n;)
        {
            while (right + 1 < n && nums[right + 1] > nums[right])
                right++;
            ret = max(ret, right - left + 1);
            left = right;
        }
        return ret;
    }

    // 7
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost)
    {
        int n = gas.size();
        for (int i = 0; i < n; i++)
        {
            int rest = 0, step = 0;
            for (; step <= n; step++)
            {
                int index = (i + step) % n;
                rest += gas[index] - cost[index];
                if (rest < 0)
                    break;
            }
            if (rest >= 0)
                return i;
            i = i + step;
        }
        return -1;
    }
};