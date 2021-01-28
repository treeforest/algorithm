package main

import "fmt"

func main() {
	var a, b, sum int
	fmt.Scanf("%d %d", &a, &b)
	sum = a + b
	s := fmt.Sprintf("%d", sum)
	if sum < 0 {
		s = s[1:]
	}

	var s2 string = ""
	var i int = 0
	var j int = 0

	for i = len(s) - 1; i >= 0; i-- {
		if j%3 == 0 && j > 0{
			s2 = "," + s2
		}
		s2 = string(s[i]) + s2
		j++
	}

	if sum < 0 {
		s2 = "-" + s2
	}

	fmt.Print(s2)
}