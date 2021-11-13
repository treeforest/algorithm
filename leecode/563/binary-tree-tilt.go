package leetcode

/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func findTilt(root *TreeNode) int {
	var res int = 0
	postorder(root, &res)
	return res
}

func postorder(node *TreeNode, res *int) int {
	if node == nil {
		return 0
	}
	l := postorder(node.Left, res)
	r := postorder(node.Right, res)
	*res += abs(l - r)
	return l + r + node.Val
}

func abs(a int) int {
	if a < 0 {
		return -a
	}
	return a
}
