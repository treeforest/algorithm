package leetcode

func isSubsequence(s string, t string) bool {
	if s == "" {
		return true
	}
	i := 0
	for j, _ := range t {
		if t[j] == s[i] {
			i++
			if i == len(s) {
				return true
			}
		}
	}
	return false
}
