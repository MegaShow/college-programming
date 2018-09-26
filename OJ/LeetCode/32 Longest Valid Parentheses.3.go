package main

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
