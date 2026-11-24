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
#include <set>
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

// 1 Singleton

// 2 ThreadPool

class Solution
{
public:
    // 3
    int numberOfArithmeticSlices(vector<int> &nums)
    {
        int n = nums.size(), ret = 0, prev = 0;

        for (int i = 2; i < n; i++)
        {
            if (nums[i] - nums[i - 1] == nums[i - 1] - nums[i - 2])
            {
                prev += 1;
                ret += prev;
            }
            else
                prev = 0;
        }

        return ret;
    }

    // 4
    string reverseStr(string s, int k)
    {
        int n = s.size();

        for (int i = 0; i < n; i += 2 * k)
        {
            int right = min(n, i + k);
            reverse(s.begin() + i, s.begin() + right);
        }

        return s;
    }
};