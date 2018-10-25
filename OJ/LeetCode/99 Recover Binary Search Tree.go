package main

import "sort"

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

// Solution 1
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

// Solution 2
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

// Solution 3
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

// Solution 4
func recoverTree(root *TreeNode) {
	var curNode, prevNode, tmpNode, firstNode, secondNode *TreeNode
	check := func () {
		if firstNode == nil && prevNode != nil && prevNode.Val > curNode.Val {
			firstNode = prevNode
		}
		if firstNode != nil && prevNode.Val > curNode.Val {
			secondNode = curNode
		}
	}
	curNode = root
	for curNode != nil {
		if curNode.Left == nil {
			check()
			prevNode, curNode = curNode, curNode.Right
		} else {
			tmpNode = curNode.Left
			for tmpNode.Right != nil && tmpNode.Right != curNode {
				tmpNode = tmpNode.Right
			}
			if tmpNode.Right == nil {
				tmpNode.Right, curNode = curNode, curNode.Left
			} else {
				check()
				tmpNode.Right, prevNode, curNode = nil, curNode, curNode.Right
			}
		}
	}
	firstNode.Val, secondNode.Val = secondNode.Val, firstNode.Val
}
