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
    ListNode *swapPairs(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *ret = new ListNode(0);
        ListNode *prev = ret;
        ListNode *cur = head, *next = cur->next, *nnext = next->next;

        while (cur && next)
        {
            prev->next = next;
            next->next = cur;
            cur->next = nnext;
            prev = cur;
            cur = nnext;
            if (cur)
                next = cur->next;
            if (next)
                nnext = next->next;
        }

        prev = ret->next;
        delete ret;
        return prev;
    }

    // 2
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
    int tmp[50010];
    int reversePairs(vector<int> &record)
    {
        return mergeSort(record, 0, record.size() - 1);
    }

    int mergeSort(vector<int> &nums, int left, int right)
    {
        if (left >= right)
            return 0;

        int mid = left + (right - left) / 2, ret = 0;
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

    // 4
    int minMutation(string startGene, string endGene, vector<string> &bank)
    {
        if (startGene == endGene)
            return 0;

        unordered_set<string> hash(bank.begin(), bank.end());
        unordered_set<string> vis;

        if (!hash.count(endGene))
            return -1;

        string change = "ATGC";
        queue<string> q;
        q.push(startGene);
        int ret = 0;

        while (q.size())
        {
            auto t = q.front();
            q.pop();

            for (int i = 0; i < t.size(); i++)
            {
                string tmp = t;
                for (char ch : change)
                {
                    tmp[i] = ch;
                    if (hash.count(tmp) && !vis.count(tmp))
                    {
                        if (tmp == endGene)
                            return ret;

                        ret++;
                        q.push(tmp);
                        vis.insert(tmp);
                    }
                }
            }
        }

        return -1;
    }

    // 5
    bool validateStackSequences(vector<int> &pushed, vector<int> &popped)
    {
        stack<int> st;
        int n = pushed.size(), i = 0;

        for (auto n : pushed)
        {
            st.push(n);
            while (st.size() && st.top() == popped[i])
            {
                st.pop();
                i++;
            }
        }

        return i == n;
    }

    // 6
    int subarraySum(vector<int> &nums, int k)
    {
        unordered_map<int, int> hash;
        hash[0] = 1;

        int ret = 0, sum = 0;
        for (auto n : nums)
        {
            sum += n;
            if (hash.count(sum - k))
                ret += hash[sum - k];
            hash[sum]++;
        }

        return ret;
    }

    // 7
    int calculate(string s)
    {
        vector<int> nums;
        char op = '+';
        int n = s.size();

        for (int i = 0; i < n; i++)
        {
            if (s[i] == ' ')
                continue;
            else if (isdigit(s[i]))
            {
                int tmp = 0;
                while (isdigit(s[i]) && i < n)
                    tmp = tmp * 10 + (s[i++] - '0');

                if (op == '+')
                    nums.push_back(tmp);
                else if (op == '-')
                    nums.push_back(-tmp);
                else if (op == '*')
                    nums.back() *= tmp;
                else
                    nums.back() /= tmp;
            }
            else
                op = s[i];
        }

        int ret = 0;
        for (auto n : nums)
            ret += n;
        return ret;
    }
};