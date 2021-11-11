package leetcode

/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func countNodes(root *TreeNode) int {
	count := 0
	preorder(root, &count)
	return count
}

func preorder(node *TreeNode, count *int) {
	if node != nil {
		*count++
		preorder(node.Left, count)
		preorder(node.Right, count)
	}
}
