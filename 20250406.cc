#include <bits/stdc++.h>
using namespace std;

// class Solution
// {
//     vector<int> ret;
//     vector<int> index; // 记录nums中当前元素的原始下标
//     int tmpNums[500010];
//     int tmpIndex[500010];

//     int tmp[50010];

// public:
//     vector<int> countSmaller(vector<int> &nums)
//     {
//         int n = nums.size();
//         ret.resize(n);
//         index.resize(n);

//         // 初始化 index 数组
//         for (int i = 0; i < n; i++)
//             index[i] = i;

//         mergeSort(nums, 0, n - 1);
//         return ret;
//     }

//     // void mergeSort(vector<int> &nums, int left, int right)
//     // {
//     //     if (left >= right)
//     //         return;

//     //     // 根据中间元素划分区间
//     //     int mid = left + (right - left) / 2;

//     //     // 先处理左右两部分
//     //     mergeSort(nums, left, mid);
//     //     mergeSort(nums, mid + 1, right);

//     //     // 处理一左一右的情况
//     //     int cur1 = left, cur2 = mid + 1, i = 0;
//     //     while (cur1 <= mid && cur2 <= right) // 降序
//     //     {
//     //         if (nums[cur1] <= nums[cur2])
//     //         {
//     //             tmpNums[i] = nums[cur2];
//     //             tmpIndex[i++] = index[cur2++];
//     //         }
//     //         else
//     //         {
//     //             ret[index[cur1]] += right - cur2 + 1;

//     //             tmpNums[i] = nums[cur1];
//     //             tmpIndex[i++] = index[cur1++];
//     //         }
//     //     }

//     //     // 处理剩下的排序过程
//     //     while (cur1 <= mid)
//     //     {
//     //         tmpNums[i] = nums[cur1];
//     //         tmpIndex[i++] = index[cur1++];
//     //     }
//     //     while (cur2 <= right)
//     //     {
//     //         tmpNums[i] = nums[cur2];
//     //         tmpIndex[i++] = index[cur2++];
//     //     }

//     //     // 还原
//     //     for (int j = left; j <= right; j++)
//     //     {
//     //         nums[j] = tmpNums[j - left];
//     //         index[j] = tmpIndex[j - left];
//     //     }
//     // }

//     int reversePairs(vector<int> &nums)
//     {
//         return mergeSort(nums, 0, nums.size() - 1);
//     }

//     // int mergeSort(vector<int> &nums, int left, int right)
//     // {
//     //     if (left >= right)
//     //         return 0;

//     //     int ret = 0;
//     //     int mid = left + (right - left) / 2;

//     //     // 先计算左右两侧的翻转对
//     //     ret += mergeSort(nums, left, mid);
//     //     ret += mergeSort(nums, mid + 1, right);

//     //     // 计算翻转对的数量
//     //     int cur1 = left, cur2 = mid + 1, i = left;

//     //     while (cur1 <= mid)
//     //     {
//     //         while (cur2 <= right && nums[cur2] * 2 >= nums[cur1] / 2.0)
//     //             cur2++;
//     //         if (cur2 > right)
//     //             break;
//     //         ret += right - cur2 + 1;
//     //         cur1++;
//     //     }

//     //     cur1 = left, cur2 = mid + 1;
//     //     while (cur1 <= mid && cur2 <= right)
//     //     {
//     //         tmp[i++] = nums[cur1] <= nums[cur2] ? nums[cur2++] : nums[cur1++];
//     //     }
//     //     while (cur1 <= mid)
//     //         tmp[i++] = nums[cur1++];
//     //     while (cur2 <= mid)
//     //         tmp[i++] = nums[cur2++];

//     //     for (int j = left; j <= right; j++)
//     //         nums[j] = tmp[j];

//     //     return ret;
//     // }

//     string countAndSay(int n)
//     {
//         string ret = "1";

//         for (int i = 1; i < n; i++)
//         {
//             string tmp;
//             int len = ret.size();
//             for (int left = 0, right = 0; right < len;)
//             {
//                 while (ret[left] == ret[right] && right < len)
//                     right++;
//                 tmp += to_string(right - left) + ret[left];
//                 left = right;
//             }
//             ret = tmp;
//         }

//         return ret;
//     }

//     int search(vector<int> &nums, int target)
//     {
//         int left = 0, right = nums.size() - 1;
//         while (left < right)
//         {
//             int mid = left + (right - left) / 2;
//             if (nums[mid] > target)
//                 right = mid - 1;
//             else if (nums[mid] < target)
//                 left = mid + 1;
//             else
//                 return mid;
//         }

//         return -1;
//     }

//     int findKthLargest(vector<int> &nums, int k)
//     {
//         srand(time(NULL));
//         return quickSort(nums, 0, nums.size() - 1, k);
//     }

//     int getRandom(vector<int> &nums, int left, int right)
//     {
//         int r = rand();
//         return nums[r % (right - left + 1) + left];
//     }

//     int quickSort(vector<int> &nums, int l, int r, int k)
//     {
//         if (l >= r)
//             return nums[l];

//         int key = getRandom(nums, l, r);
//         int i = l, left = l - 1, right = r + 1;

//         while (i < right)
//         {
//             if (nums[i] < key)
//                 swap(nums[i++], nums[left++]);
//             else if (nums[i] == key)
//                 i++;
//             else
//                 swap(nums[i], nums[--right]);
//         }

//         int rightSize = right - r + 1;
//         int midSize = (right - 1) - (left + 1) + 1;

//         if (rightSize >= k)
//             return quickSort(nums, r, right, k);
//         else if (rightSize + midSize >= k)
//             return key;
//         else
//             return quickSort(nums, left, l, k - rightSize - midSize);
//     }

//     vector<int> findAnagrams(string s, string p)
//     {
//         vector<int> ret;
//         int hash1[128] = {0};
//         int hash2[128] = {0};

//         int m = p.size();

//         for (char ch : p)
//             hash2[ch]++;

//         for (int left = 0, right = 0, count = 0; right < s.size(); right++)
//         {
//             char in = s[right];
//             if (++hash1[in] <= hash2[in])
//                 count++;

//             while (right - left + 1 > m)
//             {
//                 char out = s[left++];
//                 if (hash1[out]-- <= hash2[out])
//                     count--;
//             }

//             if (count == m)
//                 ret.push_back(left);
//         }

//         return ret;
//     }

//     int findMin(vector<int> &nums)
//     {
//         int n = nums.size(), left = 0, right = n - 1;

//         while (left < right)
//         {
//             int mid = left + (right - left) / 2;
//             if (nums[mid] > nums[n - 1])
//                 left = mid + 1;
//             else
//                 right = mid;
//         }

//         return nums[left];
//     }

//     int minSubArrayLen(int target, vector<int> &nums)
//     {
//         int ret = INT_MAX;

//         for (int left = 0, right = 0, tmp = 0; right < nums.size(); right++)
//         {
//             tmp += nums[right];
//             while (tmp >= target)
//             {
//                 ret = min(ret, right - left + 1);
//                 tmp -= nums[left++];
//             }
//         }

//         return ret == INT_MAX ? 0 : ret;
//     }

//     vector<int> findSubstring(string s, vector<string> &words)
//     {
//         vector<int> ret;
//         unordered_map<string, int> hash1;

//         int m = words.size(), len = words[0].size();

//         for (auto word : words)
//             hash1[word]++;

//         for (int i = 0; i < len; i++)
//         {
//             unordered_map<string, int> hash2;
//             for (int left = i, right = i, count = 0; right + len <= s.size(); right += len)
//             {
//                 string in = s.substr(right, len);
//                 ++hash2[in];
//                 if (hash1.count(in) && hash2[in] <= hash1[in])
//                     count++;

//                 while (right - left + 1 > len * m)
//                 {
//                     string out = s.substr(left, len);
//                     if (hash1.count(out) && hash2[out] <= hash1[out])
//                         count--;
//                     --hash2[out];
//                     left += len;
//                 }

//                 if (count == m)
//                     ret.push_back(left);
//             }
//         }

//         return ret;
//     }

//     int lengthOfLongestSubstring(string s)
//     {
//         int ret = 0;
//         int hash[128] = {0};

//         for (int left = 0, right = 0; right < s.size(); right++)
//         {
//             char in = s[right];
//             ++hash[in];
//             while (hash[in] > 1)
//             {
//                 char out = s[left++];
//                 --hash[out];
//             }
//             ret = max(ret, right - left + 1);
//         }

//         return ret;
//     }

//     vector<int> searchRange(vector<int> &nums, int target)
//     {
//         if (nums.size() == 0)
//             return {-1, -1};

//         int begin = -1, n = nums.size();

//         int left = 0, right = n - 1;

//         while (left < right)
//         {
//             int mid = left + (right - left) / 2;
//             if (nums[mid] < target)
//                 left = mid + 1;
//             else
//                 right = mid;
//         }

//         if (nums[left] != target)
//             return {-1, -1};
//         begin = left, left = 0, right = n - 1;

//         while (left < right)
//         {
//             int mid = left + (right - left + 1) / 2;
//             if (nums[mid] > target)
//                 right = mid - 1;
//             else
//                 left = mid;
//         }

//         if (begin == -1)
//             return {-1, -1};
//         return {begin, left};
//     }

//     int subarraysDivByK(vector<int> &nums, int k)
//     {
//         unordered_map<int, int> hash;
//         hash[0] = 1;

//         int sum = 0, ret = 0;

//         for (auto n : nums)
//         {
//             sum += n;
//             int r = (sum % k + k) % k;
//             if (hash.count(r))
//                 ret += hash[r];
//             hash[r]++;
//         }

//         return ret;
//     }

//     int totalFruit(vector<int> &fruits)
//     {
//         unordered_map<int, int> hash;
//         int ret = 0;
//         for (int left = 0, right = 0; right < fruits.size(); right++)
//         {
//             int in = fruits[right];
//             hash[in]++;

//             while (hash.size() > 2)
//             {
//                 int out = fruits[left++];
//                 hash[out]--;
//                 if (hash[out] == 0)
//                     hash.erase(out);
//             }

//             ret = max(ret, right - left + 1);
//         }

//         return ret;
//     }

//     vector<int> countSmaller(vector<int> &nums)
//     {
//         int n = nums.size();
//         ret.resize(n);
//         index.resize(n);

//         for (int i = 0; i < n; i++)
//             index[i] = i;

//         mergeSort(nums, 0, n - 1);
//         return ret;
//     }

//     void mergeSort(vector<int> &nums, int left, int right)
//     {
//         if (left >= right)
//             return;

//         int mid = left + (right - left) / 2;

//         mergeSort(nums, left, mid);
//         mergeSort(nums, mid + 1, right);

//         int cur1 = left, cur2 = mid + 1, i = 0;

//         while (cur1 <= mid && cur2 <= right)
//         {
//             if (nums[cur1] >= nums[cur2])
//             {
//                 tmpNums[i] = nums[cur1];
//                 tmpIndex[i++] = index[cur1++];
//             }
//             else
//             {
//                 ret[index[cur1]] += right - cur2 + 1;
//                 tmpNums[i] = nums[cur2];
//                 tmpIndex[i++] = index[cur2++];
//             }
//         }

//         while (cur1 <= mid)
//         {
//             tmpNums[i] = nums[cur1];
//             tmpIndex[i++] = index[cur1++];
//         }

//         while (cur2 <= right)
//         {
//             tmpNums[i] = nums[cur2];
//             tmpIndex[i++] = index[cur2++];
//         }

//         for (int j = left; j <= right; j++)
//         {
//             nums[j] = tmpNums[j - left];
//             index[j] = tmpIndex[j - left];
//         }
//     }

//     int minOperations(vector<int> &nums, int x)
//     {
//         int sum = 0, ret = -1;
//         for (auto n : nums)
//             sum += n;

//         int target = sum - x;
//         if (target < 1)
//             return -1;

//         for (int left = 0, right = 0, tmp = 0; right < nums.size(); right++)
//         {
//             tmp += nums[right];
//             while (tmp > target)
//                 tmp -= nums[left++];
//             if (tmp == target)
//                 ret = max(ret, right - left + 1);
//         }

//         return ret == -1 ? ret : nums.size() - ret;
//     }
// };

// int main()
// {
//     int n = 0, m = 0, q = 0;
//     cin >> n >> m >> q;

//     vector<vector<int>> arr(n + 1, vector<int>(m + 1));
//     vector<vector<long long>> dp(n + 1, vector<long long>(m + 1));

//     for (int i = 1; i <= n; i++)
//         for (int j = 1; j <= m; j++)
//             cin >> arr[i][j];

//     for (int i = 1; i <= n; i++)
//         for (int j = 1; j <= m; j++)
//             dp[i][j] = dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1] + arr[i][j];

//     int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
//     while (q--)
//     {
//         cin >> x1 >> y1 >> x2 >> y2;
//         cout << dp[x2][y2] - dp[x1 - 1][y2] - dp[x2][y1 - 1] + dp[x1 - 1][y1 - 1] << endl;
//     }

//     return 0;
// }

class Solution
{
    vector<int> ret;
    vector<int> index;
    int tmp[500010];
    int tmpIndex[500010];

public:
    vector<int> countSmaller(vector<int> &nums)
    {
        int n = nums.size();
        ret.resize(n);
        index.resize(n);

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

        int cur1 = left, cur2 = mid + 1, i = 0;

        while (cur1 <= mid && cur2 <= right)
        {
            if (nums[cur1] >= nums[cur2])
            {
                tmp[i] = nums[cur1];
                tmpIndex[i++] = nums[cur1++];
            }
            else
            {
                ret[index[cur1]] += right - cur2 + 1;

                tmp[i] = nums[cur2];
                tmpIndex[i++] = nums[cur2++];
            }
        }

        while (cur1 <= mid)
        {
            tmp[i] = nums[cur1];
            tmpIndex[i++] = nums[cur1++];
        }

        while (cur2 <= right)
        {
            tmp[i] = nums[cur2];
            tmpIndex[i++] = nums[cur2++];
        }

        for (int j = left; j <= right; j++)
        {
            nums[j] = tmp[j - left];
            index[j] = tmpIndex[j - left];
        }
    }
};