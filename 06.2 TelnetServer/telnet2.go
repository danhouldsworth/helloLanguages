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
	welcome := []byte("\n\n --- Welcome to Telnet Echo & Bye in Go! --- \n\n")
	echo := []byte("Server echo service : ")
	bye := []byte("\n\n --- Bye for now!! --- \n\n")

	c.Write(welcome)
	for {
		messageBuffer := make([]byte, 1024)
		c.Read(messageBuffer)
		if messageBuffer[0] == 'q' && messageBuffer[1] == 'u' && messageBuffer[2] == 'i' && messageBuffer[3] == 't' {
			c.Write(bye)
			c.Close()
		} else {
			c.Write(append(echo, messageBuffer...))
		}
	}
}
