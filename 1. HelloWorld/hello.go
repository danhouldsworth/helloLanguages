// 1. Done
// Bonus. Done

package main

import (
	f "fmt"
)

func main() {
	message := "Hello"         // Statically typed but inferred from declaration type.
	message += ", " + "world!" // Concatenation same as javascript
	f.Println(message)         // (I think) all exposed methods of imported module are capitalised
}
