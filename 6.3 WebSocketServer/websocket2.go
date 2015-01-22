// 2. Done

package main

import (
    "github.com/gorilla/websocket"
    "log"
    "net/http"
)

var connections map[*websocket.Conn]bool

func sendAll(msg []byte) {
    for conn := range connections {
        if err := conn.WriteMessage(websocket.TextMessage, msg); err != nil {
            delete(connections, conn)
            conn.Close()
        }
    }
}

func wsHandler(w http.ResponseWriter, r *http.Request) {
    // Upgrade http connection to websocket connection
    conn, err := websocket.Upgrade(w, r, nil, 1024, 1024)
    if err != nil {
        log.Println(err)
        return
    }

    // Add this connection to the list of connections
    connections[conn] = true
    log.Println(connections)

    for {
        messageType, msg, err := conn.ReadMessage()
        if err != nil {
            delete(connections, conn)
            conn.Close()
            return
        }

        // Print the message they have just sent to us
        log.Println(string(msg))

        // Print the message type, todo: not working well
        log.Println(string(messageType))

        // Send message to all other connected clients
        sendAll(msg)
    }
}

func main() {
    connections = make(map[*websocket.Conn]bool)

    http.Handle("/", http.StripPrefix("/", http.FileServer(http.Dir("."))))
    http.HandleFunc("/ws", wsHandler)
    http.ListenAndServe(":8080", nil)
}
