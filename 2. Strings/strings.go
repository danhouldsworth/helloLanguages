// 1. Done
// 2. Done
// 3. Done
// Bonus. Failing on string casting of unicode chinese

package main

import (
	"fmt"
	s "strings" // note how we can import to an alias
)

func main() {
	greeting := "The quick brown 狐 jumped over the lazy 犬"
	// greeting := "Hello, world!"

	// 1. Backwards
	var backwardsMsg string

	// <for...range> iterates over the elements of a data structure, in this case unicode points of a string
	for _, letter := range greeting {
		backwardsMsg = string(letter) + backwardsMsg // cast the unicode letter to string
	}
	fmt.Println(backwardsMsg)

	// 2. Upper & lower case conversion
	fmt.Println(s.ToUpper(greeting) + " " + s.ToLower(greeting))

	// 3. Substrings
	for index, _ := range greeting {
		for subCount := 0; subCount <= index; subCount++ { // Here for..loop is like JS or C
			fmt.Print(string(greeting[subCount])) // string casting is mixing up chinese unicode
		}
		fmt.Println()
	}
}

/*
Learnings for Go:
- String elements, while intuitively chars, are not 0-255 ints but unicode characters
- Strings are imutable, so need to think through memory efficiency when manipulating
*/

/* House-keeping :
- Sublime 3 + GoSublime auto calls 'go fmt' on each save
- Also displays errors with GsLint
*/
