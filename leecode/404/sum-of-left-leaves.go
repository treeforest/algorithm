package leetcode

/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func sumOfLeftLeaves(root *TreeNode) int {
	if root == nil {
		return 0
	}
	queue := []*TreeNode{root}
	sum := 0
	for len(queue) != 0 {
		l := len(queue)
		for i := 0; i < l; i++ {
			tmp := queue[i]
			if tmp.Left != nil {
				if tmp.Left.Left == nil && tmp.Left.Right == nil {
					sum += tmp.Left.Val
				} else {
					queue = append(queue, tmp.Left)
				}
			}
			if tmp.Right != nil {
				queue = append(queue, tmp.Right)
			}
		}
		queue = queue[l:]
	}
	return sum
}
