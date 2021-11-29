package leetcode

func isLetter(c byte) bool {
	if c >= 'a' && c <= 'z' {
		return true
	}
	return false
}

func decodeAtIndex(s string, k int) string {
	length := 0
	for i := 0; i < len(s); i++ {
		if isLetter(s[i]) {
			length++
			if length == k {
				return string(s[i])
			}
		} else {
			if length*int(s[i]-'0') >= k {
				if k%length != 0 {
					return decodeAtIndex(s[:i], k%length)
				}
				return decodeAtIndex(s[:i], length)
			}
			length *= int(s[i] - '0')
		}
	}
	return ""
}
