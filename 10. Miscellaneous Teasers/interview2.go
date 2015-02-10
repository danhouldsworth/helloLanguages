// Stand-alone Interview WebSocket Page - Version 2

package main

import (
	"log"
	"net"
	"os/exec"
	"strings"
	"time"
)

var (
	staticPage    = "<!doctype html><html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"/><title>Careers @ Immerse Learning</title><link href='http://fonts.googleapis.com/css?family=Roboto:400,300,100' rel='stylesheet' type='text/css'></link> <link rel=\"shortcut icon\" href=\"https://s3-eu-west-1.amazonaws.com/keystone-project/will_images/favicon.ico\"><style type=\"text/css\">body{background: #ebebeb;font-family: 'Roboto', sans-serif;}h1{text-align: center;font-size: 36px;font-weight: 300;}p{font-size: 16px;}ol{font-size: 16px;}.roundedContainer{display: block;position: relative;background: #ffffff;width: 60%;margin: 20px auto;border-radius: 10px;padding: 20px 50px;text-align: left; max-width: 800px;}.watermark{display: block;position: relative;width: 40%; min-width: 400px;margin: 20px auto 0 auto;}.socialContainer{display: block; position: relative; width: 60%; margin: 40px auto; text-align: center;}.socialIcons{width: 45px; margin: 0 20px 0 20px;}li{margin-bottom: 5px;}</style></head><body><img class=\"watermark\" src=\"https://s3-eu-west-1.amazonaws.com/keystone-project/will_images/immerse-75.png\"/><div class=\"roundedContainer\"><h1> We're Hiring! </h1><p>At Immerse we are passionate about both results and creativity - and this starts with our search for talent.</p><p>This server is listening for incoming WebSocket connections that are using the modified 24-byte handshake key 'IWillDemonstrateMySkills'. Any data received will be saved as a text file and reviewed.</p><ol><li>If you manage to upload your CV, we will invite you for a face to face interview to further demonstrate your skills.</li><li>Upload a valid <a href=\"http://en.wikipedia.org/wiki/Quine_(computing)\">Quine</a> containing your brief bio, that when executed transmits an exact copy of itself along the WebSocket and you will be invited to spend a whole day with the team, including interviews with the CEO and CTO.</li><li>Find a way to deposit a file 'employ_me.now' containing your contact details and you will immediately be offered a permanent role as a senior developer.</li></ol><p> Good luck! </p></div><div class=\"socialContainer\"> <a href=\"https://vimeo.com/immerselearning\"><img src=\"https://s3-eu-west-1.amazonaws.com/keystone-project/will_images/vimeo.png\"/ class=\"socialIcons\"></a> <a href=\"http://uk.linkedin.com/company/immerse-learning\"><img src=\"https://s3-eu-west-1.amazonaws.com/keystone-project/will_images/linkedin.png\" class=\"socialIcons\"/></a> <a href=\"https://plus.google.com/106802764981985442192/posts\"><img src=\"https://s3-eu-west-1.amazonaws.com/keystone-project/will_images/googleplus.png\" class=\"socialIcons\"/></a> <a href=\"https://twitter.com/ImmerseLearning\" class=\"socialIcons\"><img src=\"https://s3-eu-west-1.amazonaws.com/keystone-project/will_images/twitter.png\" class=\"socialIcons\"/></a> </div></body>"
	acceptUpgrade = "HTTP/1.1 101 Switching Protocols\r\nUpgrade: websocket\r\nConnection: Upgrade\r\nOrigin: null\r\nSec-WebSocket-Protocol: echo-protocol\r\n"
	denyUpgrade   = "HTTP/1.1 412 Precondition Failed\r\n\r\nThat is not the Sec-WebSocket-Key we requested."
)

func main() {
	// ToDO : Error handling
	listener, _ := net.Listen("tcp", ":8006")
	for {
		tcpConn, _ := listener.Accept()
		go handleTCP(tcpConn)
	}
}

func handleTCP(c net.Conn) {

	Upgrade := ""
	clientKey := ""

	// -- Assume incoming HTTP GET request on TCP connection. Parse Upgrade & Key if present
	msgString := readBytesOnWire(c)
	if UpgradeIndex := strings.Index(msgString, "Upgrade:"); UpgradeIndex != -1 {
		Upgrade = msgString[UpgradeIndex+9 : UpgradeIndex+9+9]
	}
	if clientKeyIndex := strings.Index(msgString, "Sec-WebSocket-Key:"); clientKeyIndex != -1 {
		clientKey = msgString[clientKeyIndex+19 : clientKeyIndex+19+24]
	}
	// --

	if Upgrade == "" {
		c.Write([]byte(staticPage))
		log.Println("*** Serving Static Page")
		c.Close()
	} else if Upgrade == "websocket" {
		log.Printf("WebSocket Upgrade Attempt : 24-byte Key >>>%s<<<\n", clientKey)
		if clientKey != "IWillDemonstrateMySkills" {
			sendBytesOnWire(c, []byte(denyUpgrade+"\r\n\r\n"))
			c.Close()
		} else {
			sendBytesOnWire(c, []byte(acceptUpgrade+"ImmerseCustomKeyAccepted"+"\r\n\r\n"))
			go handleWebSocket(c)
		}

	} else if Upgrade != "websocket" {
		log.Printf("*** Invalid Socket Upgrade Request! *** : %s", Upgrade)
		sendBytesOnWire(c, []byte("<h1>Invalid Socket Upgrade Request!</h1>"))
	}
}

func handleWebSocket(tcpConn net.Conn) {

	// -- Listen & parse WebSocketFrames
	for {

		// -- Read OpCode / Mask / Payload bits
		wsMsg := readBytesOnWire(tcpConn)
		opcode := wsMsg[0] & 15
		payloadLength := wsMsg[1] & 127
		unmaskedPayload := make([]byte, payloadLength)
		mask := []byte{wsMsg[2], wsMsg[3], wsMsg[4], wsMsg[5]}
		payload := []byte(wsMsg[6 : payloadLength+6])
		// --

		// -- UnMask Payload with XOR of Mask
		for index, maskedByte := range payload {
			unmaskedPayload[index] = maskedByte ^ mask[index%4]
		}
		// --

		// -- Save & Echo UTF8 only
		switch opcode {
		case 1:
			log.Println("Saving the received UTF-8 msg : " + string(unmaskedPayload))
			exec.Command("bash", "-c", "echo \""+string(time.Now().Format(time.ANSIC))+"\n"+string(unmaskedPayload)+"\n\n\" >> applications.txt").Run()
			wsWrite(tcpConn, string(append([]byte("Nice work. Received and saved : "), unmaskedPayload...)))
		case 2:
			log.Println("Binary message received : %v\n", unmaskedPayload)
			wsWrite(tcpConn, "Kudos for uploading a binary WebSocket packet!! Please try again using UTF-8.")
		default:
			log.Println("Opcode not supported : %v\n", opcode)
		}
		// --
	}
}

func wsWrite(c net.Conn, msg string) {
	// -- Convert a string into a single WebSocket frame, and send along TCP
	payload := []byte(msg)
	payloadLength := len(payload) // Max 127 otherwise will screw with MASK bit
	wsFrame := []byte{byte(129), byte(payloadLength)}
	sendBytesOnWire(c, append(wsFrame, payload...))
	// --
}

func sendBytesOnWire(c net.Conn, b []byte) {
	// TODO : error handling
	c.Write(b)
	log.Printf("\n*** Sending data on TCP/IP *** STARTS------------>%s<------------ENDS\n", string(b))
}

func readBytesOnWire(c net.Conn) string {
	// -- TODO : error handling
	messageBuffer := make([]byte, 1024)
	c.Read(messageBuffer)
	log.Printf("\n*** Recieved data on TCP/IP *** STARTS------------>%s<------------ENDS\n", string(messageBuffer))
	return string(messageBuffer)
}
