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
#include <sstream>
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
    vector<int> rearrangeBarcodes(vector<int> &barcodes)
    {
        int n = barcodes.size(), maxVal = 0, maxCount = 0;
        unordered_map<int, int> hash;

        for (auto num : barcodes)
            if (++hash[num] > maxCount)
            {
                maxCount = hash[num];
                maxVal = num;
            }

        vector<int> ret(n);
        int index = 0;
        for (int i = 0; i < maxCount; i++)
        {
            ret[index] = maxVal;
            index += 2;
        }

        hash.erase(maxVal);
        for (auto [a, b] : hash)
            for (int i = 0; i < b; i++)
            {

                if (index >= n)
                    index = 1;

                ret[index] = a;
                index += 2;
            }

        return ret;
    }

    // 2
    int numberOfArithmeticSlices(vector<int> &nums)
    {
        int n = nums.size();
        if (n < 3)
            return 0;

        int sum = 0, prev = 0;
        for (int i = 2; i < n; i++)
        {
            if (nums[i] - nums[i - 1] == nums[i - 1] - nums[i - 2])
            {
                prev += 1;
                sum += prev;
            }
            else
                prev = 0;
        }

        return sum;
    }

    // 3
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        int i = 0;
        return _buildTree(preorder, inorder, i, 0, inorder.size() - 1);
    }

    TreeNode *_buildTree(vector<int> &preorder, vector<int> &inorder, int &previ, int inBegin, int inEnd)
    {
        if (inBegin > inEnd)
            return nullptr;

        TreeNode *root = new TreeNode(preorder[previ]);

        int rooti = inBegin;
        while (rooti <= inEnd)
            if (inorder[rooti] == preorder[previ])
                break;
            else
                rooti++;

        previ++;
        root->left = _buildTree(preorder, inorder, previ, inBegin, rooti - 1);
        root->right = _buildTree(preorder, inorder, previ, rooti + 1, inEnd);

        return root;
    }
};