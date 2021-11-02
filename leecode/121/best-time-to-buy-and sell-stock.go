package leetcode

func maxProfit(prices []int) int {
	n := len(prices)
	if n < 2 {
		return 0
	}
	res := 0
	for i := 1; i < n; i++ {
		res = max(prices[i]-prices[i-1], res)
		prices[i] = min(prices[i-1], prices[i])
	}
	if res < 0 {
		res = 0
	}
	return res
}

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
