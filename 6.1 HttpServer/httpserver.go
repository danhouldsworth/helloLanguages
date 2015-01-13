// 1. Done
// 2. Done

package main

import (
	"io"
	"net/http"
)

func hello(w http.ResponseWriter, r *http.Request) {
	uri := r.URL.Path[1:]
	io.WriteString(w, "<h1>Go : Hello "+uri+"!</h1>")
}

func main() {
	http.HandleFunc("/", hello)
	http.ListenAndServe(":8888", nil)
}
