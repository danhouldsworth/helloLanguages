// 2. Done (Bonus Q is failing on string casting of unicode Chinese)

package main

import (
	"fmt"
)

func main() {
	greeting := "The quick brown 狐 jumped over the lazy 犬"
	// greeting := "Hello, world!"

	for index, _ := range greeting {
		for subCount := 0; subCount <= index; subCount++ {
			fmt.Print(string(greeting[subCount])) // string casting is mixing up chinese unicode
		}
		fmt.Println()
	}
}
