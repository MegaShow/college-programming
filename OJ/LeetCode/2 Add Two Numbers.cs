/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     public int val;
 *     public ListNode next;
 *     public ListNode(int x) { val = x; }
 * }
 */
public class Solution {
    public ListNode AddTwoNumbers(ListNode l1, ListNode l2) {
        ListNode root = new ListNode((l1.val + l2.val) % 10);
        ListNode p = root;
        int carry = (l1.val + l2.val) / 10;
        while (l1.next != null && l2.next != null) {
            l1 = l1.next;
            l2 = l2.next;
            p.next = new ListNode((l1.val + l2.val + carry) % 10);
            carry = (l1.val + l2.val + carry) / 10;
            p = p.next;
        }
        while (l1.next != null) {
            l1 = l1.next;
            p.next = new ListNode((l1.val + carry) % 10);
            carry = (l1.val + carry) / 10;
            p = p.next;
        }
        while (l2.next != null) {
            l2 = l2.next;
            p.next = new ListNode((l2.val + carry) % 10);
            carry = (l2.val + carry) / 10;
            p = p.next;
        }
        if (carry != 0) {
            p.next = new ListNode(carry);
        }
        return root;
    }
}
