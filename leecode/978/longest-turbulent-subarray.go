package leetcode

func maxTurbulenceSize(arr []int) int {
	l, r, n, ans := 0, 0, len(arr), 1
	for r < n-1 {
		if l == r {
			if arr[l] == arr[r+1] {
				l++
			}
			r++
		} else {
			if (arr[r-1] < arr[r] && arr[r] > arr[r+1]) || (arr[r-1] > arr[r] && arr[r] < arr[r+1]) {
				r++
			} else {
				l = r
			}
		}
		ans = max(ans, r-l+1)
	}
	return ans
}

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
