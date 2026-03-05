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
    // 1
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;
    typedef pair<int, int> PIR;
    int cutOffTree(vector<vector<int>> &forest)
    {
        m = forest.size(), n = forest[0].size();
        vector<PIR> trees;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (forest[i][j] > 1)
                    trees.push_back({i, j});

        sort(trees.begin(), trees.end(), [&](const PIR p1, const PIR p2)
             { return forest[p1.first][p1.second] < forest[p2.first][p2.second]; });

        int ret = 0, bx = 0, by = 0;
        for (auto &[a, b] : trees)
        {
            int step = dfs(forest, bx, by, a, b);
            if (step == -1)
                return -1;
            ret += step;
            bx = a;
            by = b;
        }

        return ret;
    }

    bool vis[51][51];
    int dfs(vector<vector<int>> &forest, int bx, int by, int ex, int ey)
    {
        if (bx == ex && by == ey)
            return 0;

        memset(vis, 0, sizeof vis);
        queue<PIR> q;
        q.push({bx, by});
        vis[bx][by] = true;

        int ret = 0;
        while (q.size())
        {
            ret++;
            int sz = q.size();
            while (sz--)
            {
                auto [a, b] = q.front();
                q.pop();
                for (int k = 0; k < 4; k++)
                {
                    int x = a + dx[k], y = b + dy[k];
                    if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && forest[x][y])
                    {
                        if (x == ex && y == ey)
                            return ret;
                        q.push({x, y});
                        vis[x][y] = true;
                    }
                }
            }
        }

        return -1;
    }

    // 2
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int K;
    bool vis[101][101];
    int wardrobeFinishing(int m, int n, int cnt)
    {
        K = cnt;
        int ret = 1;
        queue<pair<int, int>> q;
        q.push({0, 0});
        vis[0][0] = true;

        while (q.size())
        {
            auto [a, b] = q.front();
            q.pop();
            for (int k = 0; k < 4; k++)
            {
                int x = a + dx[k], y = b + dy[k];
                if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && check(x, y))
                {
                    ret++;
                    q.push({x, y});
                    vis[x][y] = true;
                }
            }
        }

        return ret;
    }

    bool check(int i, int j)
    {
        int tmp = 0;
        while (i)
        {
            tmp += i % 10;
            i /= 10;
        }
        while (j)
        {
            tmp += j % 10;
            j /= 10;
        }

        return tmp <= K;
    }

    // 3
    int tmp[50010];
    vector<int> sortArray(vector<int> &nums)
    {
        mergeSort(nums, 0, nums.size() - 1);
        return nums;
    }

    void mergeSort(vector<int> &nums, int left, int right)
    {
        if (left >= right)
            return;

        int mid = left + (right - left) / 2;
        mergeSort(nums, left, mid);
        mergeSort(nums, mid + 1, right);

        int i = 0, cur1 = left, cur2 = mid + 1;
        while (cur1 <= mid && cur2 <= right)
            tmp[i++] = nums[cur1] <= nums[cur2] ? nums[cur1++] : nums[cur2++];
        while (cur1 <= mid)
            tmp[i++] = nums[cur1++];
        while (cur2 <= right)
            tmp[i++] = nums[cur2++];

        for (int j = left; j <= right; j++)
            nums[j] = tmp[j - left];
    }

    // 4
    vector<vector<int>> fourSum(vector<int> &nums, int target)
    {
        sort(nums.begin(), nums.end());
        vector<vector<int>> ret;
        int n = nums.size();

        int i = 0;
        while (i < n - 3)
        {
            int j = i + 1;
            while (j < n - 2)
            {
                int left = j + 1, right = n - 1;
                while (left < right)
                {
                    long long aim = (long long)target - nums[i] - nums[j];
                    if (aim > nums[left] + nums[right])
                        left++;
                    else if (aim < nums[left] + nums[right])
                        right--;
                    else
                    {
                        ret.push_back({nums[left], nums[right], nums[i], nums[j]});
                        do
                        {
                            left++;
                        } while (left < right && nums[left] == nums[left - 1]);
                        do
                        {
                            right--;
                        } while (left < right && nums[right] == nums[right + 1]);
                    }
                }

                do
                {
                    j++;
                } while (j < n - 2 && nums[j] == nums[j - 1]);
            }

            do
            {
                i++;
            } while (i < n - 3 && nums[i] == nums[i - 1]);
        }

        return ret;
    }

    // 5
    bool containsNearbyDuplicate(vector<int> &nums, int k)
    {
        unordered_map<int, int> hash;
        for (int i = 0; i < nums.size(); i++)
        {
            if (hash.count(nums[i]) && i - hash[nums[i]] <= k)
                return true;
            hash[nums[i]] = i;
        }
        return false;
    }

    ListNode *reverseList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *newhead = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;

        return newhead;
    }
};