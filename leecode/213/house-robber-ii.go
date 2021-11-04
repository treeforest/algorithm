package leetcode

func rob(nums []int) int {
	if len(nums) == 0 {
		return 0
	}
	if len(nums) == 1 {
		return nums[0]
	}
	if len(nums) == 2 {
		return max(nums[0], nums[1])
	}

	n := len(nums)
	return max(more(nums, 0, n-1), more(nums, 1, n))
}

func more(nums []int, start, end int) int {
	pre := nums[start]
	cur := max(pre, nums[start+1])
	for i := start + 2; i < end; i++ {
		tmp := cur
		cur = max(cur, nums[i]+pre)
		pre = tmp
	}
	return cur
}

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
