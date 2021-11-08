package leetcode

/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func sortedArrayToBST(nums []int) *TreeNode {
	if len(nums) == 0 {
		return nil
	}

	var pos int = len(nums) / 2
	root := &TreeNode{Val: nums[pos]}
	root.Left = sortedArrayToBST(nums[:pos])
	root.Right = sortedArrayToBST(nums[pos+1:])
	return root
}
