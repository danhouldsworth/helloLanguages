package main

import (
	"fmt"
)

func main() {
	message := "Hello"         // Statically typed but inferred from declaration type.
	message += ", " + "world!" // Concatenation
	fmt.Println(message)       // (I think) all exposed methods of imported module are capitalised
}
