package leetcode

/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func zigzagLevelOrder(root *TreeNode) [][]int {
	if root == nil {
		return [][]int{}
	}
	queue := []*TreeNode{root}
	res := make([][]int, 0)
	leftToRight := true
	for len(queue) != 0 {
		n := len(queue)
		tmp := make([]int, 0, n)
		for i := 0; i < n; i++ {
			node := queue[i]
			tmp = append(tmp, node.Val)
			if node.Left != nil {
				queue = append(queue, node.Left)
			}
			if node.Right != nil {
				queue = append(queue, node.Right)
			}
		}
		if !leftToRight {
			// 反序
			l, r := 0, n-1
			for l < r {
				tmp[l], tmp[r] = tmp[r], tmp[l]
				l++
				r--
			}
		}
		leftToRight = !leftToRight
		res = append(res, tmp)
		queue = queue[n:]
	}
	return res
}
