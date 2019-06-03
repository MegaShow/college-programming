int FindLowesstCommonAncestor(Node* root, std::vector<Node*>& nodeList) {
    bool hasAncestor = true;
    return find(root, nodeList, &hasAncestor);
}

int find(Node* root, std::vector<Node*>& nodeList, bool* hasAncestor) {
    if (root == NULL) {
        hasAncestor = false;
        return 0;
    }
    bool left = true, right = true;
    int leftAncestor = find(root->left, nodeList, &left);
    int rightAncestor = find(root->right, nodeList, &right);
    int ancestor;
    if (left && right) {
       return root->x;
    } else if (left) {
        ancestor = leftAncestor;
    } else if (right) {
        ancestor = rightAncestor;
    } else {
        hasAncestor = false;
    }
    if (std::find(nodeList.begin(), nodeList.end(), root->x) != nodeList.end()) {
        ancestor = root->x;
        hasAncestor = true;
    }
    return ancestor;
}

int FindLowesstCommonAncestor(Node* root, std::vector<Node*>& nodeList) {
    bool hasAncestor = true;
    std::unorder_set<int> s;
    for (auto &n: nodeList) {
        s.insert(n->x);
    }
    return find(root, s, &hasAncestor);
}

int find(Node* root, std::unorder_set<int>& nodeSet, bool* hasAncestor) {
    if (root == NULL) {
        hasAncestor = false;
        return 0;
    }
    bool left = true, right = true;
    int leftAncestor = find(root->left, nodeList, &left);
    int rightAncestor = find(root->right, nodeList, &right);
    int ancestor;
    if (left && right) {
       return root->x;
    } else if (left) {
        ancestor = leftAncestor;
    } else if (right) {
        ancestor = rightAncestor;
    } else {
        hasAncestor = false;
    }
    if (nodeSet.count(root->x)) {
        ancestor = root->x;
        hasAncestor = true;
    }
    return ancestor;
}

