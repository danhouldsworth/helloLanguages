// 1. Done [area=1.507 in 12m35s at steps=10k, dwell=10k]

/*
Learning. Fell into some serious traps with division of integer types within a larger float calc. Intuitly reads as a ratio, but returns 0 with no error
Added ratio function to get around
Also note the complex types and methods. Easy now, but this took me some time as wasn't intuitive
*/

package main

import (
	"fmt"
)

var (
	// Viewport
	min, max = complex(-2, -1.5), complex(1, 1.5) // Defaults to complex128

	// Precision and depth
	steps    = 1000
	maxDwell = 100
)

func main() {

	area := 0

	for i := 0; i <= steps; i++ {
		for j := 0; j <= steps; j++ {
			if isMandy(mapToArgand(i, j)) {
				area++
			}
		}
	}

	setArea := ratio(area, (steps * steps))  // % of pixels covered
	setArea *= real(max-min) * imag(max-min) // * total argand area

	fmt.Printf("\nArea of mandlebrot set = %f\n", setArea)
}

func isMandy(c complex128) bool {
	dwell := 0
	for z := c; real(z)*real(z)+imag(z)*imag(z) < 4; z = z*z + c {
		dwell++
		if dwell >= maxDwell {
			return true
		}
	}
	return false
}

func mapToArgand(x, y int) complex128 {
	return min + complex(ratio(x, steps)*real(max-min), ratio(y, steps)*imag(max-min))
}

func ratio(a, b int) float64 {
	return float64(a) / float64(b)
}
