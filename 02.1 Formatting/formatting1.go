// 1. Done

package main

import (
	"fmt"
	s "strings"
)

func main() {
	for i := int64(0); i <= 255; i = i + 1 {
		fmt.Printf(s.Replace(fmt.Sprintf("%3d\t%8b\t%2x\n", i, i, i), " ", "0", -1))
	}
}
