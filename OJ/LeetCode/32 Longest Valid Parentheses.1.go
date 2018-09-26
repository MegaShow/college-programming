package main

func longestValidParentheses(s string) int {
	max, l := 0, len(s)
	for i := 0; i < l; i++ {
		for valid, index := i, 0; valid < l && index >= 0; valid++ {
			if s[valid] == '(' {
				index++
			} else {
				index--
			}
			if index == 0 && max < valid-i+1 {
				max = valid - i + 1
			}
		}
	}
	return max
}
