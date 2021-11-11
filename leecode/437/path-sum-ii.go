package leetcode

/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func pathSum(root *TreeNode, targetSum int) int {
	store := make(map[int]int)
	store[0] = 1
	sum := 0
	dfs(root, store, targetSum, 0, &sum)
	return sum
}

func dfs(node *TreeNode, store map[int]int, targetSum, curSum int, sum *int) {
	if node == nil {
		return
	}
	curSum += node.Val // 计算前缀和
	*sum += store[curSum-targetSum]
	store[curSum]++
	dfs(node.Left, store, targetSum, curSum, sum)
	dfs(node.Right, store, targetSum, curSum, sum)
	store[curSum]-- // 回溯
}
