// MegaShow
#ifndef BEAUTIFULTREE_HPP_
#define BEAUTIFULTREE_HPP_

#include <iostream>
#include <algorithm>
#include <string>
#include <map>
using namespace std;

namespace HFM {
    class HuffmanCode {
        private:
        struct Node {
            int val;
            int code;
            Node* left;
            Node* right;
            Node(int _val, int _code, Node* _left = NULL, Node* _right = NULL)
                : val(_val), code(_code), left(_left), right(_right) {}
        };
        Node* root;
        int size;
        string org;

        public:
        explicit HuffmanCode(const string &str);
        HuffmanCode(int w[], int n);
        ~HuffmanCode();
        void DisplayCode();
        static void inOrder(Node* n, map<int, pair<int, string> >& m, string str);
        static void deleteNode(Node* n);
    };
}

#endif
