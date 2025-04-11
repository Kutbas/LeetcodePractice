#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    string longestPalindrome(string s)
    {
        int begin = 0, len = 0, n = s.size();
        for (int i = 0; i < n; i++)
        {
            // 先做一次奇数长度的扩展
            int left = i, right = i;
            while (left >= 0 && right < n && s[left] == s[right])
            {
                left++;
                right--;
            }
            if (right - left - 1 > len)
            {
                begin = left + 1;
                len = right - left - 1;
            }
            // 再做一次偶数长度的扩展
            left = i, right = i + 1;
            while (left >= 0 && right < n && s[left] == s[right])
            {
                left++;
                right--;
            }
            if (right - left - 1 > len)
            {
                begin = left + 1;
                len = right - left - 1;
            }
        }
        return s.substr(begin, len);
    }

    string addBinary(string a, string b)
    {
        string ret;

        int cur1 = a.size() - 1, cur2 = b.size() - 1, t = 0;
        while (cur1 >= 0 || cur2 >= 0 || t)
        {
            if (cur1 >= 0)
                t += a[cur1--] - '0';
            if (cur2 >= 0)
                t += b[cur2--] - '0';
            ret += t % 2 + '0';
            t /= 2;
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }

    string multiply(string num1, string num2)
    {
        int m = num1.size(), n = num2.size();
        reverse(num1.begin(), num1.end());
        reverse(num2.begin(), num2.end());
        vector<int> tmp(m + n - 1);

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                tmp[i + j] += (num1[i] - '0') * (num2[j] - '0');
            }

        int cur = 0, t = 0;
        string ret;
        while (cur < m + n - 1 || t != 0)
        {
            if (cur < m + n - 1)
                t += tmp[cur++];
            ret += t % 10 + '0';
            t /= 10;
        }

        while (ret.size() > 1 && ret.back() == '0')
            ret.pop_back();

        reverse(ret.begin(), ret.end());
        return ret;
    }
};