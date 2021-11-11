package leetcode

/**
 * Definition for a Node.
 * type Node struct {
 *     Val int
 *     Children []*Node
 * }
 */

func levelOrder(root *Node) [][]int {
	if root == nil {
		return [][]int{}
	}
	queue := []*Node{root}
	res := make([][]int, 0)
	for len(queue) != 0 {
		l := len(queue)
		level := make([]int, 0)
		for i := 0; i < l; i++ {
			level = append(level, queue[i].Val)
			for _, child := range queue[i].Children {
				queue = append(queue, child)
			}
		}
		res = append(res, level)
		queue = queue[l:]
	}
	return res
}
