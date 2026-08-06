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
    vector<vector<int>> fourSum(vector<int> &nums, int target)
    {
        sort(nums.begin(), nums.end());

        int n = nums.size();
        vector<vector<int>> ret;
        int i = 0;
        while (i < n - 1)
        {
            int j = i + 1;
            while (j < n - 2)
            {
                int left = j + 1, right = n - 1;
                long long aim = (long long)target - nums[i] - nums[j];
                while (left < right)
                {
                    if (nums[left] + nums[right] > aim)
                        right--;
                    else if (nums[left] + nums[right] < aim)
                        left++;
                    else
                    {
                        ret.push_back({nums[i], nums[j], nums[left], nums[right]});

                        do
                        {
                            left++;
                        } while (left < right && nums[left - 1] == nums[left]);
                        do
                        {
                            right--;
                        } while (left < right && nums[right + 1] == nums[right]);
                    }
                }

                do
                {
                    j++;
                } while (j < n - 2 && nums[j - 1] == nums[j]);
            }

            do
            {
                i++;
            } while (i < n - 1 && nums[i - 1] == nums[i]);
        }

        return ret;
    }

    // 2
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
        for (auto pair : hash)
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

    // 3
    vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
    {
        vector<vector<int>> edges(numCourses);
        vector<int> in(numCourses);

        // b->a
        for (auto e : prerequisites)
        {
            int a = e[0], b = e[1];
            edges[b].push_back(a);
            in[a]++;
        }

        queue<int> q;
        for (int i = 0; i < numCourses; i++)
            if (in[i] == 0)
                q.push(i);

        vector<int> ret;
        while (q.size())
        {
            auto t = q.front();
            q.pop();
            ret.push_back(t);

            for (auto a : edges[t])
                if (--in[a] == 0)
                    q.push(a);
        }

        for (int i = 0; i < numCourses; i++)
            if (in[i])
                return {};

        return ret;
    }

    // 4
    bool wordBreak(string s, vector<string> &wordDict)
    {
        unordered_set<string> hash(wordDict.begin(), wordDict.end());

        int n = s.size();
        vector<bool> dp(n + 1);
        dp[0] = true;

        s = " " + s;
        for (int i = 1; i <= n; i++)
        {
            for (int j = i; j >= 1; j--)
                if (dp[j - 1] && hash.count(s.substr(j, i - j + 1)))
                {
                    dp[i] = true;
                    break;
                }
        }

        return dp[n];
    }

    // 5
    int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid)
    {
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();

        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        dp[0][1] = 1;

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                if (obstacleGrid[i - 1][j - 1] == 0)
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }

        return dp[m][n];
    }

    // 6
    int maxProfit(vector<int> &prices)
    {
        int n = prices.size();
        vector<int> f(n);
        auto g = f, k = f;

        f[0] = -prices[0];
        for (int i = 1; i < n; i++)
        {
            f[i] = max(f[i - 1], g[i - 1] - prices[i]);
            g[i] = max(g[i - 1], k[i - 1]);
            k[i] = f[i - 1] + prices[i];
        }

        return max(g[n - 1], k[n - 1]);
    }

    // 7
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

        --posti;
        root->right = _buildTree(inorder, postorder, posti, rooti + 1, inEnd);
        root->left = _buildTree(inorder, postorder, posti, inBegin, rooti - 1);

        return root;
    }

    // 9
    class MinStack
    {
    private:
        stack<long> st;
        long minElem;

    public:
        MinStack()
        {
        }

        void push(int value)
        {
            if (st.empty())
            {
                minElem = value;
                st.push(0);
            }
            else
            {
                long diff = value - minElem;
                if (diff < 0)
                    minElem = value;

                st.push(diff);
            }
        }

        void pop()
        {
            long top = st.top();
            st.pop();

            if (top < 0)
                minElem = minElem - top;
        }

        int top()
        {
            long top = st.top();

            if (top > 0)
                return minElem + top;
            return minElem;
        }

        int getMin()
        {
            return minElem;
        }
    };
};

// 8
string s;

string change(string &s)
{
    if (s[0] >= 'A' && s[0] <= 'Z')
        s[0] = tolower(s[0]);
    return s;
}

int main()
{
    getline(cin, s);

    regex re{"([a-zA-Z]+)"};
    sregex_token_iterator begin(s.begin(), s.end(), re, 0);
    sregex_token_iterator end;

    vector<string> words(begin, end);
    map<string, int> hash;

    for (auto &word : words)
    {
        string tmp = change(word);
        hash[tmp]++;
    }

    for (auto &[a, b] : hash)
        cout << a << ":" << b << endl;

    return 0;
}