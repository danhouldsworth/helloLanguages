// 1. Done [area=1.507 in 12m35s at steps=10000, dwell=10000]

/* Learnings :
1. 	I fell into some serious traps with division of integer types within a larger float calc.
	Intuitly reads as a ratio, but returns 0 with no error.
2. 	Also note usage of complex types and methods.
	Easy now, but this took me some time as wasn't intuitive. I do like being able to to z = z*z + c
3. 	Real shame that it takes 4 lines...
        dwell++
        if dwell >= maxDwell {
            return true
        }
	to write what would be 1 equally clear line in C...
        if (dwell++ >= maxDwell) return true
4. 	Note that vars declared in the (only loop statement) 'for' are local to that loop and not available once finished
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
	maxDwell = 1000
	// Tallies
	area    = 0
	setArea float64
)

func main() {
	for i := 0; i <= steps; i++ {
		for j := 0; j <= steps; j++ {
			if isMandy(mapToArgand(i, j)) {
				area++
			}
		}
	}
	setArea = ratio(area, (steps * steps))   // % of pixels covered
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
