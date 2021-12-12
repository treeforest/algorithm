package leetcode

import "strings"

func wordPattern(pattern string, s string) bool {
	words := strings.Split(s, " ")
	if len(words) != len(pattern) {
		return false
	}
	loc := make(map[byte]int)
	store := make(map[string]int)
	for i := 0; i < len(pattern); i++ {
		x, ok1 := loc[pattern[i]]
		y, ok2 := store[words[i]]
		if !ok1 && !ok2 {
			loc[pattern[i]] = i
			store[words[i]] = i
		} else if ok1 && ok2 && x == y {
			continue
		} else {
			return false
		}
	}
	return true
}
