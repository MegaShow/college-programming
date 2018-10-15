package main

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

var firstNode, secondNode, prevNode *TreeNode

func recoverTree(root *TreeNode) {
	firstNode, secondNode, prevNode = nil, nil, nil
	inOrder(root)
	firstNode.Val, secondNode.Val = secondNode.Val, firstNode.Val
}

func inOrder(root *TreeNode) {
	if root == nil {
		return
	}
	inOrder(root.Left)
	if firstNode == nil && prevNode != nil && prevNode.Val > root.Val {
		firstNode = prevNode
	}
	if firstNode != nil && prevNode.Val > root.Val {
		secondNode = root
	}
	prevNode = root
	inOrder(root.Right)
}
