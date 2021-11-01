package leetcode

func numTrees(n int) int {
	dp := make([]int, n+1)
	// 左右子树的数字与子树的个数没有关系
	dp[0], dp[1] = 1, 1
	for i := 2; i <= n; i++ {
		for j := 1; j <= i; j++ {
			dp[i] += dp[j-1] * dp[i-j]
		}
	}
	return dp[n]
}
