package leetcode

/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func postorderTraversal(root *TreeNode) []int {
	res := []int{}
	postorder(root, &res)
	return res
}

func postorder(node *TreeNode, res *[]int) {
	if node != nil {
		postorder(node.Left, res)
		postorder(node.Right, res)
		*res = append(*res, node.Val)
	}
}
