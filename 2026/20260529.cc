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
    string decodeString(string s)
    {
        stack<string> str;
        string ret;
        stack<int> nums;
        int num = 0;

        for (char ch : s)
        {
            if (isdigit(ch))
                num = num * 10 + (ch - '0');
            else if (ch == '[')
            {
                str.push(ret);
                ret = "";
                nums.push(num);
                num = 0;
            }
            else if (ch == ']')
            {
                string tmp = str.top();
                str.pop();
                int k = nums.top();
                nums.pop();
                while (k--)
                    tmp += ret;
                ret = tmp;
            }
            else
                ret += ch;
        }

        return ret;
    }

    // 2
    int lengthOfLIS(vector<int> &nums)
    {
        vector<int> ret;
        int n = nums.size();

        ret.push_back(nums[0]);
        for (int i = 1; i < n; i++)
        {
            if (nums[i] > ret.back())
                ret.push_back(nums[i]);
            else
            {
                int left = 0, right = ret.size() - 1;
                while (left < right)
                {
                    int mid = left + (right - left) / 2;
                    if (nums[i] > ret[mid])
                        left = mid + 1;
                    else
                        right = mid;
                }
                ret[left] = nums[i];
            }
        }

        return ret.size();
    }

    // 3
    string largestNumber(vector<int> &nums)
    {
        vector<string> strs;
        for (auto n : nums)
            strs.push_back(to_string(n));

        sort(strs.begin(), strs.end(), [](const string &s1, const string &s2)
             { return s1 + s2 > s2 + s1; });

        string ret;
        for (auto &s : strs)
            ret += s;

        return ret[0] == '0' ? "0" : ret;
    }

    // 4
    bool increasingTriplet(vector<int> &nums)
    {
        int a = INT_MAX, b = INT_MAX;
        for (auto n : nums)
        {
            if (n > a)
                return true;
            else if (n > b)
                a = n;
            else
                b = n;
        }

        return false;
    }

    // 5
    vector<string> sortPeople(vector<string> &names, vector<int> &heights)
    {
        int n = names.size();
        vector<int> index(n);
        for (int i = 0; i < n; i++)
            index[i] = i;

        sort(index.begin(), index.end(), [&](const int i, const int j)
             { return heights[i] > heights[j]; });

        vector<string> ret;
        for (auto i : index)
            ret.push_back(names[i]);

        return ret;
    }

    // 6
    vector<int> rearrangeBarcodes(vector<int> &barcodes)
    {
        unordered_map<int, int> hash;
        int maxVal = 0, maxCount = 0;

        for (auto n : barcodes)
            if (maxCount < ++hash[n])
            {
                maxCount = hash[n];
                maxVal = n;
            }

        int index = 0, n = barcodes.size();
        vector<int> ret(n);
        for (int i = 0; i < maxCount; i++)
        {
            ret[index] = maxVal;
            index += 2;
        }

        hash.erase(maxVal);
        for (auto &[x, y] : hash)
            for (int i = 0; i < y; i++)
            {
                if (index >= n)
                    index = 1;

                ret[index] = x;
                index += 2;
            }

        return ret;
    }

    // 7
    int massage(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 0)
            return 0;
        vector<int> f(n);
        auto g = f;

        f[0] = nums[0];
        for (int i = 1; i < n; i++)
        {
            f[i] = max(f[i - 1], g[i - 1] + nums[i]);
            g[i] = max(f[i - 1], g[i - 1]);
        }

        return max(f[n - 1], g[n - 1]);
    }

    // 8
    bool IsPopOrder(vector<int> &pushV, vector<int> &popV)
    {
        int n = pushV.size(), i = 0;
        stack<int> nums;

        for (auto n : pushV)
        {
            nums.push(n);
            while (nums.size() && nums.top() == popV[i])
            {
                nums.pop();
                i++;
            }
        }

        return i == n;
    }
};