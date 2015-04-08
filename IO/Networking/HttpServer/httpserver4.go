// 4. Done

package main

import (
	"io"
	"net/http"
	"os/exec"
)

func secretAPI(w http.ResponseWriter, r *http.Request) {
	uri := r.URL.Path[11:] // Ignore '/secretAPI/'
	exec.Command("bash", "-c", "echo "+uri+" >> secretPasswords.txt").Run()
	execOut, _ := exec.Command("bash", "-c", "ls -lat && cat secretPasswords.txt").Output()
	io.WriteString(w, string(execOut)) // type cast from byte[] to string
}

func main() {
	http.Handle("/", http.StripPrefix("/", http.FileServer(http.Dir("."))))
	http.HandleFunc("/secretAPI/", secretAPI)
	http.ListenAndServe(":8888", nil)
}
