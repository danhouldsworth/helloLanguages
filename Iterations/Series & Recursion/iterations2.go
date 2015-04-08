// 2. Done
// Bonus. Pretty slow so far, 2-3x slower than js :-(

package main

import (
	"fmt"
	"math"
)

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
	fmt.Printf("PI correct to %d decimal places = %g\n", n, pi(n))
}
