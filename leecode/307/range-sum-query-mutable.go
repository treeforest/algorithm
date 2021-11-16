package leetcode

type NumArray struct {
	n    int
	tr   []int
	nums []int
}

func Constructor(nums []int) NumArray {
	n := len(nums)
	tr := make([]int, n+1, n+1)
	arr := NumArray{n: n, nums: nums, tr: tr}
	for i := 1; i <= n; i++ {
		arr.add(i, nums[i-1])
	}
	return arr
}

func (this *NumArray) Update(index int, val int) {
	oldVal := this.nums[index]
	if oldVal == val {
		return
	}
	this.nums[index] = val
	this.add(index+1, val-oldVal)
}

func (this *NumArray) SumRange(left int, right int) int {
	return this.sum(right+1) - this.sum(left)
}

func (this *NumArray) add(index int, val int) {
	for i := index; i <= this.n; i += lowbit(i) {
		this.tr[i] += val
	}
}

func (this *NumArray) sum(index int) int {
	ans := 0
	for i := index; i >= 1; i -= lowbit(i) {
		ans += this.tr[i]
	}
	return ans
}

func lowbit(v int) int {
	return v & (-v)
}

/**
 * Your NumArray object will be instantiated and called as such:
 * obj := Constructor(nums);
 * obj.Update(index,val);
 * param_2 := obj.SumRange(left,right);
 */
