// 2. Done

package main

import (
	"io"
	"net/http"
)

func hello1(w http.ResponseWriter, r *http.Request) {
	io.WriteString(w, "<h1>Go : Hello, world!</h1>")
}

func hello2(w http.ResponseWriter, r *http.Request) {
	uri := r.URL.Path[7:] // Ignore '/hello/'
	io.WriteString(w, "<h1>Go : Hello "+uri+"!</h1>")
}

func main() {
	http.HandleFunc("/", hello1)
	http.HandleFunc("/hello/", hello2)
	http.ListenAndServe(":8888", nil)
}
