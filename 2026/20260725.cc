#include <mutex>
#include <vector>
#include <algorithm>
#include <climits>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <iostream>
#include <regex>
#include <map>
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

        ListNode *slow = head, *fast = head->next;
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode *cur = slow->next;
        slow->next = nullptr;
        ListNode *head2 = new ListNode(0);

        while (cur)
        {
            ListNode *next = cur->next;
            cur->next = head2->next;
            head2->next = cur;
            cur = next;
        }

        delete cur;

        ListNode *ret = new ListNode(0);
        ListNode *prev = ret;
        ListNode *cur1 = head;
        ListNode *cur2 = head2->next;
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
        delete ret, cur1, cur2;
        return;
    }

    // 2
    string decodeString(string s)
    {
        stack<int> nums;
        int num = 0;
        stack<string> strs;
        string ret;

        for (char ch : s)
        {
            if (isdigit(ch))
                num = num * 10 + (ch - '0');
            else if (ch == '[')
            {
                nums.push(num);
                num = 0;
                strs.push(ret);
                ret = "";
            }
            else if (ch == ']')
            {
                int k = nums.top();
                nums.pop();
                string tmp = strs.top();
                strs.pop();
                while (k--)
                    tmp += ret;
                ret = tmp;
            }
            else
                ret += ch;
        }

        return ret;
    }

    // 4
    int maxProfit(vector<int> &prices, int fee)
    {
        int n = prices.size();
        vector<int> f(n);
        auto g = f;
        f[0] = -prices[0];

        for (int i = 1; i < n; i++)
        {
            g[i] = max(g[i - 1], f[i - 1] + prices[i] - fee);
            f[i] = max(f[i - 1], g[i - 1] - prices[i]);
        }

        return g[n - 1];
    }

    // 5
};

// 3
class LRUCache
{
private:
    typedef list<pair<int, int>>::iterator LstItor;
    int _capacity;
    unordered_map<int, LstItor> _hash;
    list<pair<int, int>> _list;

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
};