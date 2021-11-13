package leetcode

/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func convertBST(root *TreeNode) *TreeNode {
	pre := -10001
	inorder(root, &pre)
	return root
}

func inorder(node *TreeNode, pre *int) {
	if node == nil {
		return
	}
	inorder(node.Right, pre)
	if *pre != -10001 {
		node.Val += *pre
	}
	*pre = node.Val
	inorder(node.Left, pre)
}
