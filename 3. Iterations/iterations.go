// 1. Done
// 2. Done
// 3. Need to think through extracting digits from float64
// 4. Bonus. Todo.

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

func piDigit(dps int) (n int, sum float64) {
	if dps == 0 {
		sum = 3.0
		return
	}
	for n, sum = 0, 0.0; true; n++ {
		sum += leibnizTerm(n)
		return // testing
	}
	return
}

func displayPiDigit(x int) {
	_, digit := piDigit(x) // Ignore the first of the two values
	fmt.Printf("%f", digit)
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
