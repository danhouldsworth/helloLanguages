// 6. Done. Boooomm!!

package main

import (
	"crypto/sha1"
	"fmt"
	"net"
)

var (
	wsUpgrade = "HTTP/1.1 101 Switching Protocols\r\nUpgrade: websocket\r\nConnection: Upgrade\r\nOrigin: null\r\nSec-WebSocket-Protocol: echo-protocol\r\n"
)

func hashWithMagicKey(clientKey string) string {
	hasher := sha1.New()
	hasher.Write([]byte(clientKey + "258EAFA5-E914-47DA-95CA-C5AB0DC85B11")) // MagicKey
	return "Sec-WebSocket-Accept: " + base64(hasher.Sum(nil))
}

func sendBytesOnWire(c net.Conn, b []byte) {
	c.Write(b)
	fmt.Printf("\n*** Sending data on TCP/IP *** STARTS------------>%s<------------ENDS\n", string(b))
}

func readBytesOnWire(c net.Conn) string {
	messageBuffer := make([]byte, 1024)
	c.Read(messageBuffer)
	fmt.Printf("\n*** Recieved data on TCP/IP *** STARTS------------>%s<------------ENDS\n", string(messageBuffer))
	return string(messageBuffer)
}

func main() {
	listener, _ := net.Listen("tcp", ":8006")
	tcpConn, _ := listener.Accept()

	// -- WebSocket Upgrade Handshake
	msgString := readBytesOnWire(tcpConn)
	clientKey := string(msgString[386:410]) // A guess!! fmt.Printf("Guess : %s", clientKey)
	acceptKey := hashWithMagicKey(clientKey)
	sendBytesOnWire(tcpConn, []byte(wsUpgrade+acceptKey+"\r\n\r\n"))
	// --

	wsWrite(tcpConn, "Woo-hoo! Are you listening yet....!!")

	// -- Listen & parse WebSocketFrames
	for {
		wsMsg := readBytesOnWire(tcpConn)
		payloadLength := wsMsg[1] & 127
		unmaskedPayload := make([]byte, payloadLength)
		mask := []byte{wsMsg[2], wsMsg[3], wsMsg[4], wsMsg[5]}
		payload := []byte(wsMsg[6 : payloadLength+6])
		// UnMask with XOR
		for index, maskedByte := range payload {
			unmaskedPayload[index] = maskedByte ^ mask[index%4]
		}
		wsWrite(tcpConn, "YeHah! You just sent me : "+string(unmaskedPayload))
	}
}

func wsWrite(c net.Conn, msg string) {
	payload := []byte(msg)
	payloadLength := len(payload) // Max 127 otherwise will screw with MASK bit
	wsFrame := []byte{byte(129), byte(payloadLength)}
	sendBytesOnWire(c, append(wsFrame, payload...))
}

func base64(inputMsg []byte) string {
	outputMsg := make([]byte, 4*((len(inputMsg)+2)/3))
	for i, j := 0, 0; i < len(inputMsg); i, j = i+3, j+4 {
		for index, element := range getFourBytesFromThree(inputMsg[i:]) {
			outputMsg[j+index] = element
		}
	}
	return string(outputMsg)
}

func getFourBytesFromThree(src []byte) []byte {
	four := []byte{0, 0, 0, 0}
	three := []byte{0, 0, 0}

	switch len(src) {
	case 1:
		three = append(src[0:1], []byte{0, 0}...)
	case 2:
		three = append(src[0:2], 0)
	default:
		three = src[0:3]
	}

	four[0] += three[0] & (1*128 + 1*64 + 1*32 + 1*16 + 1*8 + 1*4 + 0*2 + 0*1) / (2 * 2)

	four[1] += three[0] & (0*128 + 0*64 + 0*32 + 0*16 + 0*8 + 0*4 + 1*2 + 1*1) * (2 * 2 * 2 * 2)
	four[1] += three[1] & (1*128 + 1*64 + 1*32 + 1*16 + 0*8 + 0*4 + 0*2 + 0*1) / (2 * 2 * 2 * 2)

	four[2] += three[1] & (0*128 + 0*64 + 0*32 + 0*16 + 1*8 + 1*4 + 1*2 + 1*1) * (2 * 2)
	four[2] += three[2] & (1*128 + 1*64 + 0*32 + 0*16 + 0*8 + 0*4 + 0*2 + 0*1) / (2 * 2 * 2 * 2 * 2 * 2)

	four[3] += three[2] & (0*128 + 0*64 + 1*32 + 1*16 + 1*8 + 1*4 + 1*2 + 1*1)

	m := []byte{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'}

	switch len(src) {
	case 1:
		return []byte{m[four[0]], m[four[1]], '=', '='}
	case 2:
		return []byte{m[four[0]], m[four[1]], m[four[2]], '='}
	default:
		return []byte{m[four[0]], m[four[1]], m[four[2]], m[four[3]]}
	}
}
