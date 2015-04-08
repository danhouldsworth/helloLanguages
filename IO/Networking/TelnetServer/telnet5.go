// 1. Done

package main

import (
	"fmt"
	"net"
)

func main() {
	listener, _ := net.Listen("tcp", ":4000")
	conn, _ := listener.Accept()

	header := []byte("HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=utf-8\r\nCookie: dan=cool\r\n\r\n")
	response := []byte("<h1>Go Single Use Telnet/HTTP : Hello, world!</h1>\r\n")

	messageBuffer := make([]byte, 1024)
	conn.Read(messageBuffer)
	fmt.Printf("\nRecieved :\n-->%s<--\n", string(messageBuffer))

	conn.Write(header)
	conn.Write(response)

	conn.Close()
}
