// 2. Done (only for 1st digit and if 0-4 !!)

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
	welcome := []byte("\n\n --- Welcome to Telnet Echo & Double in Go! --- \n\n")
	echo := []byte("Server echo service : ")
	double := []byte("Server doubling service : ")

	c.Write(welcome)
	for {
		messageBuffer := make([]byte, 1024)
		c.Read(messageBuffer)
		if messageBuffer[0] >= 48 && messageBuffer[0] <= 57 {
			messageBuffer[0] -= 48
			messageBuffer[0] *= 2
			messageBuffer[0] += 48
			c.Write(append(double, messageBuffer...))
		} else {
			c.Write(append(echo, messageBuffer...))
		}
	}
}
