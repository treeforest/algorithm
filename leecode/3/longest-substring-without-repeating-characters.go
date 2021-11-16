package leetcode

func lengthOfLongestSubstring(s string) int {
	if s == "" {
		return 0
	}
	mp := make(map[byte]bool)
	l, r, n, longest := 0, 0, len(s), 0
	for r < n {
		c := s[r]
		if _, ok := mp[c]; ok {
			longest = max(longest, r-l)
			for l < r && s[l] != c {
				delete(mp, s[l])
				l++
			}
			l++
		} else {
			mp[c] = true
		}
		r++
	}
	longest = max(longest, r-l)
	return longest
}

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
