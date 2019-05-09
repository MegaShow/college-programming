/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if (head == NULL || head->next == NULL) return head;
        ListNode *prev, *slow = head, *fast = head;
        while (fast != NULL && fast->next != NULL) {
            prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        prev->next = NULL;
        head = sortList(head);
        slow = sortList(slow);
        return mergeList(head, slow);
    }

private:
    ListNode* mergeList(ListNode* l, ListNode* r) {
        ListNode root(0);
        ListNode* p = &root;
        while (l != NULL && r != NULL) {
            if (l->val < r->val) {
                p->next = l;
                l = l->next;
            } else {
                p->next = r;
                r = r->next;
            }
            p = p->next;
        }
        if (l != NULL) p->next = l;
        else p->next = r;
        return root.next;
    }
};
