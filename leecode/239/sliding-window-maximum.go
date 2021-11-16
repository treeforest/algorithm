package leetcode

func maxSlidingWindow(nums []int, k int) []int {
	q := make([]int, 0)
	push := func(i int) {
		for len(q) > 0 && nums[i] > nums[q[len(q)-1]] {
			q = q[:len(q)-1]
		}
		q = append(q, i)
	}
	for i := 0; i < k; i++ {
		push(i)
	}
	ans := make([]int, 0)
	ans = append(ans, nums[q[0]])
	for i := k; i < len(nums); i++ {
		push(i)
		for q[0] <= i-k {
			q = q[1:]
		}
		ans = append(ans, nums[q[0]])
	}
	return ans
}
