package main

type ListNode struct {
	Val  int
	Next *ListNode
}

// Solution 1
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

// Solution 2
func reverseKGroup(head *ListNode, k int) *ListNode {
	if head == nil {
		return nil
	}
	newHead := head
	var i int
	for i = 0; i < k - 1 && newHead.Next != nil; i++ {
		newHead = newHead.Next
	}
	if  i != k - 1 {
		return head
	}
	var first, next, p *ListNode = reverseKGroup(newHead.Next, k), nil, head
	for i = 0; i < k; i++ {
		next, p.Next = p.Next, first
		first, p = p, next
	}
	return newHead
}
