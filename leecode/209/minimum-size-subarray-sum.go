package leetcode

func minSubArrayLen(target int, nums []int) int {
	l, r, sum, res, n := 0, 0, 0, len(nums)+1, len(nums)
	for r < n {
		sum += nums[r]
		for sum >= target {
			res = min(res, r-l+1)
			sum -= nums[l]
			l++
		}
		r++
	}
	if res == n+1 {
		return 0
	}
	return res
}

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}
