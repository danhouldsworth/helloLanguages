// 6. Done. Boooomm!!

package main

import (
	"crypto/sha1"
	"fmt"
	"net"
	"strings"
)

var (
	wsUpgrade          = "HTTP/1.1 101 Switching Protocols\r\nUpgrade: websocket\r\nConnection: Upgrade\r\nOrigin: null\r\nSec-WebSocket-Protocol: single-pixel-GUI-protocol\r\n"
	Upgrade, clientKey string
)

func hashWithMagicKey(clientKey string) string {
	hasher := sha1.New()
	hasher.Write([]byte(clientKey + "258EAFA5-E914-47DA-95CA-C5AB0DC85B11")) // MagicKey
	return "Sec-WebSocket-Accept: " + base64(hasher.Sum(nil))
}

func readBytesOnWire(c net.Conn) string {
	messageBuffer := make([]byte, 1024)
	c.Read(messageBuffer)
	fmt.Printf("\n*** Recieved data on TCP/IP *** STARTS------------>%s<------------ENDS\n", string(messageBuffer))
	return string(messageBuffer)
}

func main() {
	listener, _ := net.Listen("tcp", ":8888")
	tcpConn, _ := listener.Accept()

	// -- Assume incoming HTTP GET request for WebSocket Upgrade on TCP connection. Parse Upgrade & Key if present
	msgString := readBytesOnWire(tcpConn)
	if UpgradeIndex := strings.Index(msgString, "Upgrade:"); UpgradeIndex != -1 {
		Upgrade = msgString[UpgradeIndex+9 : UpgradeIndex+9+9]
	}
	if clientKeyIndex := strings.Index(msgString, "Sec-WebSocket-Key:"); clientKeyIndex != -1 {
		clientKey = msgString[clientKeyIndex+19 : clientKeyIndex+19+24]
	}
	acceptKey := hashWithMagicKey(clientKey)
	tcpConn.Write([]byte(wsUpgrade + acceptKey + "\r\n\r\n"))
	// --

	// -- Perform modeling and send Plot Packets down the WebSocket
	fmt.Printf("\nSending Plot Packets : %5.1f%%", 0.0)
	offsetX := [16]uint16{0, 2, 2, 0, 3, 0, 1, 2, 1, 1, 0, 2, 3, 3, 3, 1}
	offsetY := [16]uint16{0, 2, 0, 2, 1, 1, 1, 1, 3, 2, 3, 3, 0, 2, 3, 0}
	for m := 0; m <= 15; m++ {
		for i := uint16(0); i <= 1000; i = i + 4 {
			for j := uint16(0); j <= 1000; j = j + 4 {
				fmt.Printf("\b\b\b\b\b\b%5.1f%%", 100*float64(m*1000000+int(i)*1000+int(j))/16000000)
				wsWrite(tcpConn, calcImage(i+offsetX[m], j+offsetY[m]))
			}
		}
	}
	fmt.Printf("\nDone!\n")
	// --

}
func calcImage(i, j uint16) [8]byte {
	x := float64(i)/500 - 1
	y := float64(j)/500 - 1
	r := x*x + y*y
	return [8]byte{HiByte(i), LoByte(i), HiByte(j), LoByte(j), uint8(255 * (1 - r)), uint8(128 + 128*x), uint8(128 + 128*y), 255}

}
func LoByte(i uint16) uint8 {
	return uint8(i & 0xff)
}
func HiByte(i uint16) uint8 {
	return uint8((i & 0xff00) >> 8)
}
func wsWrite(c net.Conn, plotPacket [8]byte) {
	wsFrame := []byte{byte(1*128 + 1*2), 8} // FIN bit + Binary Type
	c.Write([]byte{wsFrame[0], wsFrame[1], plotPacket[0], plotPacket[1], plotPacket[2], plotPacket[3], plotPacket[4], plotPacket[5], plotPacket[6], plotPacket[7]})
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

	four[0] += three[0] & (1*128 + 1*64 + 1*32 + 1*16 + 1*8 + 1*4 + 0*2 + 0*1) >> 2

	four[1] += three[0] & (0*128 + 0*64 + 0*32 + 0*16 + 0*8 + 0*4 + 1*2 + 1*1) << 4
	four[1] += three[1] & (1*128 + 1*64 + 1*32 + 1*16 + 0*8 + 0*4 + 0*2 + 0*1) >> 4

	four[2] += three[1] & (0*128 + 0*64 + 0*32 + 0*16 + 1*8 + 1*4 + 1*2 + 1*1) << 2
	four[2] += three[2] & (1*128 + 1*64 + 0*32 + 0*16 + 0*8 + 0*4 + 0*2 + 0*1) >> 6

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
