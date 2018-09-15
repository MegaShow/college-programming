package main

func isMatch(s string, p string) bool {
	lenS, lenP := len(s), len(p)
	dp := make([][]bool, lenS+1)
	for i := 0; i <= lenS; i++ {
		dp[i] = make([]bool, lenP+1)
	}
	dp[lenS][lenP] = true
	for i := lenS; i >= 0; i-- {
		for j := lenP - 1; j >= 0; j-- {
			firstMatch := i != lenS && (s[i] == p[j] || p[j] == '.')
			if j+1 < lenP && p[j+1] == '*' {
				dp[i][j] = dp[i][j+2] || (firstMatch && dp[i+1][j])
			} else {
				dp[i][j] = firstMatch && dp[i+1][j+1]
			}
		}
	}
	return dp[0][0]
}
