package main

// Solution 1
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

// Solution 2
import "math"

var resMap map[string]bool
var minDeleteNum int

func removeInvalidParentheses(s string) (res []string) {
	resMap = make(map[string]bool)
	minDeleteNum = math.MaxInt32
	dfs(0, 0, 0, 0, s, "")
	for k := range resMap {
		res = append(res, k)
	}
	return
}

func dfs(depth, left, right, deleteNum int, s, str string) {
	if depth == len(s) {
		if left == right {
			if deleteNum < minDeleteNum {
				minDeleteNum = deleteNum
				resMap = make(map[string]bool)
			}
			if deleteNum == minDeleteNum {
				resMap[str] = true
			}
		}
	} else {
		if s[depth] != '(' && s[depth] != ')' {
			dfs(depth+1, left, right, deleteNum, s, str+string(s[depth]))
		} else {
			dfs(depth+1, left, right, deleteNum+1, s, str)
			if s[depth] == '(' {
				dfs(depth+1, left+1, right, deleteNum, s, str+"(")
			} else if left > right {
				dfs(depth+1, left, right+1, deleteNum, s, str+")")
			}
		}
	}
}

// Solution 3
var resMap map[string]bool

func removeInvalidParentheses(s string) (res []string) {
	resMap = make(map[string]bool)
	var leftRem, rightRem int
	for _, v := range s {
		if v == '(' {
			leftRem++
		} else if v == ')' && leftRem == 0 {
			rightRem++
		} else if v == ')' {
			leftRem--
		}
	}
	dfs(0, 0, 0, leftRem, rightRem, s, "")
	for k := range resMap {
		res = append(res, k)
	}
	return
}

func dfs(depth, left, right, leftRem, rightRem int, s, str string) {
	if depth == len(s) {
		if left == right {
			resMap[str] = true
		}
	} else {
		if s[depth] != '(' && s[depth] != ')' {
			dfs(depth+1, left, right, leftRem, rightRem, s, str+string(s[depth]))
		} else if s[depth] == '(' {
			dfs(depth+1, left+1, right, leftRem, rightRem, s, str+"(")
		} else if left > right {
			dfs(depth+1, left, right+1, leftRem, rightRem, s, str+")")
		}
		if s[depth] == '(' && leftRem != 0 {
			dfs(depth+1, left, right, leftRem-1, rightRem, s, str)
		} else if s[depth] == ')' && rightRem != 0 {
			dfs(depth+1, left, right, leftRem, rightRem-1, s, str)
		}
	}
}
