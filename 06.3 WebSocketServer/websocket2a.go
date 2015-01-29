// 2. Done

package main

import (
	"github.com/gorilla/websocket"
	"log"
	"net/http"
)

var (
	counter     = 0
	connections map[*websocket.Conn]int
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
	conn, _ := websocket.Upgrade(w, r, nil, 1024, 1024)
	ID := counter
	connections[conn] = ID
	counter++

	for {
		_, msg, _ := conn.ReadMessage()
		log.Printf("Recieved from Conn#%d : %s", ID, string(msg))
		sendAll(ID, msg)
	}
}

func main() {
	connections = make(map[*websocket.Conn]int)
	http.HandleFunc("/ws", wsHandler)
	http.ListenAndServe(":8080", nil)
}
