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

class Node
{
public:
    int val;
    vector<Node *> children;

    Node() {}

    Node(int _val)
    {
        val = _val;
    }

    Node(int _val, vector<Node *> _children)
    {
        val = _val;
        children = _children;
    }
};

class Solution
{
public:
    // 1
    void duplicateZeros(vector<int> &arr)
    {
        int n = arr.size(), dest = -1, cur = 0;
        while (cur < n)
        {
            if (arr[cur])
                dest++;
            else
                dest += 2;
            if (dest >= n - 1)
                break;
            cur++;
        }

        if (dest == n)
        {
            arr[n - 1] = 0;
            dest -= 2;
            cur--;
        }

        while (cur >= 0)
        {
            if (arr[cur])
                arr[dest--] = arr[cur--];
            else
            {
                arr[dest--] = 0;
                arr[dest--] = 0;
                cur--;
            }
        }
    }

    // 2
    vector<vector<int>> levelOrder(Node *root)
    {
        vector<vector<int>> ret;
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

                for (auto &child : t->children)
                    if (child)
                        q.push(child);
            }
            ret.push_back(tmp);
        }

        return ret;
    }

    // 4
    int mySqrt(int x)
    {
        if (x < 1)
            return 0;
        int left = 1, right = x;
        while (left < right)
        {
            int mid = left + (right - left + 1) / 2;
            if (mid * mid <= x)
                left = mid;
            else
                right = mid - 1;
        }

        return left;
    }

    // 5
    void reorderList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return;

        ListNode *slow = head, *fast = head;
        while (fast)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode *newhead = slow->next;
        slow->next = nullptr;

        ListNode *prev = new ListNode(0);
        ListNode *cur = newhead;

        while (cur)
        {
            ListNode *next = cur->next;
            cur->next = prev->next;
            prev->next = cur;
            cur = next;
        }

        newhead = prev->next;

        ListNode *ret = new ListNode(0);
        ListNode *cur1 = head, *cur2 = newhead, *prev = ret;
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
    }

    // 6
    bool CheckPermutation(string s1, string s2)
    {
        if (s1.size() != s2.size())
            return false;

        int hash[128] = {0};
        for (char ch : s1)
            hash[ch]++;
        for (char ch : s2)
            if (--hash[ch] < 0)
                return false;
        return true;
    }
};

// 3
class LRUCache
{
public:
    LRUCache(int capacity)
        : _capacity(capacity)
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
            _list.splice(_list.begin(), _list, it);
            it->second = value;
        }
        else
        {
            if (_hash.size() == _capacity)
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
    unordered_map<int, LstItor> _hash;
    list<pair<int, int>> _list;
    int _capacity;
};