func isPalindrome(x int) bool {
	if x < 0 {
		return false
	}
	var y int
	for t := x; t != 0; t /= 10 {
		y = y*10 + t%10
	}
	return x == y
}
