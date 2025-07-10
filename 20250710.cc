#include <bits/stdc++.h>
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
    vector<int> sortArray(vector<int> &nums)
    {
        srand(time(NULL));
        quickSort(nums, 0, nums.size() - 1);
        return nums;
    }

    int getRandom(vector<int> &nums, int left, int right)
    {
        int r = rand();
        return nums[r % (right - left + 1) + left];
    }

    void quickSort(vector<int> &nums, int l, int r)
    {
        if (l >= r)
            return;

        int key = getRandom(nums, l, r);
        int i = l, left = l - 1, right = r + 1;
        while (i < right)
        {
            if (nums[i] < key)
                swap(nums[i++], nums[++left]);
            else if (nums[i] == key)
                i++;
            else
                swap(nums[i], nums[--right]);
        }

        quickSort(nums, l, left);
        quickSort(nums, right, r);
    }

    void sortColors(vector<int> &nums)
    {
        int n = nums.size(), i = 0, left = -1, right = n;
        while (i < right)
        {
            if (nums[i] < 1)
                swap(nums[i++], nums[++left]);
            else if (nums[i] == 1)
                i++;
            else
                swap(nums[i], nums[--right]);
        }
    }

    vector<string> ret;
    string path;
    string hash[10] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    vector<string> letterCombinations(string digits)
    {
        if (digits.empty())
            return ret;
        dfs(digits, 0);
        return ret;
    }

    void dfs(string &digits, int pos)
    {
        if (pos == digits.size())
        {
            ret.push_back(path);
            return;
        }

        for (auto ch : hash[digits[pos] - '0'])
        {
            path.push_back(ch);
            dfs(digits, pos + 1);
            path.pop_back();
        }
    }

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    vector<vector<int>> pacificAtlantic(vector<vector<int>> &heights)
    {
        m = heights.size(), n = heights[0].size();
        vector<vector<bool>> pac(m, vector<bool>(n));
        vector<vector<bool>> atl(m, vector<bool>(n));
        vector<vector<int>> ret;

        for (int i = 0; i < m; i++)
            dfs(heights, i, 0, pac);
        for (int i = 0; i < n; i++)
            dfs(heights, 0, i, pac);
        for (int i = 0; i < m; i++)
            dfs(heights, i, n - 1, atl);
        for (int i = 0; i < n; i++)
            dfs(heights, m - 1, i, atl);

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (pac[i][j] && atl[i][j])
                    ret.push_back({i, j});

        return ret;
    }

    void dfs(vector<vector<int>> &heights, int i, int j, vector<vector<bool>> &vis)
    {
        vis[i][j] = true;
        for (int k = 0; k < 4; k++)
        {
            int x = i + dx[k], y = j + dy[k];
            if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && heights[x][y] >= heights[i][j])
                dfs(heights, x, y, vis);
        }
    }

    vector<int> twoSum(vector<int> &nums, int target)
    {
        unordered_map<int, int> hash;
        for (int i = 0; i < nums.size(); i++)
        {
            int k = target - nums[i];
            if (hash[k])
                return {i, hash[k]};
            else
                hash[nums[i]] = i;
        }
        return {-1, -1};
    }

    vector<vector<int>> threeSum(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        vector<vector<int>> ret;
        int n = nums.size(), i = 0;

        while (i < n - 2)
        {
            int left = i + 1, right = n - 1;
            while (left < right)
            {
                if (nums[i] + nums[left] + nums[right] > 0)
                    right--;
                else if (nums[i] + nums[left] + nums[right] < 0)
                    left++;
                else
                {
                    ret.push_back({nums[i], nums[left], nums[right]});
                    do
                    {
                        left++;
                    } while (nums[left] == nums[left - 1] && left < right);
                    do
                    {
                        right--;
                    } while (nums[right] == nums[right + 1] && left < right);
                }
            }

            do
            {
                i++;
            } while (nums[i] == nums[i - 1] && i < n - 2);
        }

        return ret;
    }

    bool validateStackSequences(vector<int> &pushed, vector<int> &popped)
    {
        int i = 0, n = popped.size();
        stack<int> st;
        for (int num : pushed)
        {
            st.push(num);
            while (st.size() && st.top() == popped[i])
            {
                i++;
                st.pop();
            }
        }
        return i == n;
    }

    int maxProfit1(vector<int> &prices)
    {
        int ret = 0;
        for (int i = 0, prevMin = INT_MAX; i < prices.size(); i++)
        {
            ret = max(ret, prices[i] - prevMin);
            prevMin = min(prevMin, prices[i]);
        }

        return ret;
    }

    int maxProfit(vector<int> &prices)
    {
        int ret = 0, n = prices.size();
        for (int i = 0; i < n; i++)
        {
            int j = i;
            while (j + 1 < n && prices[j + 1] > prices[j])
                j++; // 寻找峰值

            ret += prices[j] - prices[i];
            i = j;
        }

        return ret;
    }
};