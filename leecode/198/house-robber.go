package leetcode

func rob(nums []int) int {
	if len(nums) == 1 {
		return nums[0]
	}
	if len(nums) == 2 {
		return max(nums[0], nums[1])
	}
	n := len(nums)
	dp := make([]int, n)
	dp[0], dp[1] = nums[0], nums[1]
	dp[2] = nums[2] + dp[0]
	for i := 3; i < n; i++ {
		dp[i] = nums[i] + max(dp[i-2], dp[i-3])
	}
	return max(dp[n-1], dp[n-2])
}

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
