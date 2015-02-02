// 1. Done

package main

import (
	"fmt"
	"os"
	"strconv"
)

var ()

func main() {
	name := os.Args[1]                            // Note [0] would be filename
	age, _ := strconv.ParseInt(os.Args[2], 10, 0) // No error handling
	fmt.Printf("Go CLI arg name : %s, and age : %d\n", name, 12*age)
}
