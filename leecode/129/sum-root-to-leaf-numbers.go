package leetcode

/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func sumNumbers(root *TreeNode) int {
	sum := 0
	dfs(root, 0, &sum)
	return sum
}

func dfs(node *TreeNode, n int, sum *int) {
	if node == nil {
		return
	}
	n = n*10 + node.Val
	if node.Left == nil && node.Right == nil {
		*sum += n
		return
	}
	dfs(node.Left, n, sum)
	dfs(node.Right, n, sum)
}
