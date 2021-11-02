package leetcode

/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func maxPathSum(root *TreeNode) int {
	if root == nil {
		return 0
	}
	maxSum := -10001
	_ = getPathSum(root, &maxSum)
	return maxSum
}

func getPathSum(node *TreeNode, maxSum *int) int {
	if node == nil {
		return -10001
	}

	left := getPathSum(node.Left, maxSum)
	right := getPathSum(node.Right, maxSum)

	curMax := max(max(node.Val+left, node.Val+right), node.Val)
	*maxSum = max(*maxSum, max(curMax, node.Val+left+right))
	return curMax
}

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
