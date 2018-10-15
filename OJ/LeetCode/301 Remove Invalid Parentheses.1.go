package main

import (
	"math"
)

type item struct {
	str         string
	deleteIndex int
	deleteNum   int
}

func removeInvalidParentheses(s string) []string {
	queue := []item{{str: s}}
	resMap := make(map[string]bool, 0)
	deleteNum := math.MaxInt32
	for len(queue) > 0 {
		front := queue[0]
		queue = append(queue[1:])
		if front.deleteNum > deleteNum {
			continue
		}
		if check(front.str) {
			deleteNum = front.deleteNum
			resMap[front.str] = true
		} else {
			for i := front.deleteIndex; i < len(front.str); i++ {
				str := front.str[:i]
				if i+1 < len(front.str) {
					str += front.str[i+1:]
				}
				queue = append(queue, item{str: str, deleteNum: front.deleteNum + 1, deleteIndex: i})
			}
		}
	}
	var res []string
	for k := range resMap {
		res = append(res, k)
	}
	return res
}

func check(s string) bool {
	stackTop := -1
	for _, v := range s {
		if v == '(' {
			stackTop++
		} else if v == ')' {
			if stackTop == -1 {
				return false
			}
			stackTop--
		}
	}
	return stackTop == -1
}
