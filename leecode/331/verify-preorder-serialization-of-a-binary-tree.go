package leetcode

import "strings"

func isValidSerialization(preorder string) bool {
	input := strings.Split(preorder, ",")
	if !PreOrder(&input) {
		return false
	}
	if len(input) != 0 {
		// 示例说明情况: 3,#,#,1
		return false
	}
	return true
}

func PreOrder(input *[]string) bool {
	if len(*input) == 0 {
		// 需要元素的时候，却没有元素的情况
		return false
	}
	item := (*input)[0]
	*input = (*input)[1:]
	if item == "#" {
		return true
	}
	return PreOrder(input) && PreOrder(input)
}
