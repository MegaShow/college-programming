package main

import "sort"

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func recoverTree(root *TreeNode) {
	var tree []int
	inOrder(root, func(node *TreeNode) { tree = append(tree, node.Val) })
	sort.Ints(tree)
	inOrder(root, func(node *TreeNode) {
		node.Val = tree[0]
		tree = append(tree[1:])
	})
}

func inOrder(root *TreeNode, fn func(*TreeNode)) {
	if root == nil {
		return
	}
	inOrder(root.Left, fn)
	fn(root)
	inOrder(root.Right, fn)
}
