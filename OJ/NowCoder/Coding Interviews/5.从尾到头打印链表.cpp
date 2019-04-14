/**
*  struct ListNode {
*        int val;
*        struct ListNode *next;
*        ListNode(int x) :
*              val(x), next(NULL) {
*        }
*  };
*/
class Solution {
public:
    vector<int> printListFromTailToHead(ListNode* head) {
        int c = 0;
        for (ListNode* n = head; n != NULL; n = n->next) {
            c++;
        }
        vector<int> res(c);
        for (ListNode* n = head; n != NULL; n = n->next) {
            res[--c] = n->val;
        }
        return res;
    }
};
