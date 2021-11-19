package leetcode

import "strings"

func longestSubstring(s string, k int) int {
	if s == "" {
		return 0
	}
	freq, split, res := [26]int{}, byte(0), 0
	for _, c := range s {
		freq[c-'a']++
	}
	for i, n := range freq {
		if 0 < n && n < k {
			split = 'a' + byte(i)
			break
		}
	}
	if split == byte(0) {
		return len(s)
	}
	for _, substr := range strings.Split(s, string(split)) {
		res = max(res, longestSubstring(substr, k))
	}
	return res
}

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
