package leetcode

func maximumUniqueSubarray(nums []int) int {
	l, r, mp := 0, 0, make(map[int]struct{})
	ans, tmp, n := 0, 0, len(nums)
	for r < n {
		if _, ok := mp[nums[r]]; ok {
			ans = max(ans, tmp)
			for nums[l] != nums[r] {
				delete(mp, nums[l])
				tmp -= nums[l]
				l++
			}
			l++
		} else {
			mp[nums[r]] = struct{}{}
			tmp += nums[r]
		}
		r++
	}
	ans = max(ans, tmp)
	return ans
}

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
