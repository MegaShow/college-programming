/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
private:
    TreeNode* build(vector<int>& pre, int ps, int pe, vector<int>& in, int is, int ie) {
        if (ps >= pe || is >= ie) return NULL;
        TreeNode* root = new TreeNode(pre[ps]);
        int index = 0;
        while (is + index < ie && pre[ps] != in[is + index]) {
            index++;
        }
        root->left = build(pre, ps+1, ps+1+index, in, is, is+index);
        root->right = build(pre, ps+index+1, pe, in, is+1+index, ie);
        return root;
    }

public:
    TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> vin) {
        if (vin.size() == 0) return NULL;
        return build(pre, 0, pre.size(), vin, 0, vin.size());
    }
};
