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

class Solution
{
public:
    string removeDuplicates(string s)
    {
        string ret;
        for (auto ch : s)
        {
            if (ret.size() && ch == ret.back())
                ret.pop_back();
            else
                ret += ch;
        }

        return ret;
    }

    string changeStr(string &s)
    {
        string ret;
        for (auto ch : s)
        {
            if (ch != '#')
                ret += ch;
            else if (ret.size())
                ret.pop_back();
        }
        return ret;
    }

    bool backspaceCompare(string s, string t)
    {
        return changeStr(s) == changeStr(t);
    }

    int calculate(string s)
    {
        vector<int> st;
        int i = 0, n = s.size();
        char op = '+';

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
                    st.push_back(tmp);
                else if (op == '-')
                    st.push_back(-tmp);
                else if (op == '*')
                    st.back() *= tmp;
                else
                    st.back() /= tmp;
            }
            else
            {
                op = s[i];
                i++;
            }
        }
        int ret = 0;
        for (auto n : st)
            ret += n;

        return ret;
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

    int getSum(int a, int b)
    {
        while (b)
        {
            int tmp = a ^ b;
            int carry = (a & b) << 1;
            a = tmp;
            b = carry;
        }
        return a;
    }

    int calculate(string s)
    {
        vector<int> st;
        int n = s.size();
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
                    st.push_back(tmp);

                else if (op == '-')
                    st.push_back(-tmp);

                else if (op == '*')
                    st.back() *= tmp;

                else if (op == '/')
                    st.back() /= tmp;
            }
            else
            {
                op = s[i++];
            }
        }

        int ret = 0;
        for (auto n : st)
            ret += n;
        return ret;
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

    vector<int> ret;
    vector<int> index;
    int tmp[50010];
    int tmpIndex[50010];

    vector<int> countSmaller(vector<int> &nums)
    {
        int n = nums.size();
        ret.resize(n);
        index.resize(n);

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
                tmp[i] = nums[cur2];
                tmpIndex[i++] = index[cur2++];
            }
            else
            {
                ret[index[cur1]] = right - cur2 + 1;

                tmp[i] = nums[cur1];
                tmpIndex[i++] = index[cur1++];
            }
        }

        while (cur1 <= mid)
        {
            tmp[i] = nums[cur1];
            tmpIndex[i++] = index[cur1++];
        }

        while (cur2 <= right)
        {
            tmp[i] = nums[cur2];
            tmpIndex[i++] = index[cur2++];
        }

        for (int j = left; j <= right; j++)
        {
            nums[j] = tmp[j - left];
            index[j] = tmpIndex[j - left];
        }
    }

    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        return merge(lists, 0, lists.size() - 1);
    }

    ListNode *merge(vector<ListNode *> lists, int left, int right)
    {
        if (left > right)
            return nullptr;
        if (left == right)
            return lists[left];

        int mid = left + (right - left) / 2;

        ListNode *l1 = merge(lists, left, mid);
        ListNode *l2 = merge(lists, mid + 1, right);

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

                prev = prev->next;
                cur1 = cur1->next;
            }
            else
            {
                prev->next = cur2;

                prev = prev->next;
                cur2 = cur2->next;
            }
        }

        if (cur1)
            prev->next = cur1;
        if (cur2)
            prev->next = cur2;

        return head;
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

    int triangleNumber(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());

        int ret = 0, n = nums.size();

        for (int i = n - 1; i >= 2; i--)
        {
            int left = 0, right = i - 2;
            while (left < right)
            {
                if (nums[left] + nums[right] > nums[i])
                {
                    ret += right - left;
                    left++;
                    right--;
                }
                else
                    left++;
            }
        }

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
            t /= 10;
            prev = prev->next;
        }

        prev = head->next;
        delete head;
        return prev;
    }

    int calculate(string s)
    {
        vector<int> st;
        int n = s.size();
        char op = '+';

        for (int i = 0; i < n;)
        {
            if (s[i] == ' ')
                i++;
            else if (s[i] >= '0' && s[i] <= '9')
            {
                int tmp = 0;
                while (i < n && s[i] >= '0' && s[i] <= '9')
                    tmp = tmp * 10 + (s[i++] - '0');

                if (op == '+')
                    st.push_back(tmp);
                else if (op == '-')
                    st.push_back(-tmp);
                else if (op == '*')
                    st.back() *= tmp;
                else
                    st.back() /= tmp;
            }
            else
                op = s[i++];
        }

        int ret = 0;
        for (auto n : st)
            ret += n;
        return ret;
    }

    vector<int> ret;
    vector<int> index;
    vector<int> tmpnums;
    vector<int> tmpindex;
    // int tmp[]

    vector<int> countSmaller(vector<int> &nums)
    {
        int n = nums.size();

        ret.resize(n);
        index.resize(n);
        tmpnums.resize(n);
        tmpindex.resize(n);

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

        int i = 0, cur1 = left, cur2 = mid + 1;
        while (cur1 <= mid && cur2 <= right)
        {
            if (nums[cur1] <= nums[cur2])
            {
                tmpnums[i] = nums[cur2];
                tmpindex[i++] = index[cur2++];
            }
            else
            {
                ret[index[cur1]] += right - cur2 + 1;
                tmpnums[i] = nums[cur1];
                tmpindex[i++] = index[cur1++];
            }
        }

        while (cur1 <= mid)
        {
            tmpnums[i] = nums[cur1];
            tmpindex[i++] = index[cur1++];
        }

        while (cur2 <= right)
        {
            tmpnums[i] = nums[cur2];
            tmpindex[i++] = index[cur2++];
        }

        for (int j = left; j <= right; j++)
        {
            nums[j] = tmpnums[j - left];
            index[j] = tmpindex[j - left];
        }
    }

    vector<int> missingTwo(vector<int> &nums)
    {
        int xorsum = 0;
        for (auto n : nums)
            xorsum ^= n;
        for (int i = 1; i <= nums.size() + 2; i++)
            xorsum ^ i;

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

    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        return Merge(lists, 0, lists.size() - 1);
    }

    ListNode *Merge(vector<ListNode *> &lists, int left, int right)
    {
        if (left > right)
            return nullptr;
        if (left == right)
            return lists[left];

        int mid = left + (right - left) / 2;
        ListNode *l1 = Merge(lists, left, mid);
        ListNode *l2 = Merge(lists, mid + 1, right);

        return Merge2Lists(l1, l2);
    }

    ListNode *Merge2Lists(ListNode *l1, ListNode *l2)
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

                prev = prev->next;
                cur1 = cur1->next;
            }
            else
            {
                prev->next = cur2;

                prev = prev->next;
                cur2 = cur2->next;
            }
        }

        if (cur1)
            prev->next = cur1;
        if (cur2)
            prev->next = cur2;

        return head->next;
    }
};

int main()
{

    return 0;
}