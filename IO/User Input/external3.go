package main

import (
	"encoding/json"
	"fmt"
	"os"
)

func main() {

	type message struct {
		name string
		age  string
	}

	file, _ := os.Open("Library/config.json") // Pass
	dec := json.NewDecoder(file)
	var m message
	dec.Decode(&m)
	fmt.Printf("Go JSON name : %s, and age = %s\n", m.name, m.age)
}
