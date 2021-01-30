package main

import (
	"container/list"
	"fmt"
)

var (
	mp map[int]*list.List = make(map[int]*list.List, 100)
	book [100]int
	maxDepth int = -1
)

func main() {
	for k, _ := range mp {
		mp[k] = list.New()
	}
	var n, m, node, k, c int
	fmt.Scanf("%d%d", &n, &m)
	for i := 0; i < m; i++ {
		fmt.Scanf("%d%d", &node, &k)
		for j := 0; j < k; j++ {
			fmt.Scanf("%d", &c)
			mp[node].PushBack(c)
		}
	}
}
