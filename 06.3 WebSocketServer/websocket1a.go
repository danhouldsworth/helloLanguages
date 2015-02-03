// 1. Done (Stripped error handling and file serving)

package main

import (
	"github.com/gorilla/websocket"
	"log"
	"net/http"
)

func wsHandler(w http.ResponseWriter, r *http.Request) {
	conn, _ := websocket.Upgrade(w, r, nil, 1024, 1024)
	defer conn.Close()
	for {
		_, msg, _ := conn.ReadMessage()
		log.Print(string(msg))
		conn.WriteMessage(websocket.TextMessage, msg)
	}
}

func main() {
	http.HandleFunc("/ws", wsHandler)
	http.ListenAndServe(":8000", nil)
}
