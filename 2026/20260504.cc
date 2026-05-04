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
    int totalFruit(vector<int> &fruits)
    {
        int n = fruits.size();
        unordered_map<int, int> hash;

        int ret = 0;
        for (int left = 0, right = 0; right < n; right++)
        {
            hash[fruits[right]]++;
            while (hash.size() > 2)
            {
                if (--hash[fruits[left]] == 0)
                    hash.erase(fruits[left]);
                left++;
            }
            ret = max(ret, right - left + 1);
        }

        return ret;
    }

    // 2
    vector<int> largestValues(TreeNode *root)
    {
        vector<int> ret;
        if (root == nullptr)
            return ret;

        queue<TreeNode *> q;
        q.push(root);
        while (q.size())
        {
            int tmp = INT_MIN;
            int sz = q.size();
            while (sz--)
            {
                auto t = q.front();
                q.pop();

                tmp = max(tmp, t->val);

                if (t->left)
                    q.push(t->left);
                if (t->right)
                    q.push(t->right);
            }

            ret.push_back(tmp);
        }

        return ret;
    }

    // 3
    typedef pair<string, int> PSI;

    struct cmp
    {
        bool operator()(const PSI &p1, const PSI &p2)
        {
            return p1.second != p2.second ? p1.second < p2.second : p1.first > p2.first;
        }
    };

    vector<string> topKFrequent(vector<string> &words, int k)
    {
        unordered_map<string, int> hash;
        for (auto &word : words)
            hash[word]++;

        priority_queue<PSI, vector<PSI>, cmp> q;
        for (auto &pair : hash)
            q.push(pair);

        vector<string> ret;
        while (k--)
        {
            auto [a, b] = q.top();
            q.pop();

            ret.push_back(a);
        }

        return ret;
    }

    // 4
    ListNode *reverseList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *newhead = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;

        return newhead;
    }

    // 5
    int jump(vector<int> &nums)
    {
        int n = nums.size(), cur = 0, far = 0, ret = 0;

        for (int i = 0; i < n - 1; i++)
        {
            far = max(far, i + nums[i]);

            if (cur >= n - 1)
                break;

            if (i == cur)
            {
                cur = far;
                ret++;
            }
        }

        return ret;
    }

    // 6
    int maxSubArray(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> dp(n + 1);

        int ret = INT_MIN;
        for (int i = 1; i <= n; i++)
        {
            dp[i] = max(dp[i - 1] + nums[i - 1], nums[i - 1]);
            ret = max(ret, dp[i]);
        }

        return ret;
    }

    // 7
    int longestSubsequence(vector<int> &arr, int difference)
    {
        unordered_map<int, int> hash;
        hash[arr[0]] = 1;
        int ret = 1, n = arr.size();

        for (int i = 1; i < n; i++)
        {
            hash[arr[i]] = hash[arr[i] - difference] + 1;
            ret = max(ret, hash[arr[i]]);
        }

        return ret;
    }

    // 8
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder)
    {
        int i = postorder.size() - 1;
        return _buildTree(inorder, postorder, i, 0, inorder.size() - 1);
    }

    TreeNode *_buildTree(vector<int> &inorder, vector<int> &postorder, int &posti, int inBegin, int inEnd)
    {
        if (inBegin > inEnd)
            return nullptr;

        TreeNode *root = new TreeNode(postorder[posti]);

        int rooti = inBegin;
        while (rooti <= inEnd)
            if (inorder[rooti] == postorder[posti])
                break;
            else
                rooti++;

        posti--;
        root->right = _buildTree(inorder, postorder, posti, rooti + 1, inEnd);
        root->left = _buildTree(inorder, postorder, posti, inBegin, rooti - 1);

        return root;
    }

    // 9
    int maxUncrossedLines(vector<int> &nums1, vector<int> &nums2)
    {
        int m = nums1.size(), n = nums2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                if (nums1[i - 1] == nums2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }

        return dp[m][n];
    }

};