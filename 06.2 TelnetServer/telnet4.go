// 3. Done

package main

import (
	"fmt"
	"net"
)

var (
	port        = 4000
	connections = make(map[net.Conn]int)
)

func main() {
	user := 0
	listener, _ := net.Listen("tcp", fmt.Sprintf(":%d", port))
	fmt.Printf("Listening on port %d\n", port)
	for {
		conn, _ := listener.Accept()
		user++
		connections[conn] = user
		go handleConnection(conn)
	}
}

func handleConnection(c net.Conn) {
	user := connections[c]
	fmt.Printf("Accepting new user #%d\n", user)
	c.Write([]byte(fmt.Sprintf("\n\n --- Welcome to Telnet Echo & Relay in Go! --- \n\nYou are user : %d\n", user)))

	for {
		// Read
		messageBuffer := make([]byte, 1024)
		parsedMsg := make([]byte, 1024)
		c.Read(messageBuffer)
		// Parse
		for i, j := 0, 0; i < 1000 || j < 1000; i, j = i+1, j+1 {
			if messageBuffer[i] == '\n' {
				parsedMsg[j] = '\\'
				parsedMsg[j+1] = 'n'
				j++
			} else if messageBuffer[i] == '\r' {
				parsedMsg[j] = '\\'
				parsedMsg[j+1] = 'r'
				j++
			} else {
				parsedMsg[j] = messageBuffer[i]
			}
		}
		// Broadcast
		for destination := range connections {
			broadcast := fmt.Sprintf("User #%d says >>> %s <<<\n", user, string(parsedMsg))
			fmt.Printf("Relaying msg from #%d to #%d : %s", user, connections[destination], broadcast)
			destination.Write([]byte(broadcast))
		}
	}
}
