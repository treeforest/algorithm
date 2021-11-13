package leetcode

/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func getMinimumDifference(root *TreeNode) int {
	res, pre := 100001, -1
	inorder(root, &res, &pre)
	return res
}

func inorder(node *TreeNode, res, pre *int) {
	if node == nil {
		return
	}
	inorder(node.Left, res, pre)
	if *pre != -1 {
		*res = min(*res, abs(node.Val-*pre))
	}
	*pre = node.Val
	inorder(node.Right, res, pre)
}

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}

func abs(a int) int {
	if a < 0 {
		return a * (-1)
	}
	return a
}
