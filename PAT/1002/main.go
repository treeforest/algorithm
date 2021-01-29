package main

import "fmt"

func main() {
	s := make([]float32, 1001)
	var k, i int
	var num float32
	fmt.Scanf("%d", &k)
	for j := 0; j < k; j++ {
		fmt.Scanf("%d%f", &i, &num)
		s[i] += num
	}
	fmt.Scanf("%d", &k)
	for j := 0; j < k; j++ {
		fmt.Scanf("%d%f", &i, &num)
		s[i] += num
	}
	var cnt int = 0
	for j := 1000; j >= 0; j-- {
		if s[j] != 0.0 {
			cnt++
		}
	}
	fmt.Print(cnt)
	for j := 1000; j >= 0; j-- {
		if s[j] != 0.0 {
			fmt.Printf(" %d %.1f", j, s[j])
		}
	}
}