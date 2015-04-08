// 1. Done

package main

import (
	"net"
)

func main() {
	listener, _ := net.Listen("tcp", ":4000")
	for {
		conn, _ := listener.Accept()
		go handleConnection(conn)
	}
}

func handleConnection(c net.Conn) {
	welcome := []byte("\n\n --- Welcome to Telnet Echo in Go! --- \n\n")
	echo := []byte("Server echo service : ")

	c.Write(welcome)
	for {
		messageBuffer := make([]byte, 1024)
		c.Read(messageBuffer)
		response := append(echo, messageBuffer...) // Note : concatenation of variadic function
		c.Write(response)
	}
}
