// MegaShow
#include <cstdio>

template <class type>
class Stack {  
    public:  
        Stack() {
            top_node = NULL;
            node_num = 0;
        }

        Stack(const Stack &stack) {
            node_num = stack.node_num;
            Node *n, *tmp;
            if (node_num) {
                top_node = new Node(stack.top_node->val);
                n = top_node;
                tmp = stack.top_node->next;
            }
            for (int i = 1; i < node_num; i++) {
                n->next = new Node(tmp->val);
                n = n->next;
                tmp = tmp->next;
            }
        }

        ~Stack() {
            clear();
        }

        bool empty() {
            return node_num == 0;
        }

        size_t size() const {
            return node_num;
        }

        type top() const {
            return top_node->val;
        }

        void push(type element) {
            top_node = new Node(element, top_node);
            node_num++;
        }

        void pop() {
            if (node_num) {
                Node *tmp = top_node;
                top_node = top_node->next;
                delete tmp;
                node_num--;
            }
        }

        void swap(Stack& stack) {
            Node *n, *tmp;
            Stack stmp(stack);
            stack.clear();
            stack.node_num = node_num;
            if (stack.node_num) {
                stack.top_node = new Node(top_node->val);
                n = stack.top_node;
                tmp = top_node->next;
            }
            for (int i = 1; i < stack.node_num; i++) {
                n->next = new Node(tmp->val);
                n = n->next;
                tmp = tmp->next;
            }
            clear();
            node_num = stmp.node_num;
            if (node_num) {
                top_node = new Node(stmp.top_node->val);
                n = top_node;
                tmp = stmp.top_node->next;
            }
            for (int i = 1; i < node_num; i++) {
                n->next = new Node(tmp->val);
                n = n->next;
                tmp = tmp->next;
            }
        }

        void reverse() {
            Stack stmp(*this);
            clear();
            while (!stmp.empty()) {
                push(stmp.top());
                stmp.pop();
            }
        } /*reverse the elements' order in the stack*/

        void clear() {
            while (!empty()) {
                pop();
            }
        }

    private:  
        struct Node {  
            type val;  
            Node* next;  
            Node(type ele, Node *n = NULL) {  
                val = ele;  
                next = n;  
            }  
        };  
        Node *top_node;  
        size_t node_num;  
};