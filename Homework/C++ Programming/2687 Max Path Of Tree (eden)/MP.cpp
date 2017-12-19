// MegaShow
#include <queue>
#include "MP.hpp"

namespace MP {
    int MaxPath::findMaxPath(TreeNode* n) {
        max = 0;
        std::queue<std::pair<TreeNode*, int> > q;
        q.push(std::make_pair(n, n->val));
        while (!q.empty()) {
            std::pair<TreeNode*, int> tmp = q.front();
            q.pop();
            if (tmp.first->left) {
                q.push(std::make_pair(tmp.first->left, tmp.second+tmp.first->left->val));
            } else {
                if (max < tmp.second) {
                    max = tmp.second;
                }
            }
            if (tmp.first->right) {
                q.push(std::make_pair(tmp.first->right, tmp.second+tmp.first->right->val));
            } else {
                if (max < tmp.second) {
                    max = tmp.second;
                }
            }
        }
        return max;
    }
}