package leetcode

func climbStairs(n int) int {
	pre, cur := 1, 1
	for i := 1; i < n; i++ {
		cur = cur + pre
		pre = cur - pre
	}
	return cur
}
