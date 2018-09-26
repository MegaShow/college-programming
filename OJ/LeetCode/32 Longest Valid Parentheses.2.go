package main

func longestValidParentheses(s string) int {
	max, stack := 0, []int{-1}
	for valid := 0; valid < len(s); valid++ {
		if s[valid] == '(' {
			stack = append(stack, valid)
		} else {
			stack = append(stack[0 : len(stack)-1])
			l := len(stack)
			if l == 0 {
				stack = []int{valid}
			} else if max < valid-stack[len(stack)-1] {
				max = valid - stack[len(stack)-1]
			}
		}
	}
	return max
}
