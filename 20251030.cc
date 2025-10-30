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
    void sortColors(vector<int> &nums)
    {
        int n = nums.size(), i = 0, left = -1, right = n;

        while (i < right)
        {
            if (nums[i] < 1)
                swap(nums[i++], nums[++left]);
            else if (nums[i] == 1)
                i++;
            else
                swap(nums[i], nums[--right]);
        }
    }

    // 2
    int longestOnes(vector<int> &nums, int k)
    {
        int n = nums.size(), ret = 0;
        for (int left = 0, right = 0, count = 0; right < n; right++)
        {
            if (nums[right] == 0)
                count++;
            while (count > k)
                if (nums[left++] == 0)
                    count--;
            ret = max(ret, right - left + 1);
        }

        return ret;
    }

    // 3
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

    // 4
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

    // 5
    int search(vector<int> &nums, int target)
    {
        int n = nums.size(), left = 0, right = n - 1;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] < target)
                left = mid + 1;
            else if (nums[mid] > target)
                right = mid - 1;
            else
                return mid;
        }

        return -1;
    }

    // 6
    bool validateStackSequences(vector<int> &pushed, vector<int> &popped)
    {
        int n = pushed.size(), i = 0;
        stack<int> st;

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

    // 7
    string convert(string s, int numRows)
    {
        if (numRows == 1)
            return s;

        int n = s.size(), d = 2 * numRows - 2;
        string ret;
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

    // 8
    string removeDuplicates(string s)
    {
        string ret;
        for (char ch : s)
        {
            if (ret.size() && ret.back() == ch)
                ret.pop_back();
            else
                ret += ch;
        }
        return ret;
    }

    // 9
    vector<int> ret;
    vector<int> tmp;
    vector<int> index;
    vector<int> tmpindex;
    vector<int> countSmaller(vector<int> &nums)
    {
        int n = nums.size();
        ret.resize(n);
        tmp.resize(n);
        index.resize(n);
        tmpindex.resize(n);
        for (int i = 0; i < n; i++)
            index[i] = i;

        mergeSort(nums, 0, nums.size() - 1);

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
                tmp[i] = nums[cur2];
                tmpindex[i++] = index[cur2++];
            }
            else
            {
                ret[index[cur1]] += right - cur2 + 1;
                tmp[i] = nums[cur1];
                tmpindex[i++] = index[cur1++];
            }
        }
        while (cur1 <= mid)
        {
            tmp[i] = nums[cur1];
            tmpindex[i++] = index[cur1++];
        }
        while (cur2 <= right)
        {
            tmp[i] = nums[cur2];
            tmpindex[i++] = index[cur2++];
        }

        for (int j = left; j <= right; j++)
        {
            nums[j] = tmp[j - left];
            index[j] = tmpindex[j - left];
        }
    }

    // 11
    vector<int> sortArray(vector<int> &nums)
    {
        srand(time(nullptr));
        quickSort(nums, 0, nums.size() - 1);
        return nums;
    }

    int getRandom(vector<int> &nums, int left, int right)
    {
        int r = rand();
        return nums[r % (right - left + 1) + left];
    }

    void quickSort(vector<int> &nums, int l, int r)
    {
        if (l >= r)
            return;

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

        quickSort(nums, l, left);
        quickSort(nums, right, r);
    }

    // 12
    bool isUnique(string astr)
    {
        if (astr.size() > 26)
            return false;

        int bitMap = 0;
        for (char ch : astr)
        {
            int i = ch - 'a';
            if (bitMap & (1 << i))
                return false;
            bitMap |= (1 << i);
        }
        return true;
    }
};

// 10
class MedianFinder
{
public:
    MedianFinder()
    {
    }

    void addNum(int num)
    {
        if (left.size() == right.size())
        {
            if (left.empty() || num < left.top())
                left.push(num);
            else
            {
                right.push(num);
                left.push(right.top());
                right.pop();
            }
        }
        else
        {
            if (num > right.top())
                right.push(num);
            else
            {
                left.push(num);
                right.push(left.top());
                left.pop();
            }
        }
    }

    double findMedian()
    {
        return left.size() == right.size() ? (left.top() + right.top() / 2.0) : left.top();
    }

private:
    priority_queue<int> left;
    priority_queue<int, vector<int>, greater<int>> right;
};