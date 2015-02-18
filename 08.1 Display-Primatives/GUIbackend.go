package main

import (
	"crypto/sha1"
	"fmt"
	// "math"
	// "math/rand"
	"net"
	"runtime"
	"strconv"
	"strings"
	// "time"
)

var (
	tcpConn    net.Conn      // Can be global as we don't intend to server multiple connections
	screenSize = 1024        // If we stick to a power of 2, integer division is easier
	IP         = "127.0.0.1" // Feel free to serve across Network / LAN
	PORT       = "8888"
	// cores      = 0
)

//
// -- This graphics function will be run, repeatedly (unless you exit), on the GUIdisplay
//
func performSomeGraphics() {

	// // eg#1 Move small 50px lines across the screen in a time controlled fashion
	// fmt.Printf("\nMoving line : %5.1f%%", 0.0)
	// for line := 1; line < screenSize; line++ {
	// 	fmt.Printf("\b\b\b\b\b\b%5.1f%%", 100*ratio(line, screenSize))
	// 	for j := screenSize>>1 - screenSize>>5; j < screenSize>>1+screenSize>>5; j++ {
	// 		wsWrite([8]byte{HiByte(line - 1), LoByte(line - 1), HiByte(j), LoByte(j), 255, 255, 255, 255})
	// 		wsWrite([8]byte{HiByte(j), LoByte(j), HiByte(line - 1), LoByte(line - 1), 255, 255, 255, 255})
	// 		wsWrite([8]byte{HiByte(j), LoByte(j), HiByte(screenSize - line + 1), LoByte(screenSize - line + 1), 255, 255, 255, 255})
	// 		wsWrite([8]byte{HiByte(screenSize - line + 1), LoByte(screenSize - line + 1), HiByte(j), LoByte(j), 255, 255, 255, 255})
	// 	}
	// 	for j := screenSize>>1 - screenSize>>5; j < screenSize>>1+screenSize>>5; j++ {
	// 		wsWrite([8]byte{HiByte(line), LoByte(line), HiByte(j), LoByte(j), 255, 0, 0, 255})
	// 		wsWrite([8]byte{HiByte(j), LoByte(j), HiByte(line), LoByte(line), 0, 255, 0, 255})
	// 		wsWrite([8]byte{HiByte(j), LoByte(j), HiByte(screenSize - line), LoByte(screenSize - line), 0, 0, 255, 255})
	// 		wsWrite([8]byte{HiByte(screenSize - line), LoByte(screenSize - line), HiByte(j), LoByte(j), 0, 0, 0, 255})
	// 	}
	// 	time.Sleep(25 * time.Millisecond)
	// }
	// fmt.Printf("\nDone!\n")
	// // --

	// // -- eg#2 Build a custom rastor of a calculated image
	// fmt.Printf("\nMath image : %5.1f%%", 0.0)
	// offsetX := [16]int{0, 2, 2, 0, 3, 0, 1, 2, 1, 1, 0, 2, 3, 3, 3, 1}
	// offsetY := [16]int{0, 2, 0, 2, 1, 1, 1, 1, 3, 2, 3, 3, 0, 2, 3, 0}
	// for m := 0; m <= 15; m++ {
	// 	for i := 0; i <= screenSize; i = i + 4 {
	// 		for j := 0; j <= screenSize; j = j + 4 {
	// 			fmt.Printf("\b\b\b\b\b\b%5.1f%%", 100*ratio(m*screenSize*screenSize+i*screenSize+j, 16*screenSize*screenSize))
	// 			wsWrite(calcImage(i+offsetX[m], j+offsetY[m]))
	// 		}
	// 	}
	// }
	// fmt.Printf("\nDone!\n")
	// // --

	// --eg#3 Display a mandlebrot set spiraling in
	left, top := 0, 0
	right, bottom := screenSize-1, screenSize-1
	go mandy(left, right, top, bottom)
	// --

	// // eg#4 3 bodies moving under gravity
	// type body struct {
	// 	mass         int
	// 	x, y, vx, vy float64
	// 	r, g, b      byte
	// }
	// numberBodies := 30
	// speed := 0.1
	// bodies := make([]body, numberBodies)
	// for i := 0; i < numberBodies; i++ {
	// 	bodies[i] = body{rand.Intn(255), float64(rand.Intn(screenSize)), float64(rand.Intn(screenSize)), speed*rand.Float64() - speed/2, speed*rand.Float64() - speed/2, byte(rand.Intn(255)), byte(rand.Intn(255)), byte(rand.Intn(255))}
	// }

	// for {
	// 	for i := 0; i < numberBodies; i++ {
	// 		for j := 0; j < numberBodies; j++ {
	// 			if i != j {
	// 				dx := bodies[i].x - bodies[j].x
	// 				dy := bodies[i].y - bodies[j].y
	// 				r2 := dx*dx + dy*dy
	// 				if r2 > 50 {
	// 					r := math.Sqrt(r2)
	// 					force := 0.01 * float64(bodies[i].mass*bodies[j].mass) / r2
	// 					bodies[i].vx -= (force / float64(bodies[i].mass)) * dx / r
	// 					bodies[j].vx += (force / float64(bodies[i].mass)) * dx / r
	// 					bodies[i].vy -= (force / float64(bodies[i].mass)) * dy / r
	// 					bodies[j].vy += (force / float64(bodies[i].mass)) * dy / r
	// 				}
	// 			}
	// 		}
	// 		// Move with velocity
	// 		bodies[i].x += bodies[i].vx
	// 		bodies[i].y += bodies[i].vy
	// 		// Drag
	// 		// bodies[i].vx -= 0.001 * bodies[i].vx * bodies[i].vx * bodies[i].vx
	// 		// bodies[i].vy -= 0.001 * bodies[i].vy * bodies[i].vy * bodies[i].vy
	// 		// Wrap boundaries
	// 		if bodies[i].x < 0 {
	// 			bodies[i].x += float64(screenSize)
	// 		}
	// 		if bodies[i].y < 0 {
	// 			bodies[i].y += float64(screenSize)
	// 		}
	// 		if bodies[i].x > float64(screenSize) {
	// 			bodies[i].x -= float64(screenSize)
	// 		}
	// 		if bodies[i].y > float64(screenSize) {
	// 			bodies[i].y -= float64(screenSize)
	// 		}

	// 		wsWrite([8]byte{HiByte(round(bodies[i].x)), LoByte(round(bodies[i].x)), HiByte(round(bodies[i].y)), LoByte(round(bodies[i].y)), bodies[i].r, bodies[i].g, bodies[i].b, byte(bodies[i].mass)})
	// 	}
	// 	time.Sleep(1 * time.Millisecond)
	// 	// fmt.Printf("Body1 x=%f, y=%f, vx=%f, vy=%f\n", bodies[0].x, bodies[0].y, bodies[0].vx, bodies[0].vy)
	// }
	// --
}

func mandy(left, right, top, bottom int) {
	deltaX := 1
	deltaY := 0
	colourBlock := true
	firstColour := isMandy(mapToArgand(left, top)) // This wastes a pixel calc

	for i, j, edge := left, top, 0; edge < 4; i, j = i+deltaX, j+deltaY {
		dwell := isMandy(mapToArgand(i, j))
		if colourBlock == true && dwell != firstColour {
			colourBlock = false
			// Initiate recurcise split immediately in case of idle CPUs
			if top < bottom-2 && left < right-2 {
				midleft := left + (right-left)/2
				midtop := top + (bottom-top)/2
				go mandy(left+1, midleft, top+1, midtop)         // TL
				go mandy(left+1, midleft, midtop+1, bottom-1)    // BL
				go mandy(1+midleft, right-1, midtop+1, bottom-1) // BR
				go mandy(1+midleft, right-1, top+1, midtop)      // TR
			}

		}
		// wsWrite([8]byte{HiByte(i), LoByte(i), HiByte(j), LoByte(j), 255 * byte(dwell%2), 255 * byte(dwell%2), 255 * byte(dwell%2), 255})
		wsWrite([8]byte{HiByte(i), LoByte(i), HiByte(j), LoByte(j), byte(dwell % 64), byte(dwell % 16), byte(dwell % 2), 255 - byte(dwell%256)})
		if deltaX > 0 && i == right {
			edge++
			deltaX--
			deltaY++
		} else if deltaY > 0 && j == bottom {
			edge++
			deltaX--
			deltaY--
		} else if deltaX < 0 && i == left {
			edge++
			deltaX++
			deltaY--
		} else if deltaY < 0 && j == top {
			edge++
			deltaX++
			deltaY++
		}
	}
	if colourBlock == true {
		//plot full block & break in firstColour
	}
}
func calcImage(i, j int) [8]byte {
	x := ratio(i, screenSize/2) - 1
	y := ratio(j, screenSize/2) - 1
	r := x*x + y*y
	return [8]byte{HiByte(i), LoByte(i), HiByte(j), LoByte(j), uint8(255 * (1 - r)), uint8(128 + 128*x), uint8(128 + 128*y), 255}
}

func isMandy(c complex128) (dwell int) {
	maxDwell := 2 << 20
	dwell = 0
	for z := c; real(z)*real(z)+imag(z)*imag(z) < 4; z = z*z + c {
		dwell++
		if dwell >= maxDwell {
			return
		}
	}
	return
}

func mapToArgand(x, y int) complex128 {
	min, max := complex(-2, -1.5), complex(1, 1.5)
	return min + complex(ratio(x, screenSize)*real(max-min), ratio(y, screenSize)*imag(max-min))
}

//
// -- Useful functions Todo : Tidy up
//
func LoByte(i int) uint8 {
	return uint8(i & 0xff)
}

func HiByte(i int) uint8 {
	return uint8((i & 0xff00) >> 8)
}

func wsWrite(plotPacket [8]byte) {
	wsFrame := []byte{byte(1*128 + 1*2), 8} // FIN bit + Binary Type
	tcpConn.Write([]byte{wsFrame[0], wsFrame[1], plotPacket[0], plotPacket[1], plotPacket[2], plotPacket[3], plotPacket[4], plotPacket[5], plotPacket[6], plotPacket[7]})
}

func ratio(a, b int) float64 {
	return float64(a) / float64(b)
}
func round(value float64) int {
	if value < 0.0 {
		value -= 0.5
	} else {
		value += 0.5
	}
	return int(value)
}

//
// --
//

//
// -- Listen & serve the GUIdisplay
//
func hashWithMagicKey(clientKey string) string {
	hasher := sha1.New()
	hasher.Write([]byte(clientKey + "258EAFA5-E914-47DA-95CA-C5AB0DC85B11")) // MagicKey
	return "Sec-WebSocket-Accept: " + base64(hasher.Sum(nil))
}

func readBytesOnWire() string {
	messageBuffer := make([]byte, 1024)
	tcpConn.Read(messageBuffer)
	return string(messageBuffer)
}

func main() {
	// -- Set & Announce multicore
	cpu := runtime.NumCPU()
	runtime.GOMAXPROCS(cpu)
	fmt.Printf("\nThere are %d CPU cores available. Allocating %d CPU cores for our purposes...\n", cpu, runtime.GOMAXPROCS(-1))
	// --

	fmt.Println("\nWaiting for Display.... Please navigate to " + IP + ":" + PORT + " to commence.")
	listener, _ := net.Listen("tcp", ":"+PORT)
	for {
		tcpConn, _ = listener.Accept()
		handleTCP() // Deliberatly blocking (Only want to do this once!!)
	}
}

func handleTCP() {
	wsUpgrade := "HTTP/1.1 101 Switching Protocols\r\nUpgrade: websocket\r\nConnection: Upgrade\r\nOrigin: null\r\nSec-WebSocket-Protocol: single-pixel-GUI-protocol\r\n"
	guiDisplay := "<html><head><title>Screen over WebSockets</title><body></body><script>var canvas = document.createElement('CANVAS');canvas.width = canvas.height = " + strconv.Itoa(screenSize) + ";document.body.appendChild(canvas);var ctx = canvas.getContext('2d');var imagedata = ctx.getImageData(0,0,canvas.width, canvas.height);var offset = function(x,y) {return (y * canvas.width + x) * 4;};var plotPacket = new ArrayBuffer(6);var plotPacketData = new Uint8Array(plotPacket);var ws = new WebSocket('ws://" + IP + ":" + PORT + "/', 'single-pixel-GUI-protocol');ws.binaryType = 'arraybuffer';ws.onopen = function() {ws.send('GUI Ready');};ws.onmessage = function(e) {plotPacketData = new Uint8Array(e.data);var xHi = plotPacketData[0];var xLo = plotPacketData[1];var yHi = plotPacketData[2];var yLo = plotPacketData[3];var R = plotPacketData[4];var G = plotPacketData[5];var B = plotPacketData[6];var A = plotPacketData[7];var x = xHi * 256 + xLo;var y = yHi * 256 + yLo;imagedata.data[offset(x,y) + 0] = R;imagedata.data[offset(x,y) + 1] = G;imagedata.data[offset(x,y) + 2] = B;imagedata.data[offset(x,y) + 3] = A;};function refresh(){ctx.putImageData(imagedata,0,0);window.requestAnimationFrame(refresh);}window.requestAnimationFrame(refresh);</script></head></html>"
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
		// for {
		performSomeGraphics() // Deliberatly blocking (Only want to do this once!!)
		// }
	}
	//---
}

//
// --
//

//
// -- Homemade base64 library
//
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

//
// --
//
