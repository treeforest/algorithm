package leetcode

/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func minDepth(root *TreeNode) int {
	if root == nil {
		return 0
	}
	queue := []*TreeNode{root}
	minHigh := 0
	for len(queue) != 0 {
		minHigh++
		l := len(queue)
		for i := 0; i < l; i++ {
			tmp := queue[i]
			if tmp.Left == nil && tmp.Right == nil {
				return minHigh
			}
			if tmp.Left != nil {
				queue = append(queue, tmp.Left)
			}
			if tmp.Right != nil {
				queue = append(queue, tmp.Right)
			}
		}
		queue = queue[l:]
	}
	return -1
}
