package leetcode

/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func rob(root *TreeNode) int {
	f := make(map[*TreeNode]int, 0)
	g := make(map[*TreeNode]int, 0)
	dfs(root, &f, &g)
	return max(f[root], g[root])
}

func dfs(node *TreeNode, f, g *map[*TreeNode]int) {
	if node == nil {
		return
	}
	dfs(node.Left, f, g)
	dfs(node.Right, f, g)
	(*f)[node] = node.Val + (*g)[node.Left] + (*g)[node.Right]
	(*g)[node] = max((*f)[node.Left], (*g)[node.Left]) + max((*f)[node.Right], (*g)[node.Right])
}

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
