package main

type ListNode struct {
	Val  int
	Next *ListNode
}

func mergeKLists(lists []*ListNode) *ListNode {
	l := len(lists)
	if l == 0 {
		return nil
	}
	for step := 1; step < l; step *= 2 {
		for i := 0; i < l && i+step < l; i += 2 * step {
			res := new(ListNode)
			n, a, b := res, lists[i], lists[i+step]
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
			lists[i] = res.Next
		}
	}
	return lists[0]
}
