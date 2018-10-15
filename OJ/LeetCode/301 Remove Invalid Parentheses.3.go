package main

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
