// A test of the interview websocket challenge

package main

import (
	"net"
)

var (
	webSocketHandshake = []byte("GET / HTTP/1.1\r\nConnection: Upgrade\r\nUpgrade: websocket\r\nSec-WebSocket-Version: 13\r\nSec-WebSocket-Key: IWillDemonstrateMySkills\r\n\r\n")
	wsFrameBits1       = []byte{1, 125 + 128, 0, 0, 0, 0}
	wsPayload1         = []byte("This is an example of a single WebSocket payload.\nWe're limited from 1-125 bytes.\nPlenty to tell me your contact details :-)\n")
	wsFrameBits2       = []byte{1, 85 + 128, 0, 0, 0, 0}
	wsPayload2         = []byte("If you need send a bio for Challenge #1, or even a lengthy Quine for Challenge #2...\n")
	wsFrameBits3       = []byte{1, 106 + 128, 0, 0, 0, 0}
	wsPayload3         = []byte("Then just send more payloads.\nOf course being sure to set your payload length bits correctly each time...\n")
)

func main() {

	tcpAddr, _ := net.ResolveTCPAddr("tcp", "nyc.bramble.io:80")
	conn, _ := net.DialTCP("tcp", nil, tcpAddr)

	conn.Write(webSocketHandshake)
	println("Writing to server = ", string(webSocketHandshake))

	reply := make([]byte, 1024)
	conn.Read(reply)
	println("Reply received from server=", string(reply))

	conn.Write(append(wsFrameBits1, wsPayload1...))
	conn.Write(append(wsFrameBits2, wsPayload2...))
	conn.Write(append(wsFrameBits3, wsPayload3...))

	conn.Close()
}
