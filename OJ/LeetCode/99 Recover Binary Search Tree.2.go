package main

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func recoverTree(root *TreeNode) {
	var tree []*TreeNode
	inOrder(root, func(node *TreeNode) { tree = append(tree, node) })
	var firstNode, secondNode *TreeNode
	for i := 0; i < len(tree); i++ {
		if firstNode == nil && tree[i].Val > tree[i+1].Val {
			firstNode = tree[i]
			continue
		}
		if firstNode != nil && tree[i].Val < tree[i-1].Val {
			if secondNode == nil {
				secondNode = tree[i]
			} else {
				secondNode = tree[i]
				break
			}
		}
	}
	firstNode.Val, secondNode.Val = secondNode.Val, firstNode.Val
}

func inOrder(root *TreeNode, fn func(*TreeNode)) {
	if root == nil {
		return
	}
	inOrder(root.Left, fn)
	fn(root)
	inOrder(root.Right, fn)
}
