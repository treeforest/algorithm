package leetcode

/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func rightSideView(root *TreeNode) []int {
	if root == nil {
		return []int{}
	}
	queue := []*TreeNode{root}
	res := make([]int, 0)
	for len(queue) != 0 {
		l := len(queue)
		for i := 0; i < l; i++ {
			tmp := queue[i]
			if tmp.Left != nil {
				queue = append(queue, tmp.Left)
			}
			if tmp.Right != nil {
				queue = append(queue, tmp.Right)
			}
		}
		res = append(res, queue[l-1].Val)
		queue = queue[l:]
	}
	return res
}
