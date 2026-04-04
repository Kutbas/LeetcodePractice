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

// 1
class LRUCache
{
public:
    LRUCache(int capacity) : _capacity(capacity)
    {
    }

    int get(int key)
    {
        auto ret = _hash.find(key);
        if (ret != _hash.end())
        {
            auto it = ret->second;
            _list.splice(_list.begin(), _list, it);
            return it->second;
        }
        return -1;
    }

    void put(int key, int value)
    {
        auto ret = _hash.find(key);
        if (ret != _hash.end())
        {
            auto it = ret->second;
            it->second = value;
            _list.splice(_list.begin(), _list, it);
        }
        else
        {
            if (_capacity == _hash.size())
            {
                pair<int, int> back = _list.back();
                _list.pop_back();
                _hash.erase(back.first);
            }
            _list.push_front({key, value});
            _hash[key] = _list.begin();
        }
    }

private:
    int _capacity;
    typedef list<pair<int, int>>::iterator LstItor;
    list<pair<int, int>> _list;
    unordered_map<int, LstItor> _hash;
};

// 2
string s;

string change(string &s)
{
    if (s[0] >= 'A' && s[0] <= 'Z')
        s[0] = tolower(s[0]);
    return s;
}

int main()
{
    getline(cin, s);

    regex re{R"([a-zA-Z]+)"};

    sregex_token_iterator begin(s.begin(), s.end(), re, 0);
    sregex_token_iterator end;

    vector<string> words(begin, end);
    map<string, int> hash;

    for (auto &word : words)
    {
        string tmp = change(word);
        hash[tmp]++;
    }

    for (auto &[a, b] : hash)
        cout << a << ":" << b << endl;

    return 0;
}

// 3
int n, m, q;

int main()
{
    cin >> n >> m >> q;
    vector<vector<int>> nums(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> nums[i][j];

    vector<vector<long long>> dp(n + 1, vector<long long>(m + 1));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1] + nums[i][j];

    int x1, y1, x2, y2;
    while (q--)
    {
        cin >> x1 >> y1 >> x2 >> y2;
        cout << dp[x2][y2] - dp[x1 - 1][y2] - dp[x2][y1 - 1] + dp[x1 - 1][y1 - 1] << endl;
    }

    return 0;
}

class Solution
{
public:
    // 4
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

    // 5
    int calculate(string s)
    {
        vector<int> nums;
        int k = 0, n = s.size();
        char op = '+';

        for (int i = 0; i < n;)
        {
            if (s[i] == ' ')
            {
                i++;
                continue;
            }
            else
            {
                if (isdigit(s[i]))
                {
                    int tmp = 0;
                    while (i < n && isdigit(s[i]))
                        tmp = tmp * 10 + (s[i++] - '0');

                    if (op == '+')
                        nums.push_back(tmp);
                    else if (op == '-')
                        nums.push_back(-tmp);
                    else if (op == '*')
                        nums.back() *= tmp;
                    else
                        nums.back() /= tmp;
                }
                else
                    op = s[i++];
            }
        }

        int ret = 0;
        for (auto num : nums)
            ret += num;

        return ret;
    }

    // 6
    bool isHappy(int n)
    {
        int slow = n, fast = squareSum(n);

        while (slow != fast)
        {
            slow = squareSum(slow);
            fast = squareSum(squareSum(fast));
        }

        return slow == 1;
    }

    int squareSum(int n)
    {
        int ret = 0;
        while (n)
        {
            int bit = n % 10;
            ret += bit * bit;
            n /= 10;
        }
        return ret;
    }

    // 7
    int lengthOfLongestSubstring(string s)
    {
        int n = s.size(), ret = 0;
        int hash[128] = {0};

        for (int left = 0, right = 0; right < n; right++)
        {
            char in = s[right];
            ++hash[in];
            while (hash[in] > 1)
            {
                char out = s[left++];
                --hash[out];
            }

            ret = max(ret, right - left + 1);
        }

        return ret;
    }
};