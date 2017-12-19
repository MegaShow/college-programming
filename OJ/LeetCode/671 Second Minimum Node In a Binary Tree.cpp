/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int findSecondMinimumValue(TreeNode* root) {
        int min = -1, out = -1;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode* n = q.front();
            q.pop();
            if (min == -1) {
                min = n->val;
            } else if (min < n->val && out == -1) {
                out = n->val;
            } else if (min > n->val) {
                out = min;
                min = n->val;
            } else if (min < n->val && out > n->val) {
                out = n->val;
            }
            //cout << min << " " << out << endl;
            if (n->left) {
                q.push(n->left);
            }
            if (n->right) {
                q.push(n->right);
            }
        }
        return out;
    }
};
