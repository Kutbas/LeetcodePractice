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
    vector<int> smallestK(vector<int> &arr, int k)
    {
        srand(time(nullptr));
        quickSort(arr, 0, arr.size() - 1, k);
        return {arr.begin(), arr.begin() + k};
    }

    int getRandom(vector<int> &nums, int left, int right)
    {
        int r = rand();
        return nums[r % (right - left + 1) + left];
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
            return quickSort(nums, l, left, k);
        else if (lRange + mRange >= k)
            return;
        else
            return quickSort(nums, right, r, k - lRange - mRange);
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
            for (int left = i, right = i, count = 0; right + len <= s.size(); right += len)
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
                    hash2[out]--;
                    left += len;
                }
                if (count == m)
                    ret.push_back(left);
            }
        }

        return ret;
    }

    string addBinary(string a, string b)
    {
        string ret;
        int m = a.size(), n = b.size();
        int cur1 = m - 1, cur2 = n - 1, t = 0;
        while (t || cur1 || cur2)
        {
            if (cur1)
                t += a[cur1--] - '0';
            if (cur2)
                t += b[cur2--] - '0';
            ret += (t % 2 + '0');
            t /= 2;
        }

        reverse(ret.begin(), ret.end());
        return ret;
    }

    string multiply(string num1, string num2)
    {
        int m = num1.size(), n = num2.size();
        vector<int> nums(m + n - 1);
        string ret;

        for (int i = num1.size() - 1; i >= 0; i--)
            for (int j = num2.size() - 1; j >= 0; j--)
                nums[i + j] += (num1[i] - '0') * (num2[j] - '0');

        int t = 0, cur = m + n - 2;
        while (t || cur >= 0)
        {
            if (cur >= 0)
                t += nums[cur--];
            ret += (t % 10 + '0');
            t /= 10;
        }

        while (ret.size() > 1 && ret[0] == '0')
            ret.erase(0, 1);

        reverse(ret.begin(), ret.end());

        return ret;
    }

    int ladderLength(string beginWord, string endWord, vector<string> &wordList)
    {
        if (beginWord == endWord)
            return 1;
        unordered_set<string> hash(wordList.begin(), wordList.end());
        unordered_set<string> vis;

        if (!hash.count(endWord))
            return 0;

        int ret = 1;
        queue<string> q;
        q.push(beginWord);
        while (q.size())
        {
            ret++;
            int sz = q.size();
            while (sz--)
            {
                auto t = q.front();
                q.pop();
                for (int i = 0; i < t.size(); i++)
                {
                    string tmp = t;
                    for (char ch = 'a'; ch <= 'z'; ch++)
                    {
                        tmp[i] = ch;
                        if (hash.count(tmp) && !vis.count(tmp))
                        {
                            if (tmp == endWord)
                                return ret;
                            q.push(tmp);
                            vis.insert(tmp);
                        }
                    }
                }
            }
        }

        return 0;
    }
};