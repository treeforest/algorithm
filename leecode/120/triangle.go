package leetcode

func minimumTotal(triangle [][]int) int {
	n := len(triangle)
	dp := make([][]int, n)
	for i := 0; i < n; i++ {
		dp[i] = make([]int, i+1)
	}
	dp[0][0] = triangle[0][0]
	for i := 1; i < n; i++ {
		dp[i][0] = dp[i-1][0] + triangle[i][0]
		j := 1
		for ; j < i; j++ {
			dp[i][j] = min(dp[i-1][j-1]+triangle[i][j], dp[i-1][j]+triangle[i][j])
		}
		dp[i][j] = dp[i-1][j-1] + triangle[i][j]
	}
	res := dp[n-1][0]
	for i := 1; i < n; i++ {
		res = min(res, dp[n-1][i])
	}
	return res
}

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}
