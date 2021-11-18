package leetcode

func containsNearbyAlmostDuplicate(nums []int, k int, t int) bool {
	if len(nums) <= 1 || k <= 0 {
		return false
	}
	n := len(nums)
	for i := 0; i < n; i++ {
		count := 0
		for j := i + 1; j < n && count < k; j++ {
			if abs(nums[i]-nums[j]) <= t {
				return true
			}
			count++
		}
	}
	return false
}

func abs(a int) int {
	if a > 0 {
		return a
	}
	return -a
}
