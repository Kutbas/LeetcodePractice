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
    int m, n;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    vector<vector<int>> highestPeak(vector<vector<int>> &isWater)
    {
        m = isWater.size(), n = isWater[0].size();
        vector<vector<int>> dist(m, vector<int>(n, -1));

        queue<pair<int, int>> q;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (isWater[i][j])
                {
                    dist[i][j] = 0;
                    q.push({i, j});
                }

        while (q.size())
        {
            int sz = q.size();
            while (sz--)
            {
                auto [a, b] = q.front();
                q.pop();
                for (int k = 0; k < 4; k++)
                {
                    int x = a + dx[k], y = b + dy[k];
                    if (x >= 0 && x < m && y >= 0 && y < n && dist[x][y] == -1)
                    {
                        dist[x][y] = dist[a][b] + 1;
                        q.push({x, y});
                    }
                }
            }
        }

        return dist;
    }

    // 2
    int maxSubArray(vector<int> &nums)
    {
        int n = nums.size(), ret = INT_MIN;
        vector<int> dp(n + 1);

        for (int i = 1; i <= n; i++)
        {
            dp[i] = max(dp[i - 1] + nums[i - 1], nums[i - 1]);
            ret = max(ret, dp[i]);
        }

        return ret;
    }

    // 4
    // 动态数组：用来存储【中序遍历后有序的二叉树节点】
    // TreeNode* 表示存储的是二叉树节点的指针
    vector<TreeNode *> TreeList;

    // 函数功能：递归实现【中序遍历】，把节点按顺序存入数组
    // 参数 root：当前遍历到的二叉树节点
    void inorder(TreeNode *root)
    {
        // 递归终止条件：如果当前节点是空的，直接返回，不做任何操作
        if (!root)
            return;

        // 第一步：递归遍历【左子树】
        inorder(root->left);

        // 第二步：把当前节点【添加到数组末尾】（核心：按中序顺序存节点）
        TreeList.push_back(root);

        // 第三步：递归遍历【右子树】
        inorder(root->right);
    }

    // 函数功能：主函数，调用遍历+串联节点，返回双向链表头节点
    // 参数 pRootOfTree：二叉搜索树的根节点
    TreeNode *Convert(TreeNode *pRootOfTree)
    {
        // 特殊情况：如果二叉树是空的，直接返回空
        if (!pRootOfTree)
            return pRootOfTree;

        // 1. 调用中序遍历，把所有有序节点存入 TreeList 数组
        inorder(pRootOfTree);

        // 2. 遍历数组，把节点两两串联成双向链表
        // 循环范围：i 最大到 倒数第二个节点（因为要连 i 和 i+1）
        for (int i = 0; i < TreeList.size() - 1; i++)
        {
            // 前一个节点的【右指针】 → 指向后一个节点
            TreeList[i]->right = TreeList[i + 1];
            // 后一个节点的【左指针】 → 指向前一个节点
            TreeList[i + 1]->left = TreeList[i];
        }

        // 数组第一个元素，就是双向链表的【头节点】，直接返回
        return TreeList[0];
    }
};

// 3
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
                _hash.erase(back.first);
                _list.pop_back();
            }
            _list.push_front({key, value});
            _hash[key] = _list.begin();
        }
    }

private:
    typedef list<pair<int, int>>::iterator LstItor;
    int _capacity;
    list<pair<int, int>> _list;
    unordered_map<int, LstItor> _hash;
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */