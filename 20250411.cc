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
    string longestPalindrome(string s)
    {
        int begin = 0, len = 0, n = s.size();
        for (int i = 0; i < n; i++)
        {
            // 先做一次奇数长度的扩展
            int left = i, right = i;
            while (left >= 0 && right < n && s[left] == s[right])
            {
                left++;
                right--;
            }
            if (right - left - 1 > len)
            {
                begin = left + 1;
                len = right - left - 1;
            }
            // 再做一次偶数长度的扩展
            left = i, right = i + 1;
            while (left >= 0 && right < n && s[left] == s[right])
            {
                left++;
                right--;
            }
            if (right - left - 1 > len)
            {
                begin = left + 1;
                len = right - left - 1;
            }
        }
        return s.substr(begin, len);
    }

    string addBinary(string a, string b)
    {
        string ret;

        int cur1 = a.size() - 1, cur2 = b.size() - 1, t = 0;
        while (cur1 >= 0 || cur2 >= 0 || t)
        {
            if (cur1 >= 0)
                t += a[cur1--] - '0';
            if (cur2 >= 0)
                t += b[cur2--] - '0';
            ret += t % 2 + '0';
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
        vector<int> tmp(m + n - 1);

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                tmp[i + j] += (num1[i] - '0') * (num2[j] - '0');
            }

        int cur = 0, t = 0;
        string ret;
        while (cur < m + n - 1 || t != 0)
        {
            if (cur < m + n - 1)
                t += tmp[cur++];
            ret += t % 10 + '0';
            t /= 10;
        }

        while (ret.size() > 1 && ret.back() == '0')
            ret.pop_back();

        reverse(ret.begin(), ret.end());
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

    int findPoisonedDuration(vector<int> &timeSeries, int duration)
    {
        int ret = 0, n = timeSeries.size();
        for (int i = 0; i < n - 1; i++)
        {
            int time = timeSeries[i + 1] - timeSeries[i];
            if (time < duration)
                ret += time;
            else
                ret += duration;
        }

        return ret + duration;
    }

    string countAndSay(int n)
    {
        string ret = "1";

        for (int i = 1; i < n; i++)
        {
            string tmp;
            int len = ret.size();
            for (int left = 0, right = 0; right < len;)
            {
                while (ret[left] == ret[right] && right < len)
                    right++;
                tmp += to_string(right - left) + ret[left];
                left = right;
            }

            ret = tmp;
        }

        return ret;
    }

    int findMin(vector<int> &nums)
    {
        int n = nums.size();
        int left = 0, right = n - 1;
        while (left < right)
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] > nums[n - 1])
                left = mid + 1;
            else
                right = mid;
        }
        return nums[left];
    }

    int pivotIndex(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> f(n), g(n);

        for (int i = 1; i < n; i++)
            f[i] = f[i - 1] + nums[i - 1];
        for (int i = n - 2; i >= 0; i--)
            g[i] = g[i + 1] + nums[i + 1];

        for (int i = 0; i < n; i++)
            if (f[i] == g[i])
                return i;
        return -1;
    }

    ListNode *swapPairs(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *newhead = new ListNode(0);
        ListNode *prev = newhead;
        prev->next = head;

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

        cur = newhead->next;
        delete newhead;
        return cur;
    }

    vector<int> singleNumber(vector<int> &nums)
    {
        int xorsum = 0;
        for (auto n : nums)
            xorsum ^= n;

        int lsb = xorsum == INT_MIN ? xorsum : xorsum & (-xorsum);

        int x = 0, y = 0;
        for (auto n : nums)
        {
            if (n & lsb)
                x ^= n;
            else
                y ^= n;
        }

        return {x, y};
    }

    vector<vector<int>> threeSum(vector<int> &nums)
    {
        vector<vector<int>> ret;
        sort(nums.begin(), nums.end());

        int i = 0, n = nums.size();
        while (i < n - 2)
        {
            int left = i + 1, right = n - 2;
            while (left < right)
            {
                if (nums[i] + nums[left] + nums[right] > 0)
                    right--;
                else if (nums[i] + nums[left] + nums[right] < 0)
                    left++;
                else
                {
                    ret.push_back({nums[i], nums[left], nums[right]});

                    do
                    {
                        left++;
                    } while (nums[left] == nums[left - 1] && left < right);

                    do
                    {
                        right--;
                    } while (nums[right] == nums[right + 1] && left < right);
                }
            }

            do
            {
                i++;
            } while (nums[i] == nums[i - 1] && i < n - 2);
        }

        return ret;
    }

    vector<int> findSubstring(string s, vector<string> &words)
    {
        vector<int> ret;
        int m = words.size(), len = words[0].size();

        unordered_map<string, int> hash1;
        for (auto word : words)
            hash1[word]++;

        for (int i = 0; i < len; i++)
        {
            unordered_map<string, int> hash2;

            for (int left = i, right = i, count = 0; right + len <= s.size();
                 right += len)
            {
                string in = s.substr(right, len);
                ++hash2[in];
                if (hash1.count(in) && hash2[in] <= hash1[in])
                    count++;

                while (right - left + 1 > len * m)
                {
                    string out = s.substr(left, len);
                    if (hash1.count(out) && hash2[out] <= hash1[out])
                        count--;
                    --hash2[out];
                    left += len;
                }

                if (count == m)
                    ret.push_back(left);
            }
        }

        return ret;
    }

    int findKthLargest(vector<int> &nums, int k)
    {
        srand(time(NULL));
        return quickSort(nums, 0, nums.size(), k);
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

        int rRange = r - right + 1, mRange = (right - 1) - (left + 1) + 1;
        if (rRange >= k)
            return quickSort(nums, right, r, k);
        else if (rRange + mRange >= k)
            return key;
        else
            return quickSort(nums, l, left, k - rRange - mRange);
    }

    ListNode *swapPairs(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *newhead = new ListNode(0);
        // newhead->next = head;
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

        cur = newhead->next;
        delete newhead;

        return cur;
    }
};

int main()
{
    int n, m, q;
    cin >> n >> m >> q;

    vector<vector<long long>> nums(n, vector<long long>(m));
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