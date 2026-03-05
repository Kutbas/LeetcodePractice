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
    void reorderList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
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
        while (cur1 || cur2)
        {
            if (cur1)
            {
                prev->next = cur1;
                cur1 = cur1->next;
                prev = prev->next;
            }
            if (cur2)
            {
                prev->next = cur2;
                cur2 = cur2->next;
                prev = prev->next;
            }
        }

        prev = ret->next;
        delete cur1, cur2, cur, head2, ret;
    }

    // 3
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        int i = 0;
        return _buildTree(preorder, inorder, i, 0, inorder.size() - 1);
    }

    TreeNode *_buildTree(vector<int> &preorder, vector<int> &inorder,
                         int &previ, int inBegin, int inEnd)
    {
        if (inBegin > inEnd)
            return nullptr;

        TreeNode *root = new TreeNode(preorder[previ]);

        int rooti = inBegin;
        while (rooti <= inEnd)
        {
            if (inorder[rooti] == preorder[previ])
                break;
            else
                rooti++;
        }

        previ++;
        root->left = _buildTree(preorder, inorder, previ, inBegin, rooti - 1);
        root->right = _buildTree(preorder, inorder, previ, rooti + 1, inEnd);

        return root;
    }

    // 4
    string longestCommonPrefix(vector<string> &strs)
    {
        for (int i = 0; i < strs[0].size(); i++)
            for (int j = 1; j < strs.size(); j++)
                if (i == strs[j].size() || strs[0][i] != strs[j][i])
                    return strs[0].substr(0, i);
        return strs[0];
    }

    // 5
    int lengthOfLIS(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> ret;
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

    // 6
    int removeDuplicates(vector<int> &nums)
    {
        int n = nums.size(), slow = 1, fast = 1;
        while (fast < n)
        {
            if (nums[fast - 1] != nums[fast])
                nums[slow++] = nums[fast];
            fast++;
        }
        return slow;
    }

    // 7
    string tree2str(TreeNode *root)
    {
        if (root == nullptr)
            return "";

        string ret = to_string(root->val);
        if (root->left || root->right)
        {
            ret += "(";
            ret += tree2str(root->left);
            ret += ")";
        }

        if (root->right)
        {
            ret += "(";
            ret += tree2str(root->right);
            ret += ")";
        }

        return ret;
    }
};

// 2
int main()
{
    string s;
    cin >> s;

    int hash[128] = {0};
    for (char ch : s)
        hash[ch]++;

    for (char ch : s)
        if (hash[ch] == 1)
        {
            cout << ch << endl;
            return 0;
        }

    cout << -1 << endl;
    return 0;
}
