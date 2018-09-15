package main

func longestPalindrome(s string) string {
	l := len(s)
	if l == 0 {
		return ""
	}
	var f [1000]int
	for i := 0; i < l-1; i++ {
		lhs, rhs := i-1, i+1
		for lhs >= 0 && rhs < l && s[lhs] == s[rhs] {
			lhs--
			rhs++
		}
		f[i] = rhs - lhs - 1
		lhs, rhs = i, i+1
		for lhs >= 0 && rhs < l && s[lhs] == s[rhs] {
			lhs--
			rhs++
		}
		if f[i] < rhs - lhs - 1 {
			f[i] = rhs - lhs - 1
		}
	}
	var mid int
	for i := range s {
		if f[i] > f[mid] {
			mid = i
		}
	}
	return s[mid-(f[mid]-1)/2 : mid+f[mid]/2+1]
}
