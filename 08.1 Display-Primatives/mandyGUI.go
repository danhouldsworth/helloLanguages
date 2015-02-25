package main

import (
	"fmt"
	"github.com/danhouldsworth/gui"
)

var (
	screenSize = 1 << 11 // Stick to a power of 2, makes box division safer.
	maxDwell   = 100     //
)

func main() {
	gui.Screen(screenSize)
	gui.Launch()

	left, top := 0, 0
	right, bottom := screenSize-1, screenSize-1
	go mandy(left, right, top, bottom)

	fmt.Scanln() // Press Enter to abort
}

func mandy(left, right, top, bottom int) {
	deltaX := 1
	deltaY := 0
	colourBlock := true
	firstColour := isMandy(mapToArgand(left, top)) // This wastes a pixel calc

	for i, j, edge := left, top, 0; edge < 4; i, j = i+deltaX, j+deltaY {
		dwell := isMandy(mapToArgand(i, j))
		if colourBlock == true && dwell != firstColour {
			colourBlock = false
			// Initiate recurcise split immediately in case of idle CPUs
			if top < bottom-2 && left < right-2 {
				midleft := left + (right-left)/2
				midtop := top + (bottom-top)/2
				go mandy(left+1, midleft, top+1, midtop)         // TL
				go mandy(left+1, midleft, midtop+1, bottom-1)    // BL
				go mandy(1+midleft, right-1, midtop+1, bottom-1) // BR
				go mandy(1+midleft, right-1, top+1, midtop)      // TR
			}

		}
		gui.Plot(i, j, byte(dwell%64), byte(dwell%16), byte(dwell%2), 255-byte(dwell%256))
		if deltaX > 0 && i == right {
			edge++
			deltaX--
			deltaY++
		} else if deltaY > 0 && j == bottom {
			edge++
			deltaX--
			deltaY--
		} else if deltaX < 0 && i == left {
			edge++
			deltaX++
			deltaY--
		} else if deltaY < 0 && j == top {
			edge++
			deltaX++
			deltaY++
		}
	}
	if colourBlock == true {
		gui.FillRect(left, top, right, bottom, byte(firstColour%64), byte(firstColour%16), byte(firstColour%2), 255-byte(firstColour%256))
	}
}

func isMandy(c complex128) (dwell int) {
	dwell = 0
	for z := c; real(z)*real(z)+imag(z)*imag(z) < 4; z = z*z + c {
		dwell++
		if dwell >= maxDwell {
			return
		}
	}
	return
}

func mapToArgand(x, y int) complex128 {
	min, max := complex(-2, -1.5), complex(1, 1.5)
	return min + complex(ratio(x, screenSize)*real(max-min), ratio(y, screenSize)*imag(max-min))
}

func ratio(a, b int) float64 {
	return float64(a) / float64(b)
}
