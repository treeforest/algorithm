package leetcode

/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func kthSmallest(root *TreeNode, k int) int {
	stack := []*TreeNode{root}
	p := root.Left
	for p != nil {
		stack = append(stack, p)
		p = p.Left
	}
	for k > 1 {
		p = stack[len(stack)-1]
		stack = stack[:len(stack)-1]
		k--
		if p.Right != nil {
			stack = append(stack, p.Right)
			p = p.Right.Left
			for p != nil {
				stack = append(stack, p)
				p = p.Left
			}
		}
	}
	return stack[len(stack)-1].Val
}
