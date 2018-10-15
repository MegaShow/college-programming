package main

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

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
