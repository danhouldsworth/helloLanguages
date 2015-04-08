// 2. Done

package main

import (
	"github.com/gorilla/websocket"
	"log"
	"net/http"
)

var (
	counter                             = 0
	connections map[*websocket.Conn]int = make(map[*websocket.Conn]int)
)

func sendAll(senderID int, msg []byte) {
	for conn := range connections {
		log.Printf("Passing message from Conn#%d to Conn#%d : %s", senderID, connections[conn], string(msg))
		if err := conn.WriteMessage(websocket.TextMessage, msg); err != nil {
			delete(connections, conn)
			conn.Close()
		}
	}
}

func wsHandler(w http.ResponseWriter, r *http.Request) {
	log.Println("*** New WebSocket Connection ***")
	conn, _ := websocket.Upgrade(w, r, nil, 1024, 1024)
	counter++
	connections[conn] = counter

	for {
		_, msg, _ := conn.ReadMessage()
		log.Printf("Recieved from Conn#%d : %s", counter, string(msg))
		sendAll(counter, msg)
	}
}

func main() {
	log.Println("*** Now listening for WebSockets on port 8080 ***")
	http.HandleFunc("/ws", wsHandler)
	http.ListenAndServe(":8080", nil)
}
