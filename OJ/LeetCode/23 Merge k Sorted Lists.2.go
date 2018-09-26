package main

type ListNode struct {
	Val  int
	Next *ListNode
}

func mergeKLists(lists []*ListNode) *ListNode {
	l := len(lists)
	if l == 0 {
		return nil
	} else if l == 1 {
		return lists[0]
	}
	a, b := mergeKLists(lists[:l/2]), mergeKLists(lists[l/2:])
	res := new(ListNode)
	n := res
	for a != nil && b != nil {
		if a.Val <= b.Val {
			n.Next = &ListNode{Val: a.Val}
			n = n.Next
			a = a.Next
		} else {
			n.Next = &ListNode{Val: b.Val}
			n = n.Next
			b = b.Next
		}
	}
	for a != nil {
		n.Next = &ListNode{Val: a.Val}
		n = n.Next
		a = a.Next
	}
	for b != nil {
		n.Next = &ListNode{Val: b.Val}
		n = n.Next
		b = b.Next
	}
	return res.Next
}
