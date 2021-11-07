package leetcode

/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func isSymmetric(root *TreeNode) bool {
	return SymmetricTree(root.Left, root.Right)
}

func SymmetricTree(l, r *TreeNode) bool {
	if l == nil && r == nil {
		return true
	} else if (l == nil && r != nil) || (l != nil && r == nil) {
		return false
	}
	if l.Val != r.Val {
		return false
	}
	if !SymmetricTree(l.Left, r.Right) || !SymmetricTree(l.Right, r.Left) {
		return false
	}
	return true
}
