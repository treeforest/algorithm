package leetcode

func partitionLabels(s string) []int {
	mp := make(map[rune]int)
	for i, c := range s {
		mp[c] = i
	}
	pre, cur := -1, 0
	ans := make([]int, 0)
	for i, c := range s {
		j := mp[c]
		if j > cur {
			cur = j
		} else if i == cur {
			ans = append(ans, cur-pre)
			pre = cur
			cur++
		}
	}
	return ans
}
