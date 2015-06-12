package main

import "fmt"

func main() {
	go count("Child")
	count("Parent")

	// -- Parent doesn't wait for Child to finish executing!
	var input string
	fmt.Scanln(&input)
	fmt.Println("done")
}

func count(owner string) {
	for i := 0; i <= 10; i++ {
		fmt.Printf("%s counts : %d\n", owner, i)
	}
}
