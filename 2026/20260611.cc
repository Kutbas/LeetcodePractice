#include <bits/stdc++.h>
#include <mutex>
using namespace std;


class Solution {
public:
    // 1
	vector<TreeNode*> TreeList;

	void Inorder(TreeNode* root)
	{
		if(root==nullptr)
			return;

		Inorder(root->left);
		TreeList.push_back(root);
		Inorder(root->right);
	}

    TreeNode* Convert(TreeNode* pRootOfTree) {
        if(pRootOfTree==nullptr)
			return nullptr;

		Inorder(pRootOfTree);

		for(int i=1;i<TreeList.size();i++)
		{
			TreeList[i]->left=TreeList[i-1];
			TreeList[i-1]->right=TreeList[i];
		}

		return TreeList[0];
    }

    // 2
};