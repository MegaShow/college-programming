package main

// Solution 1
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

// Solution 2
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

// Solution 3
func longestValidParentheses(s string) (max int) {
	dp := make([]int, len(s))
	for i := 1; i < len(s); i++ {
		if s[i] == ')' {
			if s[i-1] == '(' {
				if i == 1 {
					dp[i] = 2
				} else {
					dp[i] = dp[i-2] + 2
				}
			} else if i-1-dp[i-1] >= 0 && s[i-1-dp[i-1]] == '(' {
				if i-2-dp[i-1] >= 0 {
					dp[i] = dp[i-1] + 2 + dp[i-2-dp[i-1]]
				} else {
					dp[i] = dp[i-1] + 2
				}
			}
			if max < dp[i] {
				max = dp[i]
			}
		}
	}
	return
}

// Solution 4
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
