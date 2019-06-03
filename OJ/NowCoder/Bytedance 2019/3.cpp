struct Nodo {
    Node* next;
    int val;
    Node(int val): val(val), next(NULL) {}
    Node(): val(0), next(NULL) {}
}

Node* add(Node* a, Node* b) {
    Node* p = NULL, root = NULL;
    bool inc = false;
    while (a != NULL && b != NULL) {
        int val = (a->val + b->val) % 10 + (inc ? 1 : 0);
        inc = (a->val + b->val) / 10 == 1;
        if (p == NULL) {
            p = new Node(val);
            root = p;
        } else {
            p->next = new Node(val);
            p = p->next;
        }
        a = a->next;
        b = b->next;
    }
    while (a != NULL) {
        p->next = new Node(a->val + (inc ? 1 : 0));
        p = p->next;
        a = a->next;
        inc = false;
    }
    while (b != NULL) {
        p->next = new Node(b->val + (inc ? 1 : 0));
        p = p->next;
        b = b->next;
        inc = false;
    }
    if (inc) {
        p->next = new Node(1);
    }
    return root;
}
