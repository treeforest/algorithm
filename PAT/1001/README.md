# 1001 A+B Format

## Problem

https://pintia.cn/problem-sets/994805342720868352/problems/994805528788582400

## Code
```go
package main

import "fmt"

func main() {
	var a, b, sum, l int
	fmt.Scanf("%d %d", &a, &b)
	sum = a + b
	s := fmt.Sprintf("%d", sum)

	if sum < 0 {
		s = s[1:]
	}

	l = len(s)
	for i := 3; l - i > 0; i = i + 3 {
		s = s[:l-i] + "," + s[l-i:]
	}

	if sum < 0 {
		s = "-" + s
	}

	fmt.Print(s)
}
```