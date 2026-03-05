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
    int minCut(string s)
    {
        int n = s.size();
        vector<vector<bool>> isPal(n, vector<bool>(n));

        for (int i = n - 1; i >= 0; i--)
            for (int j = i; j < n; j++)
                if (s[i] == s[j])
                    isPal[i][j] = j - i + 1 > 3 ? isPal[i + 1][j - 1] : true;

        vector<int> dp(n, INT_MAX);
        for (int i = 0; i < n; i++)
        {
            if (isPal[0][i])
                dp[i] = 0;
            else
            {
                for (int j = 1; j <= i; j++)
                {
                    if (isPal[j][i])
                        dp[i] = min(dp[j - 1] + 1, dp[i]);
                }
            }
        }
        return dp[n - 1];
    }

    // 2
    string decodeString(string s)
    {
        stack<int> nums;
        int k = 0;
        stack<string> st;
        st.push("");
        string tmp;

        for (char ch : s)
        {
            if (isdigit(ch))
                k = k * 10 + (ch - '0');
            else if (ch == '[')
            {
                st.push(tmp);
                tmp = "";
                nums.push(k);
                k = 0;
            }
            else if (ch == ']')
            {
                int count = nums.top();
                nums.pop();
                string top = st.top();
                st.pop();
                while (count--)
                    top += tmp;
                tmp = top;
                // st.push(tmp);
            }
            else
                tmp += ch;
        }
        return tmp;
    }

    // 3
    int findLength(vector<int> &nums1, vector<int> &nums2)
    {
        int m = nums1.size(), n = nums2.size();

        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        int ret = 0;

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                if (nums1[i - 1] == nums2[j - 1])
                {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    ret = max(ret, dp[i][j]);
                }

        return ret;
    }

    // 4
    int eraseOverlapIntervals(vector<vector<int>> &in)
    {
        sort(in.begin(), in.end());
        int n = in.size(), ret = 0, right = in[0][1];

        for (int i = 1; i < n; i++)
        {
            int a = in[i][0], b = in[i][1];
            if (a < right)
            {
                ret++;
                right = min(right, b);
            }
            else
                right = b;
        }

        return ret;
    }

    // 5
    vector<int> findSubstring(string s, vector<string> &words)
    {
        int n = s.size(), m = words.size(), len = words[0].size();
        unordered_map<string, int> hash1;
        for (auto &word : words)
            hash1[word]++;

        vector<int> ret;
        for (int i = 0; i < len; i++)
        {
            unordered_map<string, int> hash2;
            for (int left = i, right = i, count = 0; right + len <= n;
                 right += len)
            {
                string in = s.substr(right, len);
                if (hash1.count(in) && ++hash2[in] <= hash1[in])
                    count++;
                while (right - left + 1 > len * m)
                {
                    string out = s.substr(left, len);
                    if (hash1.count(out) && hash2[out]-- <= hash1[out])
                        count--;
                    left += len;
                }
                if (count == m)
                    ret.push_back(left);
            }
        }

        return ret;
    }
};

// 6
int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> nums(n + 1);
    vector<long long> dp(n + 1);

    for (int i = 1; i <= n; i++)
        cin >> nums[i];
    for (int i = 1; i <= n; i++)
        dp[i] = dp[i - 1] + nums[i];

    int l, r;
    while (m--)
    {
        cin >> l >> r;
        cout << dp[r] - dp[l - 1] << endl;
    }

    return 0;
}