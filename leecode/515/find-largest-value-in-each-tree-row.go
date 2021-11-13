package leetcode

/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func largestValues(root *TreeNode) []int {
	if root == nil {
		return []int{}
	}
	queue := []*TreeNode{root}
	res := make([]int, 0)
	for len(queue) != 0 {
		l := len(queue)
		maxVal := queue[0].Val
		for i := 0; i < l; i++ {
			node := queue[i]
			maxVal = max(maxVal, node.Val)
			if node.Left != nil {
				queue = append(queue, node.Left)
			}
			if node.Right != nil {
				queue = append(queue, node.Right)
			}
		}
		res = append(res, maxVal)
		queue = queue[l:]
	}
	return res
}

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
