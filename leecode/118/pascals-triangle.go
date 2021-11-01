package leetcode

func generate(numRows int) [][]int {
	res := make([][]int, numRows)
	for i := 0; i < numRows; i++ {
		res[i] = make([]int, i+1)
	}
	res[0][0] = 1
	for i := 1; i < numRows; i++ {
		res[i][0] = res[i-1][0]
		for j := 1; j <= i; j++ {
			if i == j {
				res[i][j] = res[i-1][j-1]
				continue
			}
			res[i][j] = res[i-1][j-1] + res[i-1][j]
		}
	}
	return res
}
