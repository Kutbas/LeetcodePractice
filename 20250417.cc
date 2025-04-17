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
    vector<int> findSubstring(string s, vector<string> &words)
    {
        int m = words.size(), len = words[0].size();
        unordered_map<string, int> hash1;
        vector<int> ret;
        for (auto word : words)
            hash1[word]++;

        for (int i = 0; i < len; i++)
        {
            unordered_map<string, int> hash2;
            for (int left = i, right = i, count = 0; right + len <= s.size(); right += len)
            {
                string in = s.substr(right, len);
                ++hash2[in];
                if (hash1.count(in) && hash2[in] <= hash1[in])
                    count++;

                while (right - left + 1 > m * len)
                {
                    string out = s.substr(left, len);
                    if (hash1.count(out) && hash2[out] <= hash1[out])
                        count--;
                    hash2[out]--;
                    left += len;
                }
                if (count == m)
                    ret.push_back(left);
            }
        }

        return ret;
    }

    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        return mergeSort(lists, 0, lists.size() - 1);
    }

    ListNode *mergeSort(vector<ListNode *> &lists, int left, int right)
    {
        if (left > right)
            return nullptr;
        if (left == right)
            return lists[left];

        int mid = left + (right - left) / 2;
        ListNode *l1 = mergeSort(lists, left, mid);
        ListNode *l2 = mergeSort(lists, mid + 1, right);

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

        prev = head->next;
        delete head;
        return prev;
    }

    int calculate(string s)
    {
        int ret = 0, n = s.size();
        vector<int> st;
        char op = '+';

        for (int i = 0; i < n;)
        {
            if (s[i] == ' ')
            {
                i++;
                continue;
            }
            else if (s[i] >= '0' && s[i] <= '9')
            {
                int t = 0;
                while (i < n && s[i] >= '0' && s[i] <= '9')
                {
                    t += t * 10 + (s[i] - '0');
                    i++;
                }
                if (op == '+')
                    st.push_back(t);
                else if (op == '-')
                    st.push_back(-t);
                else if (op == '*')
                    st.back() *= t;
                else
                    st.back() /= t;
            }
            else
                op = s[i++];
        }

        for (auto tmp : st)
            ret += tmp;
        return ret;
    }

    bool CheckPermutation(string s1, string s2)
    {
        if (s1.size() != s2.size())
            return false;
        int hash[128] = {0};
        for (auto ch : s1)
            hash[ch]++;

        for (auto ch : s2)
        {
            if (--hash[ch] < 0)
                return false;
        }

        return true;
    }

    string countAndSay(int n)
    {
        string ret = "1";

        for (int i = 1; i < n; i++)
        {
            int len = ret.size();
            string tmp;
            for (int left = 0, right = 0; right < len;)
            {
                while (right < n && ret[left] == ret[right])
                    right++;
                tmp += to_string(right - left) + ret[left];
                left = right;
            }
            ret = tmp;
        }

        return ret;
    }

    string minWindow(string s, string t)
    {
        int begin = -1, minlen = INT_MAX;
        int m = t.size();
        int hash1[128] = {0};
        int hash2[128] = {0};
        for (auto ch : t)
            hash1[ch]++;

        for (int left = 0, right = 0, count = 0; right < s.size(); right++)
        {
            char in = s[right];
            if (++hash2[in] <= hash1[in])
                count++;

            while (count == m)
            {
                char out = s[left++];
                if (hash2[out]-- <= hash1[out])
                    count--;

                if (right - left + 1 < minlen)
                {
                    minlen = right - left + 1;
                    begin = left;
                }
            }
        }

        return begin == -1 ? "" : s.substr(begin, minlen);
    }

    void duplicateZeros(vector<int> &arr)
    {
        int n = arr.size(), dest = -1, cur = 0;
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

    int findPeakElement(vector<int> &nums)
    {
        int left = 0, right = nums.size() - 1;
        while (left < right)
        {
            int mid = left + (right - left + 1) / 2;
            if (nums[mid] > nums[mid - 1])
                left = mid;
            else
                right = mid - 1;
        }
        return left;
    }

    vector<int> ret;
    vector<int> index;
    vector<int> tmp;
    vector<int> tmpIndex;
    vector<int> countSmaller(vector<int> &nums)
    {
        int n = nums.size();
        ret.resize(n);
        index.resize(n);
        tmp.resize(n);
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

        return;
    }

    int triangleNumber(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int ret = 0;
        for (int i = n - 1; i >= 2; i--)
        {
            int left = 0, right = i - 1;
            while (left < right)
            {
                if (nums[left] + nums[right] > nums[i])
                {
                    ret += right - left - 1;
                    right--;
                }
                else
                    left++;
            }
        }
        return ret;
    }

    int lastStoneWeight(vector<int> &stones)
    {
        priority_queue<int> q;
        for (auto n : stones)
            q.push(n);

        while (q.size() > 1)
        {
            int a = q.top();
            q.pop();
            int b = q.top();
            q.pop();
            if (a > b)
                q.push(a - b);
        }
        return q.empty() ? 0 : q.top();
    }
};
