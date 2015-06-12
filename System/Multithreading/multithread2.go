package main

import "fmt"
import "time"

func main() {
	go count("Child")
	count("Parent")
}

func count(owner string) {
	for i := 0; i <= 10; i++ {
		fmt.Printf("%s counts : %d\n", owner, i)
		if i == 5 && owner == "Parent" {
			time.Sleep(time.Second)
		}
	}
}
