package leetcode

/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */

func diameterOfBinaryTree(root *TreeNode) int {
	var maxLen int = 0
	depth(root, &maxLen)
	return maxLen
}

func depth(node *TreeNode, maxLen *int) int {
	if node == nil {
		return 0
	}
	left := depth(node.Left, maxLen)
	right := depth(node.Right, maxLen)
	*maxLen = max(*maxLen, left+right)
	return max(left, right) + 1
}

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
