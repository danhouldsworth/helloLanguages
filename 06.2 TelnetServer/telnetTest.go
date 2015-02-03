// 3. Done

package main

import (
	"fmt"
	"net"
)

var (
	port        = 4000
	connections = make(map[net.Conn]bool) // Q : Does listener.Accept() return a pointer to, or a net.Conn?
)

func main() {
	user := 0
	listener, _ := net.Listen("tcp", fmt.Sprintf(":%d", port))
	fmt.Printf("Listening on port %d\n", port)
	for {
		conn, _ := listener.Accept()
		connections[conn] = true
		user++
		go handleConnection(user, conn)
	}
}

func handleConnection(user int, c net.Conn) {
	fmt.Printf("Accepting new user #%d\n", user)
	c.Write([]byte(fmt.Sprintf("\n\n --- Welcome to Telnet Echo & Relay in Go! --- \n\nYou are user : %d\n", user)))

	for {
		//READ
		messageBuffer := make([]byte, 1024)
		c.Read(messageBuffer)
		// BROADCAST
		for destination := range connections {
			broadcast := fmt.Sprintf("User #%d says : %s", user, string(messageBuffer))
			fmt.Printf("Relaying msg from #%d to #%d : %s", user, 0, broadcast)
			destination.Write([]byte(broadcast))
		}
	}
}
