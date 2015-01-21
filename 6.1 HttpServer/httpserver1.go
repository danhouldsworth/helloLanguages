// 1. Done

package main

import (
	"io"
	"net/http"
)

func hello(w http.ResponseWriter, r *http.Request) {
	io.WriteString(w, "<h1>Go : Hello, world!</h1>")
}

func main() {
	http.HandleFunc("/", hello)
	http.ListenAndServe(":8887", nil)
}
