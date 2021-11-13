package leetcode

/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func findBottomLeftValue(root *TreeNode) int {
	queue := []*TreeNode{root}
	var res int
	for len(queue) != 0 {
		res = queue[0].Val // 记录最左边的值
		l := len(queue)
		for i := 0; i < l; i++ {
			n := queue[i]
			if n.Left != nil {
				queue = append(queue, n.Left)
			}
			if n.Right != nil {
				queue = append(queue, n.Right)
			}
		}
		queue = queue[l:]
	}
	return res
}
