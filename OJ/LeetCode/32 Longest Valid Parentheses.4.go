package main

func longestValidParentheses(s string) (max int) {
	var left, right int
	for i := 0; i < len(s); i++ {
		if s[i] == '(' {
			left++
		} else {
			right++
		}
		if left == right {
			if max < left * 2 {
				max = left * 2
			}
		} else if left < right {
			left, right = 0, 0
		}
	}
	left, right = 0, 0
	for i := len(s) - 1; i >= 0; i-- {
		if s[i] == '(' {
			left++
		} else {
			right++
		}
		if left == right {
			if max < left * 2 {
				max = left * 2
			}
		} else if left > right {
			left, right = 0, 0
		}
	}
	return
}
