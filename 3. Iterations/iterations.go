package main

import (
	"fmt"
	"math"
)

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

func leibnizTerm(n int) float64 {
	return math.Pow(-1, float64(n)) / float64(n+n+1)
}

func piDigit(dps int) int {
	if dps == 0 {
		return 3
	}
	for n, sum := 0, 0.0; true; n++ {
		sum += leibnizTerm(n)
	}
}

func displayPiDigit(x int) {
	fmt.Printf("%d", piDigit(x))
}

func main() {

	n := 7

	for i := 0; i <= n; i++ {
		fmt.Printf("%d! = %d,  \t%dth Fibonacci = %d,  \tPI = ", i, factorial(i), i, fib(i))
		for j := 0; j <= i; j++ {
			displayPiDigit(j)
		}
		fmt.Println()
	}
}

/*
Learnings : Turns out you can't do nested functions (local scope) !
*/
