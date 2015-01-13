// 1. Done
// 2. Done
// 3. Done
// Bonus. Done

package main

import (
	"io"
	"net/http"
	"os/exec"
)

func hello(w http.ResponseWriter, r *http.Request) {
	uri := r.URL.Path[7:] // Ignore '/hello/'
	io.WriteString(w, "<h1>Go : Hello "+uri+"!</h1>")
}

func secretAPI(w http.ResponseWriter, r *http.Request) {
	execOut, _ := exec.Command("bash", "-c", "ls -lat").Output()
	io.WriteString(w, string(execOut)) // type cast from byte[] to string
}

func main() {
	http.HandleFunc("/hello/", hello)
	http.Handle("/", http.StripPrefix("/", http.FileServer(http.Dir("."))))
	http.HandleFunc("/secretAPI/", secretAPI)
	http.ListenAndServe(":8888", nil)
}
