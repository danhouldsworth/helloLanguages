// Stand-alone Interview WebSocket Page

package main

import (
	"github.com/gorilla/websocket"
	"io"
	"log"
	"net/http"
	"os/exec"
	"time"
)

var (
	staticPage = "<!doctype html><html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"/><title>Careers @ Immerse Learning</title><link href='http://fonts.googleapis.com/css?family=Roboto:400,300,100' rel='stylesheet' type='text/css'></link> <link rel=\"shortcut icon\" href=\"https://s3-eu-west-1.amazonaws.com/keystone-project/will_images/favicon.ico\"><style type=\"text/css\">body{background: #ebebeb;font-family: 'Roboto', sans-serif;}h1{text-align: center;font-size: 36px;font-weight: 300;}p{font-size: 16px;}ol{font-size: 16px;}.roundedContainer{display: block;position: relative;background: #ffffff;width: 60%;margin: 20px auto;border-radius: 10px;padding: 20px 50px;text-align: left; max-width: 800px;}.watermark{display: block;position: relative;width: 40%; min-width: 400px;margin: 20px auto 0 auto;}.socialContainer{display: block; position: relative; width: 60%; margin: 40px auto; text-align: center;}.socialIcons{width: 45px; margin: 0 20px 0 20px;}li{margin-bottom: 5px;}</style></head><body><img class=\"watermark\" src=\"https://s3-eu-west-1.amazonaws.com/keystone-project/will_images/immerse-75.png\"/><div class=\"roundedContainer\"><h1> We're Hiring! </h1><p>At Immerse we are passionate about both results and creativity - and this starts with our search for talent.</p><p>This server is listening for incoming WebSocket connections that are using the modified 24-byte handshake key 'IWillDemonstrateMySkills'. Any data received will be saved as a text file and reviewed.</p><ol><li>If you manage to upload your CV, we will invite you for a face to face interview to further demonstrate your skills.</li><li>Upload a valid <a href=\"http://en.wikipedia.org/wiki/Quine_(computing)\">Quine</a> containing your brief bio, that when executed transmits an exact copy of itself along the WebSocket and you will be invited to spend a whole day with the team, including interviews with the CEO and CTO.</li><li>Find a way to deposit a file 'employ_me.now' containing your contact details and you will immediately be offered a permanent role as a senior developer.</li></ol><p> Good luck! </p></div><div class=\"socialContainer\"> <a href=\"https://vimeo.com/immerselearning\"><img src=\"https://s3-eu-west-1.amazonaws.com/keystone-project/will_images/vimeo.png\"/ class=\"socialIcons\"></a> <a href=\"http://uk.linkedin.com/company/immerse-learning\"><img src=\"https://s3-eu-west-1.amazonaws.com/keystone-project/will_images/linkedin.png\" class=\"socialIcons\"/></a> <a href=\"https://plus.google.com/106802764981985442192/posts\"><img src=\"https://s3-eu-west-1.amazonaws.com/keystone-project/will_images/googleplus.png\" class=\"socialIcons\"/></a> <a href=\"https://twitter.com/ImmerseLearning\" class=\"socialIcons\"><img src=\"https://s3-eu-west-1.amazonaws.com/keystone-project/will_images/twitter.png\" class=\"socialIcons\"/></a> </div></body>"
)

func wsHandler(w http.ResponseWriter, r *http.Request) {

	// -- If not a WebSocket Upgrade then serve Static Page
	if upgradeType, ok := r.Header["Upgrade"]; ok == false {
		log.Printf("Serving HTTP static page to Header : %v\n", r.Header)
		io.WriteString(w, staticPage)
		return

		// Otherwise, check Upgrade type is for WebSocket
	} else if upgradeType[0] == "websocket" {

		// And if a Key is present in the header...
		if customKey, ok := r.Header["Sec-Websocket-Key"]; ok == true {

			// ...but not the Custom Key we requested, then deny & exit
			if customKey[0] != "IWillDemonstrateMySkills" {
				log.Printf("*** WebSocket attempt with invalid key *** : %s\n", customKey[0])
				w.WriteHeader(412)
				return
				// ...otherwise accept
			} else {
				log.Printf("*** WebSocket accepted with custom key *** : %s\n", customKey[0])
			}
			// --

			// -- In the unlikely event the ask for websocket upgrade with no key...
		} else {
			log.Printf("*** WebSocket upgrade with no Key???? *** : %v\n", r.Header)
			return
		}
		// --

		// -- Upgrade to WebSocket
		conn, err := websocket.Upgrade(w, r, nil, 1024, 1024)
		if err != nil {
			log.Printf("*** Failed WebSocket Upgrade *** : %s\n", err)
			return
		}
		defer conn.Close()
		// --

		// -- Save & Echo UTF-8 WebSocket messages
		for {
			log.Println("Listening for messages on live WebSocket")
			messageType, msg, err := conn.ReadMessage()
			if err != nil {
				log.Printf("*** WebSocket Connection Closed *** : %s\n", err)
				return
			}
			if messageType == websocket.TextMessage {
				log.Println("Saving the received UTF-8 msg : " + string(msg))
				exec.Command("bash", "-c", "echo \""+string(time.Now().Format(time.ANSIC))+"\n"+string(msg)+"\n\n\" >> applications.txt").Run()
				conn.WriteMessage(websocket.TextMessage, append([]byte("Nice work. Received and saved : "), msg...))

			} else if messageType == websocket.BinaryMessage {
				log.Println("Binary message received : %v\n", msg)
				conn.WriteMessage(websocket.TextMessage, []byte("Kudos for uploading a binary WebSocket packet!! Please try again using UTF-8."))
			} else {
				log.Println("WebSocket of unknown type received : %v\n", messageType)
			}
		}
		// --

		// -- Don't serve Upgrade for another type
	} else {
		log.Printf("*** Invalid Socket Upgrade Request! *** : %s", upgradeType)
		io.WriteString(w, "<h1>Invalid Socket Upgrade Request!</h1>")
	}
	// --
}

func main() {
	log.Printf("Interview Page : Listening on port 8080...\n")
	http.HandleFunc("/", wsHandler)
	http.ListenAndServe(":8080", nil)
}
