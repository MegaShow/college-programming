// MegaShow
#ifndef MP_HPP_
#define MP_HPP_

#include <iostream>
#define MAX_INIT 0

namespace MP {
    struct TreeNode {
        int val;
        int id;
        TreeNode* left;
        TreeNode* right;
        TreeNode(int x, int i) :val(x), id(i), left(NULL), right(NULL) {}
    };


    class MaxPath {
        private:
        int max;

        public:
        MaxPath() :max(MAX_INIT) {}
        int findMaxPath(TreeNode* n);

    };
}

#endif