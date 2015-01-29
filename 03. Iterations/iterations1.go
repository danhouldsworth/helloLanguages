// 1. Done

package main

import (
	"fmt"
)

var n = 8

func factorial(x int) int {
	if x == 0 || x == 1 {
		return x
	} else {
		return x * factorial(x-1)
	}
}

func fib(x int) int {
	if x == 0 || x == 1 {
		return x
	} else {
		return fib(x-2) + fib(x-1)
	}
}

func main() {
	for i := 0; i <= n; i++ {
		fmt.Printf("%d! = %d,  \t%dth Fibonacci = %d\n", i, factorial(i), i, fib(i))
	}
}

/*
Learnings : Turns out you can't do nested functions (local scope) !
*/
