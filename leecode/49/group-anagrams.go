package leetcode

import "sort"

type S []byte

func (s S) Len() int {
	return len(s)
}
func (s S) Less(i, j int) bool {
	return s[i] < s[j]
}
func (s S) Swap(i, j int) {
	s[i], s[j] = s[j], s[i]
}

func groupAnagrams(strs []string) [][]string {
	mp := make(map[string]int)
	ans := make([][]string, 0)
	for _, str := range strs {
		s := S(str)
		sort.Sort(s)
		if k, ok := mp[string(s)]; ok {
			ans[k] = append(ans[k], str)
		} else {
			mp[string(s)] = len(ans)
			ans = append(ans, []string{str})
		}
	}
	return ans
}
