package leetcode

func getRow(rowIndex int) []int {
	n := rowIndex + 1
	dp := make([][]int, n)
	for i := 0; i <= rowIndex; i++ {
		dp[i] = make([]int, i+1)
		dp[i][0] = 1
		dp[i][i] = 1
	}
	for i := 1; i <= rowIndex; i++ {
		for j := 1; j < i; j++ {
			dp[i][j] = dp[i-1][j-1] + dp[i-1][j]
		}
	}
	return dp[rowIndex]
}
