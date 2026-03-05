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
    vector<string> ret;
    vector<string> binaryTreePaths(TreeNode *root)
    {
        dfs(root, "");
        return ret;
    }

    void dfs(TreeNode *root, string path)
    {
        path += to_string(root->val);

        if (root->left == nullptr && root->right == nullptr)
        {
            ret.push_back(path);
            return;
        }

        path += "->";
        if (root->left)
            dfs(root->left, path);
        if (root->right)
            dfs(root->right, path);
    }

    // 2
    int removeDuplicates(vector<int> &nums)
    {
        int n = nums.size();
        int slow = 1, fast = 1;

        while (fast < n)
        {
            if (nums[fast] != nums[fast - 1])
                nums[slow++] = nums[fast];

            fast++;
        }

        return slow;
    }

    // 4
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
        ListNode *prev = ret, *cur1 = head, *cur2 = head2->next;
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
        delete cur, head2, cur1, cur2, ret;
        return;
    }

    // 5
    typedef pair<TreeNode *, unsigned int> PTI;
    int widthOfBinaryTree(TreeNode *root)
    {
        vector<PTI> q;
        q.push_back({root, 1});
        unsigned int ret = 0;

        while (q.size())
        {
            int sz = q.size();
            vector<PTI> tmp;

            auto [x1, y1] = q[0];
            auto [x2, y2] = q.back();

            ret = max(ret, y2 - y1 + 1);

            for (auto &[x, y] : q)
            {
                if (x->left)
                    tmp.push_back({x->left, 2 * y});
                if (x->right)
                    tmp.push_back({x->right, 2 * y + 1});
            }

            q = tmp;
        }

        return ret;
    }

    // 6
    int minSubArrayLen(int target, vector<int> &nums)
    {
        int n = nums.size();
        int ret = INT_MAX;

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

    // 7
    class DiningPhilosophers
    {
    public:
        DiningPhilosophers()
        {
        }

        void wantsToEat(int philosopher,
                        function<void()> pickLeftFork,
                        function<void()> pickRightFork,
                        function<void()> eat,
                        function<void()> putLeftFork,
                        function<void()> putRightFork)
        {
            int l = philosopher, r = (philosopher + 1) % 5;
            if (l % 2 == 0)
            {
                lock[l].lock();
                lock[r].lock();
            }
            else
            {
                lock[r].lock();
                lock[l].lock();
            }
            pickLeftFork();
            pickRightFork();
            eat();
            putLeftFork();
            putRightFork();
            lock[l].unlock();
            lock[r].unlock();
        }

    private:
        std::mutex lock[5];
    };
};
