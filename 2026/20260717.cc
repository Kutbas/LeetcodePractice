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
#include <regex>
#include <map>
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
    void duplicateZeros(vector<int> &arr)
    {
        int n = arr.size(), cur = 0, dest = -1;

        while (cur < n)
        {

            if (arr[cur])
                dest++;
            else
                dest += 2;

            if (dest >= n - 1)
                break;

            cur++;
        }

        if (dest == n)
        {
            arr[n - 1] = 0;
            cur--;
            dest -= 2;
        }

        while (cur >= 0)
        {
            if (arr[cur])
                arr[dest--] = arr[cur--];
            else
            {
                arr[dest--] = 0;
                arr[dest--] = 0;
                cur--;
            }
        }
    }

    // 2
    vector<int> smallestK(vector<int> &arr, int k)
    {
        srand(time(nullptr));
        quickSort(arr, 0, arr.size() - 1, k);
        return {arr.begin(), arr.begin() + k};
    }

    int getRandom(vector<int> &arr, int left, int right)
    {
        int r = rand();
        return arr[r % (right - left + 1) + left];
    }

    void quickSort(vector<int> &nums, int l, int r, int k)
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

        int lRange = left - l + 1, mRange = (right - 1) - (left + 1) + 1;
        if (lRange >= k)
            quickSort(nums, l, left, k);
        else if (lRange + mRange >= k)
            return;
        else
            quickSort(nums, right, r, k - lRange - mRange);
    }

    // 3
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

    // 4
    bool containsDuplicate(vector<int> &nums)
    {
        unordered_map<int, int> hash;

        for (auto n : nums)
            if (hash.count(n))
                return true;
            else
                hash[n]++;

        return false;
    }

    // 5
    typedef pair<TreeNode *, unsigned int> PTI;
    int widthOfBinaryTree(TreeNode *root)
    {
        vector<PTI> q;
        q.push_back({root, 1});

        unsigned int ret = 1;
        while (q.size())
        {
            vector<PTI> tmp;
            auto [x1, y1] = q[0];
            auto [x2, y2] = q.back();

            ret = max(ret, y2 - y1 + 1);

            // if(x1->left)
            //     tmp.push_back({x1->left,2*y1});
            // if(x1->right)
            //     tmp.push_back({x1->right,2*y1+1});
            // if(x2->left)
            //     tmp.push_back({x2->left,2*y2});
            // if(x2->right)
            //     tmp.push_back({x2->right,2*y2+1});
            for (auto [x, y] : q)
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

    // 6
    int hammingDistance(int x, int y)
    {
        int ret = 0;

        for (int i = 0; i < 32; i++)
        {
            int a = (x >> i) & 1;
            int b = (y >> i) & 1;
            if (a != b)
                ret++;
        }

        return ret;
    }

    // 7
    int tmp[50010];
    int reversePairs(vector<int> &nums)
    {
        return mergeSort(nums, 0, nums.size() - 1);
    }

    int mergeSort(vector<int> &nums, int left, int right)
    {
        if (left >= right)
            return 0;

        int ret = 0, mid = left + (right - left) / 2;
        ret += mergeSort(nums, left, mid);
        ret += mergeSort(nums, mid + 1, right);

        int i = 0, cur1 = left, cur2 = mid + 1;
        while (cur1 <= mid && cur2 <= right)
        {
            if (nums[cur1] / 2.0 <= nums[cur2])
                cur2++;
            else
            {
                ret += right - cur2 + 1;
                cur1++;
            }
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

    // 8
    ListNode *swapPairs(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *tmp = swapPairs(head->next->next);
        ListNode *newhead = head->next;
        newhead->next = head;
        head->next = tmp;

        return newhead;
    }

    // 9
    ListNode *swapPairs(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *ret = new ListNode(0);
        ListNode *prev = ret, *cur = head, *next = cur->next, *nnext = next->next;

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

    // 10
    vector<vector<int>> ret;
    vector<int> path;
    int aim, sum = 0;
    vector<vector<int>> combinationSum(vector<int> &candidates, int target)
    {
        aim = target;
        dfs(candidates, 0);
        return ret;
    }

    void dfs(vector<int> &nums, int pos)
    {
        if (sum > aim)
            return;

        if (sum == aim)
        {
            ret.push_back(path);
            return;
        }

        for (int i = pos; i < nums.size(); i++)
        {
            sum += nums[i];
            path.push_back(nums[i]);
            dfs(nums, i);
            path.pop_back();
            sum -= nums[i];
        }
    }
};