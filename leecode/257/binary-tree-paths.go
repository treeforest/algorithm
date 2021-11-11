package leetcode

import "fmt"

/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func binaryTreePaths(root *TreeNode) []string {
	if root.Left == nil && root.Right == nil {
		return []string{fmt.Sprintf("%d", root.Val)}
	}
	paths := make([]string, 0)
	preorder(root.Left, fmt.Sprintf("%d", root.Val), &paths)
	preorder(root.Right, fmt.Sprintf("%d", root.Val), &paths)
	return paths
}

func preorder(node *TreeNode, path string, paths *[]string) {
	if node != nil {
		path = fmt.Sprintf("%s->%d", path, node.Val)
		if node.Left == nil && node.Right == nil {
			*paths = append(*paths, path)
			return
		}
		preorder(node.Left, path, paths)
		preorder(node.Right, path, paths)
	}
}
