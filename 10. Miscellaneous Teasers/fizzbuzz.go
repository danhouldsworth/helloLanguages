package main

import (
	"fmt"
)

var (
	fizzbuzzed bool
)

func main() {

	for i := 1; i <= 100; i++ {
		fizzbuzzed = false
		if i%3 == 0 {
			fmt.Printf("Fizz")
			fizzbuzzed = true
		}
		if i%5 == 0 {
			fmt.Printf("Buzz")
			fizzbuzzed = true
		}
		if fizzbuzzed {
			fmt.Println()
		} else {
			fmt.Println(i)
		}
	}
}
