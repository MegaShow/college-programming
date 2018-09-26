package main

import (
	"container/heap"
)

type ListNode struct {
	Val  int
	Next *ListNode
}

// Item 是优先队列中包含的元素。
type Item struct {
	value    int
	// 元素的索引可以用于更新操作，它由 heap.Interface 定义的方法维护。
	index int // 元素在堆中的索引。
}

// 一个实现了 heap.Interface 接口的优先队列，队列中包含任意多个 Item 结构。
type PriorityQueue []*Item

func (pq PriorityQueue) Len() int { return len(pq) }

func (pq PriorityQueue) Less(i, j int) bool {
	return pq[i].value < pq[j].value
}

func (pq PriorityQueue) Swap(i, j int) {
	pq[i], pq[j] = pq[j], pq[i]
	pq[i].index = i
	pq[j].index = j
}

func (pq *PriorityQueue) Push(x interface{}) {
	n := len(*pq)
	item := x.(*Item)
	item.index = n
	*pq = append(*pq, item)
}

func (pq *PriorityQueue) Pop() interface{} {
	old := *pq
	n := len(old)
	item := old[n-1]
	item.index = -1 // 为了安全性考虑而做的设置
	*pq = old[0 : n-1]
	return item
}

// 更新函数会修改队列中指定元素的优先级以及值。
func (pq *PriorityQueue) update(item *Item, value int) {
	item.value = value
	heap.Fix(pq, item.index)
}

func mergeKLists(lists []*ListNode) *ListNode {
	var arr []int
	for _, l := range lists {
		for l != nil {
			arr = append(arr, l.Val)
			l = l.Next
		}
	}
	pq := make(PriorityQueue, len(arr))
	for i, v := range arr {
		pq[i] = &Item{
			value:    v,
			index:    i,
		}
	}
	heap.Init(&pq)
	res := new(ListNode)
	n := res
	for pq.Len() > 0 {
		n.Next = &ListNode{Val: heap.Pop(&pq).(*Item).value}
		n = n.Next
	}
	return res.Next
}
