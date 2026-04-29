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
    int minSubArrayLen(int target, vector<int> &nums)
    {
        int n = nums.size(), ret = INT_MAX;

        for (int left = 0, right = 0, tmp = 0; right < n; right++)
        {
            tmp += nums[right];
            while (tmp >= target)
            {
                ret = min(ret, right - left + 1);
                tmp -= nums[left++];
            }
        }

        return ret == INT_MAX ? 0 : ret;
    }

    // 2
    vector<int> missingTwo(vector<int> &nums)
    {
        int xorsum = 0;
        for (auto n : nums)
            xorsum ^= n;
        for (int i = 1; i <= nums.size() + 2; i++)
            xorsum ^= i;

        int lsb = xorsum & (-xorsum) == INT_MIN ? INT_MIN : xorsum & (-xorsum);
        int x = 0, y = 0;

        for (auto n : nums)
        {
            if (n & lsb)
                x ^= n;
            else
                y ^= n;
        }

        for (int i = 1; i <= nums.size() + 2; i++)
        {
            if (i & lsb)
                x ^= i;
            else
                y ^= i;
        }

        return {x, y};
    }

    // 3
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
                int i = index[ch];
                if (hash[i - 1] == 0)
                    return -1;
                hash[i - 1]--, hash[i]++;
            }
        }

        for (int i = 0; i < n - 1; i++)
            if (hash[i])
                return -1;

        return hash[n - 1];
    }

    // 4
    string decodeString(string s)
    {
        stack<string> st;
        string ret;
        stack<int> nums;
        int num = 0;

        for (char ch : s)
        {
            if (isdigit(ch))
                num = num * 10 + (ch - '0');
            else if (ch == '[')
            {
                st.push(ret);
                ret = "";
                nums.push(num);
                num = 0;
            }
            else if (ch == ']')
            {
                int k = nums.top();
                nums.pop();
                string tmp = st.top();
                st.pop();
                while (k--)
                    tmp += ret;
                ret = tmp;
            }
            else
                ret += ch;
        }

        return ret;
    }

    // 5
    vector<vector<int>> ret;
    vector<vector<int>> levelOrder(Node *root)
    {
        if (root == nullptr)
            return ret;

        queue<Node *> q;
        q.push(root);
        while (q.size())
        {
            int sz = q.size();
            vector<int> tmp;
            while (sz--)
            {
                auto t = q.front();
                q.pop();
                tmp.push_back(t->val);

                for (auto &a : t->children)
                    if (a)
                        q.push(a);
            }

            ret.push_back(tmp);
        }

        return ret;
    }

    // 6
    vector<string> ret;
    vector<string> binaryTreePaths(TreeNode *root)
    {
        dfs(root, "");
        return ret;
    }

    void dfs(TreeNode *root, string path)
    {
        if (root == nullptr)
            return;

        path += to_string(root->val);
        if (root->left == nullptr && root->right == nullptr)
            ret.push_back(path);

        path += "->";
        dfs(root->left, path);
        dfs(root->right, path);
    }

    // 7
    int myAtoi(string str)
    {
        int n = str.size(), cur = 0, sign = 1, ret = 0;

        while (str[cur] == ' ')
            if (++cur == n)
                return 0;

        if (str[cur] == '+' || str[cur] == '-')
        {
            if (str[cur] == '-')
                sign = -1;
            cur++;
        }

        for (int i = cur; i < n; i++)
        {
            if (!isdigit(str[i]))
                break;

            if (ret > (INT_MAX - (str[i] - '0')) / 10)
                return sign == 1 ? INT_MAX : INT_MIN;

            ret = ret * 10 + (str[i] - '0');
        }

        return ret * sign;
    }

    // 8
    vector<int> ret;
    vector<int> preorderTraversal(TreeNode *root)
    {
        if (root == nullptr)
            return ret;
        dfs(root);
        return ret;
    }

    void dfs(TreeNode *root)
    {
        if (root == nullptr)
            return;

        ret.push_back(root->val);
        dfs(root->left);
        dfs(root->right);
    }

    // 9
    int longestSubsequence(vector<int> &arr, int difference)
    {
        unordered_map<int, int> hash;
        hash[arr[0]] = 1;
        int ret = 1;

        for (int i = 1; i < arr.size(); i++)
        {
            hash[arr[i]] = hash[arr[i] - difference] + 1;
            ret = max(ret, hash[arr[i]]);
        }

        return ret;
    }
};