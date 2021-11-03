package leetcode

func calculateMinimumHP(dungeon [][]int) int {
	if len(dungeon) == 0 {
		return 0
	}
	m, n := len(dungeon), len(dungeon[0])
	dp := make([][]int, m)
	for i := 0; i < m; i++ {
		dp[i] = make([]int, n)
	}
	dp[m-1][n-1] = dungeon[m-1][n-1]
	for i := m - 2; i >= 0; i-- {
		dp[i][n-1] = min(dungeon[i][n-1], dp[i+1][n-1]+dungeon[i][n-1])
	}
	for j := n - 2; j >= 0; j-- {
		dp[m-1][j] = min(dungeon[m-1][j], dp[m-1][j+1]+dungeon[m-1][j])
	}
	for i := m - 2; i >= 0; i-- {
		for j := n - 2; j >= 0; j-- {
			if dp[i+1][j] >= 0 || dp[i][j+1] >= 0 {
				dp[i][j] = dungeon[i][j]
			} else {
				dp[i][j] = dungeon[i][j] + max(dp[i+1][j], dp[i][j+1])
			}
		}
	}
	if dp[0][0] > 0 {
		return 1
	}
	return 1 - dp[0][0]
}

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}
