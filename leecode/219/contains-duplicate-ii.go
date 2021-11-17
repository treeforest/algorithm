package leetcode

func containsNearbyDuplicate(nums []int, k int) bool {
	if k == 0 || len(nums) <= 1 {
		return false
	}
	l, r, n, store := 0, 0, len(nums), make(map[int]struct{})
	for r < n {
		if r-l > k {
			// 超出范围k，删除左指针指向的元素，并且左指针向右移
			delete(store, nums[l])
			l++
		}
		if _, ok := store[nums[r]]; ok {
			// 记录有对应的整数，而这两个整数所对应索引差的绝对值肯定是在范围k之内的
			return true
		}
		store[nums[r]] = struct{}{} // 标记范围k内存在的整数
		r++
	}
	return false
}
