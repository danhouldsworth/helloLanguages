// 6. Done. Boooomm!!

package main

import (
	"crypto/sha1"
	"encoding/base64"
	"fmt"
	// "io"
	"net"
)

func main() {
	listener, err := net.Listen("tcp", ":8006")
	if err != nil {
		fmt.Print(err)
	}
	conn, err := listener.Accept()
	if err != nil {
		fmt.Print(err)
	}

	wsUpgrade := []byte("HTTP/1.1 101 Switching Protocols\r\nUpgrade: websocket\r\nConnection: Upgrade\r\nOrigin: null\r\n")
	protocol := []byte("Sec-WebSocket-Protocol: flt-protocol\r\n")
	key := []byte("Sec-WebSocket-Accept: ")

	messageBuffer := make([]byte, 1024)
	conn.Read(messageBuffer)
	fmt.Printf("\nRecieved :\n-->%s<--\n", string(messageBuffer))

	// parse messageBuffer for "Sec-WebSocket-Key: 1234567890123456789012==" clientkey eg:
	clientKey := string(messageBuffer[387:411])
	clientKey += "258EAFA5-E914-47DA-95CA-C5AB0DC85B11" // append MAGICKEY

	hasher := sha1.New()
	hasher.Write([]byte(clientKey))
	acceptKey := base64.StdEncoding.EncodeToString(hasher.Sum(nil))

	conn.Write(wsUpgrade)
	conn.Write(protocol)
	conn.Write(key)
	conn.Write([]byte(acceptKey))
	conn.Write([]byte("\r\n\r\n"))

	messageBuffer = make([]byte, 1024)
	conn.Read(messageBuffer)
	fmt.Printf("\nRecieved :\n-->%s<--\n", string(messageBuffer))

	// conn.Close()
}
