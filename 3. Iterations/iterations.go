// 1. Done
// 2. Done
// 3. Done
// 4. Bonus. Pretty slow so far, 2-3x slower than js :-(

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

func truncate(x float64, dp int) float64 {
	return math.Floor(math.Pow(10, float64(dp))*x) / math.Pow(10, float64(dp))
}

func pi(dp int) float64 {
	for n, lastSum, sum := 0, 0.0, 0.0; ; n++ {
		lastSum = truncate(sum, dp) // Truncating now saves me 2 more later.
		sum += 4 * leibnizTerm(n)
		if truncate(sum, dp) == lastSum {
			return lastSum
		}
	}
}

func main() {
	n := 7

	for i := 0; i <= n; i++ {
		fmt.Printf("%d! = %d,  \t%dth Fibonacci = %d,  \tPI = %g\n", i, factorial(i), i, fib(i), pi(i))
	}
}

/*
Learnings : Turns out you can't do nested functions (local scope) !
*/
