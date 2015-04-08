package main

import (
	"fmt"
)

var (
	n       = 8
	counter = 0
)

func main() {
	solve(n, 1, 2, 3)
}

func solve(n, source, tmp, target int) {
	if n == 1 {
		counter++
		move(source, target)
	} else if n > 1 {
		solve(n-1, source, target, tmp)
		solve(1, source, tmp, target)
		solve(n-1, tmp, source, target)
	}
}
func move(source, target int) {
	fmt.Printf("Step %d : Move a ring from tower %d to tower %d\n", counter, source, target)
}
