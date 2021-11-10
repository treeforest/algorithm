package leetcode

/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
type BSTIterator struct {
	stack []*TreeNode
}

func Constructor(root *TreeNode) BSTIterator {
	stack := []*TreeNode{root}
	tmp := root.Left
	for tmp != nil {
		stack = append(stack, tmp)
		tmp = tmp.Left
	}
	return BSTIterator{stack: stack}
}

func (this *BSTIterator) Next() int {
	l := len(this.stack)
	tmp := this.stack[l-1]
	nextVal := tmp.Val
	this.stack = this.stack[:l-1]
	if tmp.Right != nil {
		this.stack = append(this.stack, tmp.Right)
		tmp = tmp.Right.Left
		for tmp != nil {
			this.stack = append(this.stack, tmp)
			tmp = tmp.Left
		}
	}
	return nextVal
}

func (this *BSTIterator) HasNext() bool {
	return len(this.stack) > 0
}

/**
 * Your BSTIterator object will be instantiated and called as such:
 * obj := Constructor(root);
 * param_1 := obj.Next();
 * param_2 := obj.HasNext();
 */
