package main

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
