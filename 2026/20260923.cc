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
    int getSum(int a, int b)
    {
        while (b)
        {
            int x = a ^ b;
            int carry = (a & b) << 1;
            a = x;
            b = carry;
        }

        return a;
    }

    // 2
    int minNumberOfFrogs(string croakOfFrogs)
    {
        string s = "croak";
        int n = s.size();
        unordered_map<char, int> index;
        for (int i = 0; i < n; i++)
            index[s[i]] = i;

        int hash[5] = {0};
        for (char ch : croakOfFrogs)
        {
            if (ch == 'c')
            {
                if (hash[n - 1])
                    hash[n - 1]--;
                hash[0]++;
            }
            else
            {
                int in = index[ch];
                if (hash[in - 1] == 0)
                    return -1;
                hash[in - 1]--;
                hash[in]++;
            }
        }

        for (int i = 0; i < n - 1; i++)
            if (hash[i])
                return -1;

        return hash[n - 1];
    }

    // 3
    vector<int> ret;
    vector<int> tmp;
    vector<int> index;
    vector<int> tmpIndex;
    vector<int> countSmaller(vector<int> &nums)
    {
        int n = nums.size();
        ret.resize(n);
        tmp.resize(n);
        index.resize(n);
        tmpIndex.resize(n);

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
                tmpIndex[i++] = index[cur2++];
            }
            else
            {
                ret[index[cur1]] += right - cur2 + 1;
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

    // 4
    ListNode *reverseList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *newhead = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;

        return newhead;
    }

    void reorderList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return;

        ListNode *slow = head, *fast = head->next;
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode *head2 = slow->next;
        slow->next = nullptr;
        head2 = reverseList(head2);

        ListNode *ret = new ListNode(0);
        ListNode *prev = ret;
        ListNode *cur1 = head, *cur2 = head2;
        while (cur1 || cur2)
        {
            if (cur1)
            {
                prev->next = cur1;
                cur1 = cur1->next;
                prev = prev->next;
            }
            if (cur2)
            {
                prev->next = cur2;
                cur2 = cur2->next;
                prev = prev->next;
            }
        }

        prev = ret->next;
        delete ret;
        // return prev;
    }

    // 5
    string hash[10] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    vector<string> ret;
    string path;
    vector<string> letterCombinations(string digits)
    {
        dfs(digits, 0);
        return ret;
    }

    void dfs(string &s, int pos)
    {
        if (pos == s.size())
        {
            ret.push_back(path);
            return;
        }

        for (char ch : hash[s[pos] - '0'])
        {
            path.push_back(ch);
            dfs(s, pos + 1);
            path.pop_back();
        }
    }

    // 6
    bool lemonadeChange(vector<int> &bills)
    {
        int hash[21] = {0};

        for (auto n : bills)
        {
            if (n == 5)
                hash[5]++;
            else if (n == 10)
            {
                if (!hash[5])
                    return false;

                hash[5]--, hash[10]++;
            }
            else
            {
                if (hash[5] && hash[10])
                    hash[5]--, hash[10]--;
                else if (hash[5] >= 3)
                    hash[5] -= 3;
                else
                    return false;
            }
        }

        return true;
    }

    // 7
    int getMaxLen(vector<int> &nums)
    {
        int n = nums.size(), ret = 0;
        vector<int> f(n + 1);
        auto g = f;

        for (int i = 1; i <= n; i++)
        {
            if (nums[i - 1] > 0)
            {
                f[i] = f[i - 1] + 1;
                g[i] = g[i - 1] == 0 ? 0 : g[i - 1] + 1;
            }
            else if (nums[i - 1] < 0)
            {
                f[i] = g[i - 1] == 0 ? 0 : g[i - 1] + 1;
                g[i] = f[i - 1] + 1;
            }
            ret = max(ret, f[i]);
        }

        return ret;
    }

    // 8
    string reverseStr(string s, int k)
    {
        int n = s.size();
        for (int i = 0; i < n; i += 2 * k)
        {
            int right = min(i + k, n);
            reverse(s.begin() + i, s.begin() + right);
        }

        return s;
    }
};