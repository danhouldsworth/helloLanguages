// 2. Done [Clearly must set valid GOPATH / Go workspace]
package main

import (
	"fmt"
	lib "github.com/danhouldsworth/hello/library"
	s "strings"
)

func main() {
	fmt.Printf("Go package name = %s, and age = %d\n", s.ToUpper(lib.Name), 12*lib.Age)
}
