// 1. Done
// 2. Done (for sinlge digits 0-4 !)

package main

import (
	// "fmt"
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
	welcome := []byte("\n\n --- Welcome to Telnet Echo & Double in Go! --- \n\n")
	echo := []byte("Server echo service : ")
	double := []byte("Server doubling service : ")
	messageBuffer := make([]byte, 1024)

	c.Write(welcome)
	for {
		c.Read(messageBuffer)
		if messageBuffer[0] >= 48 && messageBuffer[0] <= 57 {
			messageBuffer[0] -= 48
			messageBuffer[0] *= 2
			messageBuffer[0] += 48
			c.Write(double)
			c.Write(messageBuffer)
		} else {
			c.Write(echo)
			c.Write(messageBuffer)
		}
	}
}
