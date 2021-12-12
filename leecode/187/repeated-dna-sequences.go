package leetcode

func findRepeatedDnaSequences(s string) []string {
	count, n := make(map[string]int), len(s)
	for i := 0; i <= n-10; i++ {
		count[s[i:i+10]]++
	}
	ans := []string{}
	for k, v := range count {
		if v >= 2 {
			ans = append(ans, k)
		}
	}
	return ans
}
