
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
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        ListNode *cur1 = l1, *cur2 = l2;
        ListNode *newhead = new ListNode(0);

        ListNode *prev = newhead; // 尾指针
        int t = 0;                // 记录进位
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

        prev = newhead->next;
        delete newhead;
        return prev;
    }

    ListNode *swapPairs(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *newhead = new ListNode(0);
        newhead->next = head;
        ListNode *prev = newhead; // 尾指针

        ListNode *cur = head, *next = head->next, *nnext = next->next;

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

        cur = newhead->next;
        delete newhead;

        return cur;
    }

    void reorderList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr || head->next->next == nullptr)
            return;

        // 找到链表的中间节点
        ListNode *slow = head, *fast = head;

        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        // 把后面的部分逆序
        ListNode *head2 = new ListNode(0);
        ListNode *cur = slow->next;
        slow->next = nullptr; // 把两个链表断开

        while (cur)
        {
            ListNode *next = cur->next;
            cur->next = head2->next;
            head2->next = cur;
            cur = next;
        }

        // 合并两个链表
        ListNode *ret = new ListNode(0);
        ListNode *prev = ret;
        ListNode *cur1 = head, *cur2 = head2->next;

        while (cur1)
        {
            // 先放第一个链表
            prev->next = cur1;
            cur1 = cur1->next;
            prev = prev->next;

            if (cur2)
            {
                prev->next = cur2;
                prev = prev->next;
                cur2 = cur2->next;
            }
        }

        delete head2, ret;
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

    int triangleNumber(vector<int> &nums)
    {
        int ret = 0;
        sort(nums.begin(), nums.end());

        int n = nums.size();

        for (int i = n - 1; i >= 2; i--)
        {
            int left = 0, right = i - 1;
            while (left < right)
            {
                if (nums[left] + nums[right] > nums[i])
                {
                    ret += right - left + 1;
                    right--;
                }
                else
                    left++;
            }
        }

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
            hash[sum] = i;
        }

        return ret;
    }

    vector<int> twoSum(vector<int> &nums, int target)
    {
        int left = 0, right = nums.size() - 1;
        while (left < right)
        {
            if (nums[left] + nums[right] < target)
                left++;
            else if (nums[left] + nums[right] > target)
                right--;
            else
                return {nums[left], nums[right]};
        }
        return {-1, -1};
    }

    int bitSum(int n)
    {
        int ret = 0;
        while (n)
        {
            int tmp = n % 10;
            ret += tmp * tmp;
            n /= 10;
        }
        return ret;
    }

    bool isHappy(int n)
    {
        int slow = n, fast = bitSum(n);
        while (slow != fast)
        {
            slow = bitSum(slow);
            fast = bitSum(bitSum(fast));
        }
        return slow == 1;
    }

    vector<int> sortArray(vector<int> &nums)
    {
        srand(time(NULL));
        quickSort(nums, 0, nums.size() - 1);
        return nums;
    }

    // int getRandom(vector<int> &nums, int left, int right)
    // {
    //     int r = rand();
    //     return nums[r % (right - left + 1) + left];
    // }

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

    int longestOnes(vector<int> &nums, int k)
    {
        int ret = 0;
        for (int left = 0, right = 0, count = 0; right < nums.size(); right++)
        {
            if (nums[right] == 0)
                count++;

            while (count > k)
            {
                if (nums[left++] == 0)
                    count--;
            }
            if (count == k)
                ret = max(ret, right - left + 1);
        }

        return ret;
    }

    vector<int> smallestK(vector<int> &nums, int k)
    {
        srand(time(NULL));
        QuickSort(nums, 0, nums.size() - 1);
        return {nums.begin(), nums.begin() + k};
    }

    int getRandom(vector<int> &nums, int left, int right)
    {
        int r = rand();
        return nums[r % (right - left + 1) + left];
    }

    void QuickSort(vector<int> &nums, int l, int r)
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

        QuickSort(nums, l, left);
        QuickSort(nums, right, r);
    }

    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        ListNode *cur1 = l1, *cur2 = l2;
        ListNode *newhead = new ListNode(0);

        ListNode *prev = newhead;

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

        prev = newhead->next;
        delete newhead;
        return prev;
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
            hash[sum] = i;
        }
        return ret;
    }

    int triangleNumber(vector<int> &nums)
    {
        int ret = 0, n = nums.size();

        for (int i = n - 1; i >= 2; i--)
        {
            int left = 0, right = i - 1;
            while (left < right)
            {
                if (nums[left] + nums[right] > i)
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

    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        ListNode *cur1 = l1, *cur2 = l2;
        ListNode *newhead = new ListNode(0);

        ListNode *prev = newhead;

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

        prev = newhead->next;
        delete newhead;

        return prev;
    }
};