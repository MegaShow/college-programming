package main

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
