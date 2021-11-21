package leetcode

func maxResult(nums []int, k int) int {
	q, n := make([]int, 0), len(nums)
	push := func(i int) {
		for len(q) > 0 && nums[q[len(q)-1]] < nums[i] {
			q = q[:len(q)-1]
		}
		q = append(q, i)
	}
	push(0)
	for i := 1; i < n; i++ {
		for q[0] < i-k {
			q = q[1:]
		}
		nums[i] += nums[q[0]]
		push(i)
	}
	return nums[n-1]
}

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
