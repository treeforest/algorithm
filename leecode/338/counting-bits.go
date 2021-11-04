package leetcode

func countBits(n int) []int {
	bits := make([]int, n+1)
	for i := 1; i <= n; i++ {
		// bits[i&(i-1)] 除高位外所占1的个数
		bits[i] = bits[i&(i-1)] + 1
	}
	return bits
}
