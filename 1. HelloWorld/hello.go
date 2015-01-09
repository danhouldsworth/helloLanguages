package main

import (
	f "fmt"
)

func main() {
	var message string = "Hello" // Statically typed but inferred from declaration type.
	message += ", " + "world!"   // Concatenation
	f.Println(message)           // (I think) all exposed methods of imported module are capitalised
}
