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
    ListNode *reverseList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *tmp = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;

        return tmp;
    }

    // 2
    bool checkPartitioning(string s)
    {
        int n = s.size();
        vector<vector<bool>> dp(n, vector<bool>(n));

        for (int i = n - 1; i >= 0; i--)
            for (int j = i; j < n; j++)
                if (s[i] == s[j])
                    dp[i][j] = j - i + 1 > 3 ? dp[i + 1][j - 1] : true;

        for (int i = 1; i < n - 1; i++)
            for (int j = i; j < n - 1; j++)
                if (dp[0][i - 1] && dp[i][j] && dp[j + 1][n - 1])
                    return true;

        return false;
    }

    // 3
    int myAtoi(string str)
    {
        int n = str.size(), cur = 0, sign = 1;

        while (str[cur] == ' ')
            if (++cur == n - 1)
                break;

        if (str[cur] == '+' || str[cur] == '-')
        {
            if (str[cur] == '-')
                sign = -1;
            cur++;
        }

        int res = 0;
        for (int i = cur; i < n; i++)
        {
            if (!isdigit(str[i]))
                break;

            // res*10+(str[i]-'0')>INT_MAX
            if (res > (INT_MAX - (str[i] - '0')) / 10)
                return sign == 1 ? INT_MAX : INT_MIN;

            res = res * 10 + (str[i] - '0');
        }

        return res * sign;
    }

    // 4
    int MoreThanHalfNum_Solution(vector<int> &numbers)
    {
        int n = numbers.size(), ret = numbers[0], count = 1;

        for (int i = 1; i < n; i++)
        {
            if (numbers[i] == ret)
                count++;
            else if (--count == 0)
            {
                ret = numbers[i];
                count = 1;
            }
        }

        return ret;
    }

    // 5
    bool IsPopOrder(vector<int> &pushV, vector<int> &popV)
    {
        int n = pushV.size(), i = 0;
        stack<int> st;

        for (auto num : pushV)
        {
            st.push(num);

            while (st.size() && st.top() == popV[i])
            {
                st.pop();
                i++;
            }
        }

        return i == n;
    }

    // 6
    // Matrix-Vector Dot Product
};