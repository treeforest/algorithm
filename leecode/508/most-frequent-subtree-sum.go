package leetcode

/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func findFrequentTreeSum(root *TreeNode) []int {
	store := make(map[int]int)
	maxNum := 0
	postorder(root, store, &maxNum)
	res := make([]int, 0)
	for k, v := range store {
		if v == maxNum {
			res = append(res, k)
		}
	}
	return res
}

func postorder(node *TreeNode, store map[int]int, maxNum *int) int {
	if node == nil {
		return 0
	}

	left := postorder(node.Left, store, maxNum)
	right := postorder(node.Right, store, maxNum)

	val := node.Val + left + right
	store[val]++
	*maxNum = max(store[val], *maxNum)
	return val
}

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
