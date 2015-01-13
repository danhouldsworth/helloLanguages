// 1. Done
// 2. Done (for sinlge digits 0-4 !)
// 3. Done

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
	bye := []byte("\n\n --- Bye for now!! --- \n\n")

	c.Write(welcome)
	for {
		messageBuffer := make([]byte, 1024)
		c.Read(messageBuffer)
		if messageBuffer[0] >= 48 && messageBuffer[0] <= 57 {
			messageBuffer[0] -= 48
			messageBuffer[0] *= 2
			messageBuffer[0] += 48
			c.Write(double)
			c.Write(messageBuffer)
		} else if messageBuffer[0] == 'q' && messageBuffer[1] == 'u' && messageBuffer[2] == 'i' && messageBuffer[3] == 't' {
			c.Write(bye)
			c.Close()
		} else {
			c.Write(echo)
			c.Write(messageBuffer)
		}
	}
}
