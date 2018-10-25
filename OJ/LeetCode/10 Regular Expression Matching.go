package main

// Solution 1
func isMatch(s string, p string) bool {
	if len(s) == 0 && len(p) == 0 {
		return true
	} else if len(p) == 0 && len(s) != 0 {
		return false
	} else if p[0] == '.' && (len(p) == 1 || p[1] != '*') {
		if len(s) == 0 {
			return false
		}
		return isMatch(s[1:], p[1:])
	} else if p[0] == '.' {
		if isMatch(s, p[2:]) {
			return true
		}
		for i := 0; i < len(s); i++ {
			if isMatch(s[i+1:], p[2:]) {
				return true
			}
		}
	} else {
		if len(p) != 1 && p[1] == '*' {
			if isMatch(s, p[2:]) {
				return true
			}
			if len(s) != 0 {
				c := p[0]
				for i := 0; i < len(s) && c == s[i]; i++ {
					if isMatch(s[i+1:], p[2:]) {
						return true
					}
				}
			}
		} else if len(s) == 0 {
			return false
		} else if p[0] == s[0] {
			return isMatch(s[1:], p[1:])
		} else {
			return false
		}
	}
	return false
}

// Solution 2
func isMatch(s string, p string) bool {
	if len(p) == 0 {
		return len(s) == 0
	}
	firstMatch := len(s) != 0 && (s[0] == p[0] || p[0] == '.')
	if len(p) > 1 && p[1] == '*' {
		return isMatch(s, p[2:]) || (firstMatch && isMatch(s[1:], p))
	}
	return firstMatch && isMatch(s[1:], p[1:])
}

// Solution 3
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
