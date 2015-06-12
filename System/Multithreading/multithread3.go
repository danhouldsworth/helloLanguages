package main

import "fmt"
import "time"

func main() {
	signals := make(chan string)

	fmt.Println("Parent : launching child go routine.")
	go childCount(signals) // Child process
	fmt.Println("Parent : Waiting on child...")

	msg := <-signals

	fmt.Printf("Parent : Child has terminated with <%s>\n", msg)
}

func childCount(signals chan string) {
	for i := 0; i <= 10; i++ {
		fmt.Printf("Child: count %d\n", i)
		if i > 5 {
			time.Sleep(time.Second)
		}
	}
	signals <- "Finished"
}
