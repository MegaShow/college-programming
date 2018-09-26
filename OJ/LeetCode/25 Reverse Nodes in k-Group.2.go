package main

type ListNode struct {
	Val  int
	Next *ListNode
}

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
