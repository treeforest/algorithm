package leetcode

/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func pathSum(root *TreeNode, targetSum int) [][]int {
	slice := make([][]int, 0)
	findPath(root, targetSum, &slice, []int(nil))
	return slice
}

func findPath(node *TreeNode, sum int, slice *[][]int, stack []int) {
	if node == nil {
		return
	}
	sum -= node.Val
	stack = append(stack, node.Val)
	if sum == 0 && node.Left == nil && node.Right == nil {
		*slice = append(*slice, append([]int{}, stack...))
		stack = stack[:len(stack)-1]
	}
	findPath(node.Left, sum, slice, stack)
	findPath(node.Right, sum, slice, stack)
}
