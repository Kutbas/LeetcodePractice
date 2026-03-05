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

    // 3
    int findLengthOfLCIS(vector<int> &nums)
    {
        int n = nums.size(), ret = 1;
        for (int left = 0, right = 0; right < n; right++)
        {
            while (right + 1 < n && nums[right + 1] > nums[right])
                right++;
            ret = max(ret, right - left + 1);
            left = right + 1;
        }
        return ret;
    }

    // 4
    int MoreThanHalfNum_Solution(vector<int> &numbers)
    {
        int n = numbers.size(), ret = numbers[0], count = 1;

        for (auto num : numbers)
        {
            if (num == ret)
                count++;
            else if (--count == 0)
            {
                ret = num;
                count = 1;
            }
        }

        return ret;
    }

    // 5
    vector<vector<int>> ret;
    vector<int> path;
    vector<vector<int>> subsets(vector<int> &nums)
    {
        dfs(nums, 0);
        return ret;
    }

    void dfs(vector<int> &nums, int pos)
    {
        ret.push_back(path);

        if (pos == nums.size())
            return;

        for (int i = pos; i < nums.size(); i++)
        {
            path.push_back(nums[i]);
            dfs(nums, i + 1);
            path.pop_back();
        }
    }

    // 6
    ListNode *swapPairs(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
        {
            return head;
        }

        // 保存第二个节点（它将变成新的头）
        ListNode *newHead = head->next;

        // 递归处理后面的节点
        ListNode *nextPair = swapPairs(newHead->next);

        // 交换当前两个节点
        newHead->next = head;  // 新头指向旧头
        head->next = nextPair; // 旧头指向后续链表

        return newHead; // 返回新的头
    }
};

// 2
int main()
{
    string s;
    cin >> s;

    int hash[128] = {0};
    for (char ch : s)
        hash[ch]++;

    for (char ch : s)
        if (hash[ch] == 1)
        {
            cout << ch << endl;
            return 0;
        }

    cout << -1 << endl;
    return 0;
}