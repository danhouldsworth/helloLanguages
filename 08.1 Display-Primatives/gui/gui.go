package gui

import (
	"crypto/sha1"
	"encoding/base64"
	"fmt"
	"io/ioutil"
	"net"
	"runtime"
	"strconv"
	"strings"
)

var (
	tcpConn    net.Conn           // Can be global as we don't intend to server multiple connections
	IP         = "127.0.0.1:8888" // Feel free to serve across Network / LAN
	ScreenSize = 1024             // If we stick to a power of 2, integer division is easier
	html       string
)

// -- Expose Setup API
func Screen(s int) {
	ScreenSize = s
}
func Address(s string) {
	IP = s
}
func Launch() {
	// -- Set & Announce multicore
	cpu := runtime.NumCPU()
	runtime.GOMAXPROCS(cpu)
	fmt.Printf("\nThere are %d CPU cores available. Allocating %d CPU cores for our purposes...\n", cpu, runtime.GOMAXPROCS(-1))
	// --

	// -- Listen & serve the GUIdisplay
	fmt.Println("\nWaiting for Display.... Please navigate to " + IP + " to commence.")
	listener, _ := net.Listen("tcp", IP)
	for webSocReady := false; webSocReady != true; {
		tcpConn, _ = listener.Accept()
		webSocReady = handleTCP()
	}
	// --
}

// --

// -- Expose runtime API
func Plot(x int, y int, r uint8, g uint8, b uint8, a uint8) {
	wsWrite([8]byte{hiByte(x), lowByte(x), hiByte(y), lowByte(y), r, g, b, a})
}

// --

func hashWithMagicKey(clientKey string) string {
	hasher := sha1.New()
	hasher.Write([]byte(clientKey + "258EAFA5-E914-47DA-95CA-C5AB0DC85B11")) // MagicKey
	return "Sec-WebSocket-Accept: " + base64.StdEncoding.EncodeToString(hasher.Sum(nil))
}

func readBytesOnWire() string {
	messageBuffer := make([]byte, 1024)
	tcpConn.Read(messageBuffer)
	return string(messageBuffer)
}

func handleTCP() bool {
	guiDisplay := strings.Replace(html, "GUI_SCREEN_SIZE", strconv.Itoa(ScreenSize), -1)
	guiDisplay = strings.Replace(guiDisplay, "GUI_IP", IP, -1)
	var Upgrade, clientKey string

	// -- Assume incoming HTTP GET request for WebSocket Upgrade on TCP connection. Parse Upgrade & Key if present
	request := readBytesOnWire()
	if UpgradeIndex := strings.Index(request, "Upgrade:"); UpgradeIndex != -1 {
		Upgrade = request[UpgradeIndex+9 : UpgradeIndex+9+9]
	}
	if clientKeyIndex := strings.Index(request, "Sec-WebSocket-Key:"); clientKeyIndex != -1 {
		clientKey = request[clientKeyIndex+19 : clientKeyIndex+19+24]
	}

	// -- Serve GUIdisplay if not WebSocket upgrade request
	if Upgrade == "" {
		tcpConn.Write([]byte(guiDisplay))
		fmt.Println("*** Serving GUIdisplay Page ***")
		tcpConn.Close()
		// Otherwise handshake and start sedning display...
	} else if Upgrade == "websocket" {
		acceptKey := hashWithMagicKey(clientKey)
		tcpConn.Write([]byte(wsUpgrade + acceptKey + "\r\n\r\n"))
		fmt.Println("*** GUIdisplay Opened WebSocket ***")
		return true
	}
	return false
	//---
}

//
// -- Useful functions Todo : Tidy up
//

func lowByte(i int) uint8 {
	return uint8(i & 0xff)
}

func hiByte(i int) uint8 {
	return uint8((i & 0xff00) >> 8)
}
func wsWrite(plotPacket [8]byte) {
	wsFrame := []byte{byte(1*128 + 1*2), 8} // FIN bit + Binary Type
	tcpConn.Write([]byte{wsFrame[0], wsFrame[1], plotPacket[0], plotPacket[1], plotPacket[2], plotPacket[3], plotPacket[4], plotPacket[5], plotPacket[6], plotPacket[7]})
}

// -- Setup
func init() {
	htmlB, err := ioutil.ReadFile("gui/GUIdisplay.html")
	if err != nil {
		panic(err)
	}
	html = string(htmlB)
}

const wsUpgrade = "HTTP/1.1 101 Switching Protocols\r\nUpgrade: websocket\r\nConnection: Upgrade\r\nOrigin: null\r\nSec-WebSocket-Protocol: single-pixel-GUI-protocol\r\n"

// --
