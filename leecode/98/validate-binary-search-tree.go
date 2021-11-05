package leetcode

/*
* Definition for a binary tree node.
* type TreeNode struct {
*     Val int
*     Left *TreeNode
*     Right *TreeNode
* }
 */
func isValidBST(root *TreeNode) bool {
	res := make([]int, 0)
	traverse(root, &res)
	for i := 1; i < len(res); i++ {
		if res[i] <= res[i-1] {
			return false
		}
	}
	return true
}

func traverse(node *TreeNode, res *[]int) {
	if node != nil {
		traverse(node.Left, res)
		*res = append(*res, node.Val)
		traverse(node.Right, res)
	}
}
