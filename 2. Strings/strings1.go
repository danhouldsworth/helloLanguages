// 1. Done
/*
Learnings for Go:
- String elements, while intuitively chars, are not 0-255 ints but unicode characters
- Strings are imutable, so need to think through memory efficiency when manipulating

House-keeping :
- Sublime 3 + GoSublime auto calls 'go fmt' on each save
- Also displays errors with GsLint
*/

package main

import (
	"fmt"
	s "strings" // note how we can import to an alias
)

func main() {
	greeting := "The quick brown 狐 jumped over the lazy 犬"
	// greeting := "Hello, world!"

	var backwardsMsg string

	for _, letter := range greeting { // <for...range> iterates over the elements of a data structure, in this case unicode points of a string
		backwardsMsg = string(letter) + backwardsMsg // cast the unicode letter to string
	}
	fmt.Println(backwardsMsg)
	fmt.Println(s.ToUpper(greeting) + " " + s.ToLower(greeting))
}
