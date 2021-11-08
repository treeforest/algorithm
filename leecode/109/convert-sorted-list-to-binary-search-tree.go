package leetcode

/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func sortedListToBST(head *ListNode) *TreeNode {
	if head == nil {
		return nil
	}

	p := head
	n := 0 // 记录共有多少个元素
	for p != nil {
		n++
		p = p.Next
	}

	pos := n / 2 // 中间元素
	var pre *ListNode = nil
	q := head
	for i := 0; i < pos; i++ {
		pre = q
		q = q.Next
	}

	root := &TreeNode{Val: q.Val}
	if pre != nil {
		pre.Next = nil
		root.Left = sortedListToBST(head)
	} else {
		root.Left = nil
	}
	root.Right = sortedListToBST(q.Next)
	return root
}
