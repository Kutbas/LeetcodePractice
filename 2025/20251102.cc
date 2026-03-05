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
    int findMaxLength(vector<int> &nums)
    {
        unordered_map<int, int> hash;
        hash[0] = -1;

        int ret = 0, sum = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            sum += nums[i] == 0 ? -1 : 1;
            if (hash.count(sum))
                ret = max(ret, i - hash[sum]);
            hash[sum] = i;
        }

        return ret;
    }

    // 2
    vector<vector<int>> ret;
    vector<int> path;
    bool vis[7];
    vector<vector<int>> permute(vector<int> &nums)
    {
        dfs(nums, 0);
        return ret;
    }

    void dfs(vector<int> &nums, int pos)
    {
        if (path.size() == nums.size())
        {
            ret.push_back(path);
            return;
        }

        for (int i = 0; i < nums.size(); i++)
        {
            if (!vis[i])
            {
                vis[i] = true;
                path.push_back(nums[i]);
                dfs(nums, i);
                path.pop_back();
                vis[i] = false;
            }
        }
    }

    // 3
    bool validateStackSequences(vector<int> &pushed, vector<int> &popped)
    {
        stack<int> st;
        int i = 0, n = pushed.size();

        for (auto n : pushed)
        {
            st.push(n);
            while (st.size() && st.top() == popped[i])
            {
                st.pop();
                i++;
            }
        }

        return i == n;
    }

    // 4
    int K, res;
    int kthSmallest(TreeNode *root, int k)
    {
        K = k;
        dfs(root);
        return res;
    }

    void dfs(TreeNode *root)
    {
        if (root->left)
            dfs(root->left);

        if (--K == 0)
        {
            res = root->val;
            return;
        }

        if (root->right)
            dfs(root->right);
    }

    // 5
    string decodeString(string s)
    {
        string tmp;
        int k = 0;
        stack<int> nums;
        stack<string> st;

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
                string top = st.top();
                st.pop();
                int count = nums.top();
                nums.pop();
                while (count--)
                    top += tmp;
                st.push(top);
            }
            else
                tmp += ch;
        }

        return st.top();
    }

    // 6
    vector<int> twoSum(vector<int> &nums, int target)
    {
        unordered_map<int, int> hash;
        for (int i = 0; i < nums.size(); i++)
        {
            int x = target - nums[i];
            if (hash.count(x))
                return {i, hash[x]};
            hash[nums[i]] = i;
        }

        return {-1, -1};
    }
};