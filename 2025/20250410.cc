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
    bool containsNearbyDuplicate(vector<int> &nums, int k)
    {
        unordered_map<int, int> hash;

        for (int i = 0; i < nums.size(); i++)
        {
            if (hash.count(nums[i]))
            {
                if (i - hash[nums[i]] <= k)
                    return true;
            }
            hash[nums[i]] = i;
        }
        return false;
    }

    vector<vector<string>> groupAnagrams(vector<string> &strs)
    {
        unordered_map<string, vector<string>> hash;

        // 把所有的字母异位词分组
        for (auto &s : strs)
        {
            string tmp = s;
            sort(tmp.begin(), tmp.end());

            hash[tmp].push_back(s);
        }

        // 提取结果
        vector<vector<string>> ret;

        for (auto &[x, y] : hash)
        {
            ret.push_back(y);
        }
        return ret;
    }

    string longestCommonPrefix(vector<string> &strs)
    {
        string ret = strs[0];
        for (int i = 1; i < strs.size(); i++)
        {
            ret = findCommon(ret, strs[i]);
        }
        return ret;
    }

    string findCommon(string &s1, string &s2)
    {
        int i = 0;
        while (i < min(s1.size(), s2.size()) && s1[i] == s2[i])
            i++;
        return s1.substr(0, i);
    }

    string longestCommonPrefix(vector<string> &strs)
    {
        for (int i = 0; i < strs[0].size(); i++)
        {
            char tmp = strs[0][i];
            for (int j = 1; j < strs.size(); j++)
            {
                if (i == strs[j].size() || tmp != strs[j][i])
                    return strs[0].substr(0, i);
            }
        }
        return strs[0];
    }

    vector<vector<int>> generate(int numRows)
    {
        vector<vector<int>> ret(numRows);
        ret[0].resize(1);
        ret[0][0] = 1;

        for (int i = 1; i < numRows; i++)
        {
            ret[i].resize(i + 1);
            ret[i][0] = ret[i][i] = 1;
            for (int j = 1; j < i; j++)
                ret[i][j] = ret[i - 1][j] + ret[i - 1][j - 1];
        }

        return ret;
    }

    int singleNumber(vector<int> &nums)
    {
        int ret = 0;
        for (int i = 0; i < 32; i++)
        {
            int count = 0;
            for (auto n : nums)
            {
                if ((n >> i) & 1 == 1)
                    count++;
            }

            count %= 3;
            if (count == 1)
                ret |= (1 << i);
        }

        return ret;
    }

    void duplicateZeros(vector<int> &nums)
    {
        int dest = -1, cur = 0, n = nums.size();
        while (cur < n)
        {
            if (nums[cur])
                dest++;
            else
                dest += 2;
            if (dest > n - 1)
                break;
            cur++;
        }

        if (dest == n)
        {
            nums[n - 1] = 0;
            cur--;
            dest -= 2;
        }

        while (cur >= 0)
        {
            if (nums[cur])
                nums[dest--] = nums[cur--];
            else
            {
                nums[dest--] = 0;
                nums[dest--] = 0;
                cur--;
            }
        }
    }

    bool isPalindrome(string s)
    {
        string tmp;
        for (auto &ch : s)
        {
            if (isalnum(ch))
                tmp += tolower(ch);
        }

        int n = tmp.size();
        for (int i = 0, j = n - 1; i < j; i++, j--)
            if (tmp[i] != tmp[j])
                return false;
        return true;
    }

    vector<int> tmp;

    vector<int> sortArray(vector<int> &nums)
    {
        int n = nums.size();
        tmp.resize(n);
        mergeSort(nums, 0, n - 1);
        return nums;
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
            tmp[i++] = nums[cur1] <= nums[cur2] ? nums[cur1++] : nums[cur2++];
        }

        while (cur1 <= mid)
        {
            tmp[i++] = nums[cur1++];
        }
        while (cur2 <= right)
        {
            tmp[i++] = nums[cur2++];
        }

        for (int j = left; j <= right; j++)
            nums[j] = tmp[j - left];
    }

    bool isUnique(string astr)
    {
        if (astr.size() > 26)
            return false;

        int bitMap = 0;
        for (auto ch : astr)
        {
            int i = ch - 'a';
            if ((bitMap >> i) & 1 == 1)
                return false;
            bitMap |= (1 << i);
        }
        return true;
    }

    string minWindow(string s, string t)
    {
        int begin = -1, minlen = INT_MAX, m = t.size();
        int hash1[128] = {0};
        int hash2[128] = {0};

        for (auto ch : t)
            hash1[ch]++;

        for (int left = 0, right = 0, count = 0; right < s.size(); right++)
        {
            char in = s[right];
            if (++hash2[in] <= hash1[in])
                count++;

            while (count > m)
            {
                char out = s[left++];
                if (hash2[out]-- <= hash1[out])
                    count--;
            }

            if (count == m)
            {
                if (right - left + 1 < minlen)
                {
                    minlen = right - left + 1;
                    begin = left;
                }
            }
        }

        return begin == -1 ? "" : s.substr(begin, minlen);
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

    vector<vector<int>> matrixBlockSum(vector<vector<int>> &mat, int k)
    {
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1] + mat[i - 1][j - 1];

        vector<vector<int>> ret(m, vector<int>(n));

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                int x1 = max(0, i - k) + 1, y1 = max(0, j - k) + 1;
                int x2 = min(m - 1, i + k) + 1, y2 = min(n - 1, j + k) + 1;

                ret[i][j] = dp[x2][y2] - dp[x1 - 1][y2] - dp[x2][y1 - 1] + dp[x1 - 1][y1 - 1];
            }

        return ret;
    }

    int waysToStep(int n)
    {
        if (n < 3)
            return n;

        int base = 1000000007;
        int dp1 = 1, dp2 = 2, dp3 = 4, tmp2, tmp3;

        while (n-- != 2)
        {
            tmp2 = dp2, tmp3 = dp3;
            dp3 = (((dp1 + dp2) % base) + dp3) % base;
            dp2 = tmp3;
            dp1 = tmp2;
        }
        return dp3;
    }

    void reorderList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr || head->next->next)
            return;

        ListNode *slow = head, *fast = head;

        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode *head2 = new ListNode(0);
        ListNode *cur = slow->next;
        slow->next = nullptr;

        while (cur)
        {
            ListNode *next = cur->next;
            cur->next = head2->next;
            head2->next = cur;
            cur = next;
        }

        ListNode *ret = new ListNode(0);
        ListNode *prev = ret;
        ListNode *cur1 = head, *cur2 = head2->next;

        while (cur1)
        {
            prev->next = cur1;
            cur1 = cur1->next;
            prev = prev->next;

            if (cur2)
            {
                prev->next = cur2;
                cur2 = cur2->next;
                prev = prev->next;
            }
        }

        delete head2, ret;
    }
};