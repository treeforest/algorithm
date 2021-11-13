package leetcode

/**
 * Definition for a Node.
 * type Node struct {
 *     Val int
 *     Children []*Node
 * }
 */

func preorder(root *Node) []int {
	res := []int{}
	preorderHelper(root, &res)
	return res
}

func preorderHelper(node *Node, res *[]int) {
	if node != nil {
		*res = append(*res, node.Val)
		for _, c := range node.Children {
			preorderHelper(c, res)
		}
	}
}
