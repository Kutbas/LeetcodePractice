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
    string longestPalindrome(string s)
    {
        if (s.size() < 2)
            return s;

        int n = s.size(), begin = 0, maxlen = 1;
        vector<vector<int>> dp(n, vector<int>(n));
        for (int i = 0; i < n; i++)
            dp[i][i] = true;

        for (int L = 2; L <= n; L++)
            for (int i = 0; i < n; i++)
            {
                int j = i + L - 1;
                if (j >= n)
                    break;

                if (s[i] != s[j])
                    dp[i][j] = false;
                else
                {
                    if (L == 2)
                        dp[i][j] = true;
                    else
                        dp[i][j] = dp[i + 1][j - 1];
                }

                if (dp[i][j] && j - i + 1 > maxlen)
                {
                    maxlen = j - i + 1;
                    begin = i;
                }
            }

        return s.substr(begin, maxlen);
    }

    void reorderList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr || head->next->next == nullptr)
            return;

        ListNode *slow = head, *fast = head;
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode *head2 = new ListNode(0);
        ListNode *prev = head2;
        // head2->next = slow->next;
        ListNode *cur = slow->next;
        slow->next = nullptr;

        // ListNode *cur = head2->next;
        while (cur)
        {
            ListNode *next = cur->next;
            cur->next = prev->next;
            prev->next = cur;
            // head2->next = next;
            // next->next = cur;
            cur = next;
        }

        ListNode *ret = new ListNode(0);
        prev = ret;
        ListNode *cur1 = head, *cur2 = head2->next;

        while (cur1)
        {
            prev->next = cur1;

            prev = prev->next;
            cur1 = cur1->next;
            if (cur2)
            {
                prev->next = cur2;
                prev = prev->next;
                cur2 = cur2->next;
            }
        }

        delete head2, ret;
        return;
    }

    bool validateStackSequences(vector<int> &pushed, vector<int> &popped)
    {
        stack<int> st;
        int n = popped.size(), i = 0;

        for (auto num : pushed)
        {
            st.push(num);
            while (st.size() && st.top() == popped[i])
            {
                st.pop();
                i++;
            }
        }

        return i == n;
    }

    int tmp[50010];
    int reversePairs(vector<int> &nums)
    {
        return mergeSort(nums, 0, nums.size() - 1);
    }

    int mergeSort(vector<int> &nums, int left, int right)
    {
        if (left >= right)
            return 0;

        int ret = 0;
        int mid = left + (right - left) / 2;

        ret += mergeSort(nums, left, mid);
        ret += mergeSort(nums, mid + 1, right);

        int cur1 = left, cur2 = mid + 1, i = 0;
        while (cur1 <= mid)
        {
            while (cur2 <= right && nums[cur1] <= 2 * nums[cur2])
                cur2++;
            if (cur2 > right)
                break;

            ret += right - cur2 + 1;
            cur1++;
        }

        cur1 = left, cur2 = mid + 1;
        while (cur1 <= mid && cur2 <= right)
            tmp[i++] = nums[cur1] <= nums[cur2] ? nums[cur2++] : nums[cur1++];

        while (cur1 <= mid)
            tmp[i++] = nums[cur1++];
        while (cur2 <= right)
            tmp[i++] = nums[cur2++];

        for (int j = left; j <= right; j++)
            nums[j] = tmp[j - left];

        return ret;
    }

    int mySqrt(int x)
    {
        if (x < 1)
            return 0;
        int left = 1, right = x;
        while (left < right)
        {
            int mid = left + (right - left + 1) / 2;
            if (mid * mid <= x)
                left = mid;
            else
                right = mid - 1;
        }
        return left;
    }

    ListNode *swapPairs(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *newhead = new ListNode(0);
        ListNode *prev = newhead;
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

        prev = newhead->next;
        delete newhead;
        return prev;
    }

    string convert(string s, int numRows)
    {
        if (numRows == 1)
            return s;

        string ret;
        int n = s.size(), d = 2 * numRows - 2;

        for (int i = 0; i < n; i += d)
            ret += s[i];

        for (int k = 1; k < numRows - 1; k++)
            for (int i = k, j = d - k; i < n || j < n; i += d, j += d)
            {
                if (i < n)
                    ret += s[i];
                if (j < n)
                    ret += s[j];
            }

        for (int i = numRows - 1; i < n; i += d)
            ret += s[i];

        return ret;
    }

    string addBinary(string a, string b)
    {
        int n = a.size(), m = b.size();
        string ret;
        // reverse(a.begin(), a.end());
        // reverse(b.begin(), b.end());

        int i = n - 1, j = m - 1, t = 0;
        while (i || j || t)
        {
            if (i)
                t += (a[i--] - '0');
            if (j)
                t += (b[i--] - '0');
            // t += (a[i--] - '0') + (b[i--] - '0');
            ret += (t % 2 + '0');
            t /= 2;
        }

        reverse(ret.begin(), ret.end());
        return ret;
    }

    string multiply(string num1, string num2)
    {
        int m = num1.size(), n = num2.size();
        reverse(num1.begin(), num1.end());
        reverse(num2.begin(), num2.end());

        string ret;
        vector<int> tmp(m + n - 1);

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                tmp[i + j] += (num1[i] - '0') * (num2[j] - '0');

        int cur = 0, t = 0;
        while (cur < m + n - 1 || t)
        {
            if (cur < m + n - 1)
                t += tmp[cur++];
            ret += (t % 10 + '0');
            t /= 10;
        }

        while (ret.size() && ret.back() == '0')
            ret.pop_back();

        reverse(ret.begin(), ret.end());
        return ret;
    }

    int tmp[50010];
    int reversePairs(vector<int> &nums)
    {
        return mergesort(nums, 0, nums.size() - 1);
    }

    int mergesort(vector<int> &nums, int left, int right)
    {
        if (left >= right)
            return 0;

        int ret = 0;
        int mid = left + (right - left) / 2;
        ret += mergesort(nums, left, mid);
        ret += mergesort(nums, mid + 1, right);

        int cur1 = left, cur2 = mid + 1, i = 0;
        while (cur1 <= mid && cur2 <= right)
        {
            if (nums[cur1] <= nums[cur2])
                tmp[i++] = nums[cur1++];
            else
            {
                ret += mid - cur1 + 1;
                tmp[i++] = nums[cur2++];
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

    string multiply(string num1, string num2)
    {
        int m = num1.size(), n = num2.size();

        string ret;
        vector<int> tmp(m + n - 1);
        for (int i = m - 1; i >= 0; i--)
            for (int j = n - 1; j >= 0; j--)
                tmp[i + j] += (num1[i] - '0') * (num2[j] - '0');

        int cur = m + n - 2, t = 0;
        while (cur >= 0 || t)
        {
            if (cur >= 0)
                t += (tmp[cur--]);
            ret += (t % 10 + '0');
            t /= 10;
        }

        while (ret.size() > 1 && ret[0] == '0')
            ret.erase(ret.begin());

        reverse(ret.begin(), ret.end());
        return ret;
    }

    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        ListNode *head = new ListNode(0);
        ListNode *prev = head;
        ListNode *cur1 = l1, *cur2 = l2;

        int t = 0;
        while (cur1 || cur2 || t)
        {
            if (cur1)
            {
                t += cur1->val;
                cur1 = cur1->next;
            }
            if (cur2)
            {
                t += cur2->val;
                cur2 = cur2->next;
            }

            prev->next = new ListNode(t % 10);
            prev = prev->next;
            t /= 10;
        }

        prev = head->next;
        delete head;
        return prev;
    }

    string addBinary(string a, string b)
    {
        string ret;
        int cur1 = a.size() - 1, cur2 = b.size() - 1;

        int t = 0;
        while (cur1 >= 0 || cur2 >= 0 || t)
        {
            if (cur1 >= 0)
                t += (a[cur1--] - '0');
            if (cur2 >= 0)
                t += (b[cur2--] - '0');
            ret += (t % 2 + '0');
            t /= 2;
        }

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
            while (st.size() && st.top() == popped[i])
            {
                st.pop();
                i++;
            }
        }

        return i == n;
    }

    int waysToStep(int n)
    {
        if (n < 3)
            return n;
        int base = 1000000007, dp1 = 1, dp2 = 2, dp3 = 4, tmp2, tmp3;

        while (n-- != 3)
        {
            tmp3 = dp3, tmp2 = dp2;
            dp3 = (((dp1 + dp2) % base) + dp3) % base;
            dp2 = tmp3;
            dp1 = tmp2;
        }
        return dp3;
    }

    vector<vector<int>> zigzagLevelOrder(TreeNode *root)
    {
        vector<vector<int>> ret;
        if (root == nullptr)
            return ret;

        int level = 1;
        queue<TreeNode *> q;
        q.push(root);

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

            if (level % 2 == 0)
                reverse(tmp.begin(), tmp.end());
            level++;
            ret.push_back(tmp);
        }
        return ret;
    }

    int tmp[50010];
    int reversePairs(vector<int> &nums)
    {
        return merge_Sort(nums, 0, nums.size() - 1);
    }

    int merge_Sort(vector<int> &nums, int left, int right)
    {
        if (left >= right)
            return 0;

        int ret = 0;
        int mid = left + (right - left) / 2;
        ret += merge_Sort(nums, left, mid);
        ret += merge_Sort(nums, mid + 1, right);

        int cur1 = left, cur2 = mid + 1, i = 0;

        while (cur1 <= mid)
        {
            while (cur2 <= right && nums[cur1] <= 2.0 * nums[cur2])
                cur2++;
            if (cur2 > right)
                break;

            ret += mid - cur1 + 1;
            cur1++;
        }

        cur1 = left, cur2 = mid + 1;
        while (cur1 <= mid && cur2 <= right)
            tmp[i++] = nums[cur1] <= nums[cur2] ? nums[cur2++] : nums[cur1++];

        while (cur1 <= mid)
            tmp[i++] = nums[cur1++];
        while (cur2 <= right)
            tmp[i++] = nums[cur2++];
        for (int j = left; j <= right; j++)
            nums[j] = tmp[j - left];

        return ret;
    }

    vector<vector<int>> zigzagLevelOrder(TreeNode *root)
    {
        vector<vector<int>> ret;
        if (root == nullptr)
            return ret;

        int level = 1;
        queue<TreeNode *> q;
        q.push(root);

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

            if (level % 2 == 0)
                reverse(tmp.begin(), tmp.end());
            level++;
            ret.push_back(tmp);
        }

        return ret;
    }

    priority_queue<int, vector<int>, greater<int>> heap;
    int _k;

    void KthLargest(int k, vector<int> &nums)
    {
        _k = k;
        for (auto x : nums)
        {
            heap.push(x);
            if (heap.size() > _k)
                heap.pop();
        }
    }

    int add(int val)
    {
        heap.push(val);
        if (heap.size() > _k)
            heap.pop();
        return heap.top();
    }

    typedef pair<string, int> PSI;

    struct cmp
    {
        bool operator()(const PSI &a, const PSI &b)
        {
            if (a.second == b.second) // 频次相同，字典序按照大根堆排列
            {
                return a.first < b.first;
            }
            return a.second > b.second;
        }
    };

    vector<string> topKFrequent(vector<string> &words, int k)
    {
        // 统计每个单词的频次
        unordered_map<string, int> hash;
        for (auto &s : words)
            hash[s]++;

        // 创建一个大小为K的堆
        priority_queue<PSI, vector<PSI>, cmp> heap;

        for (auto &psi : hash)
        {
            heap.push(psi);
            if (heap.size() > k)
                heap.pop();
        }

        // 提取结果
        vector<string> ret(k);
        for (int i = k - 1; i >= 0; i--)
        {
            ret[i] = heap.top().first;
            heap.pop();
        }
        return ret;
    }
};

int main()
{
    int n, m, q;
    cin >> n >> m >> q;

    vector<vector<int>> nums(n, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> nums[i][j];

    vector<vector<long long>> dp(n + 1, vector<long long>(m + 1));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1] + nums[i - 1][j - 1];

    int x1, y1, x2, y2;
    while (q--)
    {
        cin >> x1 >> y1 >> x2 >> y2;
        cout << dp[x2][y2] - dp[x1 - 1][y2] - dp[x2][y1 - 1] + dp[x1 - 1][y1 - 1] << endl;
    }
    return 0;
}