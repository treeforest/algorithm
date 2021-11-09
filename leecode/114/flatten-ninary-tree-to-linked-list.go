package leetcode

/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func flatten(root *TreeNode) {
	list := []*TreeNode{}
	preorder(root, &list)
	cur := root
	for i := 1; i < len(list); i++ {
		list[i].Left = nil
		list[i].Right = nil
		cur.Left = nil
		cur.Right = list[i]
		cur = cur.Right
	}
	return
}

func preorder(node *TreeNode, list *[]*TreeNode) {
	if node == nil {
		return
	}
	*list = append(*list, node)
	preorder(node.Left, list)
	preorder(node.Right, list)
}
