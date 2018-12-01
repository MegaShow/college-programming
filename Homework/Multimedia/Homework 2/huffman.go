package main

import "sort"

type Node struct {
	Left   *Node
	Right  *Node
	Parent *Node
	Value  uint
	Factor int
}

func GetHuffmanTree(arr []uint) *Node {
	m := make(map[uint]int)
	for _, v := range arr {
		m[v]++
	}
	var nodes []*Node
	for k, v := range m {
		nodes = append(nodes, &Node{Value: k, Factor: v})
	}
	for len(nodes) > 1 {
		sort.Slice(nodes, func(i, j int) bool {
			return nodes[i].Factor < nodes[j].Factor
		})
		newNode := &Node{Left: nodes[0], Right: nodes[1], Factor: nodes[0].Factor + nodes[1].Factor}
		nodes[0].Parent, nodes[1].Parent = newNode, newNode
		nodes = append(nodes[2:], newNode)
	}
	if len(nodes) == 1 {
		return nodes[0]
	}
	return nil
}

func GetHuffmanTableMap(root *Node) map[uint]string {
	table := make(map[uint]string)
	scan(root, "", &table)
	return table
}

func scan(root *Node, prefix string, table *map[uint]string) {
	if root.Left == nil || root.Right == nil {
		(*table)[root.Value] = prefix
	}
	if root.Left != nil {
		scan(root.Left, prefix + "0", table)
	}
	if root.Right != nil {
		scan(root.Right, prefix + "1", table)
	}
}
