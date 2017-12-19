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
    bool findTarget(TreeNode* root, int k) {
        vector<int> v;
        function<void(TreeNode*)> func;
        func = [&v, &func](TreeNode* n) -> void {
            if (n != NULL) {
                v.push_back(n->val);
                func(n->left);
                func(n->right);
            }
        };
        func(root);
        map<int, int> m;
        for (int i = 0; i < v.size(); i++) {
            int var = k - v[i];
            if (m.count(var)) {
                return true;
            }
            m[v[i]] = i;
        }
        return false;
    }
};
