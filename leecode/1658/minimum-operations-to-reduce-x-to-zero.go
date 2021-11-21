package leetcode

func minOperations(nums []int, x int) int {
	total := 0
	for _, num := range nums {
		total += num
	}
	target := total - x
	if target < 0 {
		return -1
	}
	if target == 0 {
		return len(nums)
	}
	l, r, sum, res, n := 0, 0, 0, -1, len(nums)
	for r < n {
		if sum < target {
			sum += nums[r]
			r++
		}
		for sum >= target {
			if sum == target {
				res = max(res, r-l)
			}
			sum -= nums[l]
			l++
		}
	}
	if res == -1 {
		return -1
	}
	return n - res
}

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
