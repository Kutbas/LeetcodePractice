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

class Node
{
public:
    int val;
    vector<Node *> children;

    Node() {}

    Node(int _val)
    {
        val = _val;
    }

    Node(int _val, vector<Node *> _children)
    {
        val = _val;
        children = _children;
    }
};

class Solution
{
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode *root)
    {
        vector<vector<int>> ret;
        if (root == nullptr)
            return ret;

        queue<TreeNode *> q;
        q.push(root);

        int level = 1;

        while (q.size())
        {
            int sz = q.size();
            vector<int> tmp;
            for (int i = 0; i < sz; i++)
            {
                auto t = q.front();
                q.pop();
                tmp.push_back(t->val);

                if (t->left)
                    q.push(t->left);
                if (t->right)
                    q.push(t->right);
            }

            // 判断是否逆序
            if (level % 2 == 0)
                reverse(tmp.begin(), tmp.end());
            ret.push_back(tmp);
            level++;
        }

        return ret;
    }

    int widthOfBinaryTree(TreeNode *root)
    {
        // 用数组模拟队列
        vector<pair<TreeNode *, unsigned int>> q;
        q.push_back({root, 1});

        unsigned int ret = 0;
        while (q.size())
        {
            auto &[x1, y1] = q[0];
            auto &[x2, y2] = q.back();
            ret = max(ret, y2 - y1 + 1);

            // 让下一层进队
            vector<pair<TreeNode *, unsigned int>> tmp;
            for (auto &[x, y] : q)
            {
                if (x->left)
                    tmp.push_back({x->left, 2 * y});
                if (x->right)
                    tmp.push_back({x->right, 2 * y + 1});
            }
            q = tmp;
        }

        return ret;
    }

    vector<int> largestValues(TreeNode *root)
    {
        vector<int> ret;
        if (root == nullptr)
            return ret;

        queue<TreeNode *> q;
        q.push(root);

        while (q.size())
        {
            int sz = q.size();
            int tmp = INT_MIN;

            for (int i = 0; i < sz; i++)
            {
                auto t = q.front();
                q.pop();

                tmp = max(tmp, t->val);
                if (t->left)
                    q.push(t->left);
                if (t->right)
                    q.push(t->right);
            }
            ret.push_back(tmp);
        }
        return ret;
    }

    int getSum(int a, int b)
    {
        while (b)
        {
            int xorsum = a ^ b;
            int carry = (a & b) << 1;
            a = xorsum;
            b = carry;
        }
        return a;
    }

    int calculate(string s)
    {
        int n = s.size();
        vector<int> nums;

        char op = '+';

        int i = 0;
        while (i < n)
        {
            if (s[i] == ' ')
                i++;
            else if (s[i] >= '0' && s[i] <= '9')
            {
                int tmp = 0;
                while (i < n && s[i] >= '0' && s[i] <= '9')
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
                op = s[i++];
        }

        int ret = 0;
        for (auto n : nums)
            ret += n;
        return ret;
    }

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

    int findKthLargest(vector<int> &nums, int k)
    {
        srand(time(NULL));
        return quickSort(nums, 0, nums.size() - 1, k);
    }

    int getRandom(vector<int> &nums, int left, int right)
    {
        int r = rand();
        return nums[r % (right - left + 1) + left];
    }

    int quickSort(vector<int> &nums, int l, int r, int k)
    {
        if (l >= r)
            return nums[l];

        int key = getRandom(nums, l, r);
        int i = l, left = l - 1, right = r + 1;

        while (i < right)
        {
            if (nums[i] < key)
                swap(nums[i++], nums[++left]);
            else if (nums[i] == key)
                i++;
            else
                swap(nums[i], nums[--right]);
        }

        int rRange = right - r + 1, mRange = (r - 1) - (left + 1) + 1;
        if (rRange >= k)
            return quickSort(nums, r, right, k);
        else if (rRange + mRange >= k)
            return key;
        else
            return quickSort(nums, left, l, k - rRange - mRange);
    }

    int triangleNumber(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        int ret = 0, n = nums.size();

        for (int i = n - 1; i >= 2; i--)
        {
            int left = 0, right = i - 1;
            while (left < right)
            {
                if (nums[left] + nums[right] > nums[i])
                {
                    ret += right - left;
                    right--;
                }
                else
                    left++;
            }
        }

        return ret;
    }

    vector<int> ret;
    vector<int> index;
    vector<int> tmpNums;
    vector<int> tmpIndex;

    vector<int> countSmaller(vector<int> &nums)
    {
        int n = nums.size();
        ret.resize(n);
        index.resize(n);
        tmpNums.resize(n);
        tmpIndex.resize(n);

        for (int i = 0; i < n; i++)
            index[i] = i;

        mergeSort(nums, 0, n - 1);

        return ret;
    }

    void mergeSort(vector<int> &nums, int left, int right)
    {
        if (left >= right)
            return;

        int mid = left + (right - left) / 2;
        mergeSort(nums, left, mid);
        mergeSort(nums, mid + 1, right);

        int cur1 = left, cur2 = mid + 1, i = 0;
        while (cur1 <= mid && cur2 <= right)
        {
            if (nums[cur1] <= nums[cur2])
            {
                tmpNums[i] = nums[cur2];
                tmpIndex[i++] = index[cur2++];
            }
            else
            {
                ret[index[cur1]] += right - cur2 + 1;
                tmpNums[i] = nums[cur1];
                tmpIndex[i++] = index[cur1++];
            }
        }

        while (cur1 <= mid)
        {
            tmpNums[i] = nums[cur1];
            tmpIndex[i++] = index[cur1++];
        }

        while (cur2 <= right)
        {
            tmpNums[i] = nums[cur2];
            tmpIndex[i++] = index[cur2++];
        }

        for (int j = left; j <= right; j++)
        {
            nums[j] = tmpNums[j - left];
            index[j] = tmpIndex[j - left];
        }
    }

    int findMaxLength(vector<int> &nums)
    {
        unordered_map<int, int> hash;
        hash[0] = -1;

        int sum = 0, ret = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            sum += nums[i] == 0 ? -1 : 1;
            if (hash.count(sum))
                ret = max(ret, i - hash[sum]);
            else
                hash[sum] = i;
        }

        return ret;
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
            if (lsb & n)
                x ^= n;
            else
                y ^= n;
        }

        for (int i = 1; i <= nums.size() + 2; i++)
        {
            if (lsb & i)
                x ^= i;
            else
                y ^= i;
        }

        return {x, y};
    }

    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        return merge_sort(lists, 0, lists.size() - 1);
    }

    ListNode *merge_sort(vector<ListNode *> lists, int left, int right)
    {
        if (left > right)
            return nullptr;
        if (left == right)
            return lists[left];

        int mid = left + (right - left) / 2;
        ListNode *l1 = merge_sort(lists, left, mid);
        ListNode *l2 = merge_sort(lists, mid + 1, right);

        return merge2lists(l1, l2);
    }

    ListNode *merge2lists(ListNode *l1, ListNode *l2)
    {
        if (l1 == nullptr)
            return l2;
        if (l2 == nullptr)
            return l1;

        ListNode *head = new ListNode(0);
        ListNode *prev = head;
        ListNode *cur1 = l1, *cur2 = l2;

        while (cur1 && cur2)
        {
            if (cur1->val <= cur2->val)
            {
                prev->next = cur1;

                // prev = prev->next = cur1;
                cur1 = cur1->next;
            }
            else
            {
                // prev = prev->next = cur2;

                cur2 = cur2->next;
            }
        }

        if (cur1)
            prev->next = cur1;
        if (cur2)
            prev->next = cur2;

        return head->next;
    }

    int subarraySum(vector<int> &nums, int k)
    {
        unordered_map<int, int> hash;
        hash[0] = 1;
        int sum = 0, ret = 0;

        for (auto n : nums)
        {
            sum += n;
            if (hash.count(sum - k))
                ret += hash[sum - k];
            hash[sum]++;
        }

        return ret;
    }

    string multiply(string num1, string num2)
    {
        int m = num1.size(), n = num2.size();
        reverse(num1.begin(), num1.end());
        reverse(num2.begin(), num2.end());

        vector<int> tmp(m + n - 1);
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                tmp[i + j] += (num1[i] - '0') * (num2[j] - '0');

        string ret;
        int t = 0, cur = 0;
        while (cur < m + n - 1 || t)
        {
            if (cur < m + n - 1)
                t += tmp[cur++];
            ret += (t % 10 + '0');
            t /= 10;
        }

        while (ret.size() > 1 && ret.back() == '0')
            ret.pop_back();

        reverse(ret.begin(), ret.end());
        return ret;
    }

    bool validateStackSequences(vector<int> &pushed, vector<int> &popped)
    {
        stack<int> st;

        int i = 0, n = popped.size();
        for (auto num : pushed)
        {
            st.push(num);
            while (st.size() && st.size() == popped[i])
            {
                st.pop();
                i++;
            }
        }

        return i == n;
    }
};