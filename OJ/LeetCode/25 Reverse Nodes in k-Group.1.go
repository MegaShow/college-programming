package main

type ListNode struct {
	Val  int
	Next *ListNode
}

func reverseKGroup(head *ListNode, k int) *ListNode {
	var p, prev *ListNode = head, nil
	for p != nil {
		var first, next, pprev *ListNode = nil, nil, p
		var i int
		for i = 0; p != nil && i < k; i++ {
			next, p.Next = p.Next, first
			first, p = p, next
		}
		if p == nil && i != k {
			p, first = first, nil
			for ; i > 0; i-- {
				next, p.Next = p.Next, first
				first, p = p, next
			}
			p = nil
		}
		if prev == nil {
			head = first
		} else {
			prev.Next = first
		}
		prev = pprev
 	}
	return head
}
