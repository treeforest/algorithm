package leetcode

/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func hasPathSum(root *TreeNode, targetSum int) bool {
	if root == nil {
		return false
	}
	if root.Left == nil && root.Right == nil && root.Val == targetSum {
		return true
	}
	if root.Left != nil {
		root.Left.Val += root.Val
	}
	if root.Right != nil {
		root.Right.Val += root.Val
	}
	return hasPathSum(root.Left, targetSum) || hasPathSum(root.Right, targetSum)
}
