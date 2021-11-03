func partition(s string) [][]string {
	n := len(s)
	f := make([][]int, n)
	for i := range f {
		f[i] = make([]int, n)
	}

	var isPalindrome func(i, j int) int
	isPalindrome = func(i, j int) int {
		if i >= j {
			return 1
		}
		if f[i][j] == 0 {
			f[i][j] = -1
			if s[i] == s[j] {
				f[i][j] = isPalindrome(i+1, j-1)
			}
		}
		return f[i][j]
	}

	ans := [][]string{}
	splits := []string{}

	var dfs func(i int)
	dfs = func(i int) {
		if i == n {
			ans = append(ans, append([]string(nil), splits...))
			return
		}
		for j := i; j < n; j++ {
			if isPalindrome(i, j) > 0 {
				splits = append(splits, s[i:j+1])
				dfs(j + 1)
				splits = splits[:len(splits)-1]
			}
		}
	}

	dfs(0)
	return ans
}