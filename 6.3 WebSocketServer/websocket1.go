// 1. Done

// To run must set $GOPATH
// for more details on packages see here: http://golang.org/doc/code.html
package main

import (
    "github.com/gorilla/websocket"
    "log"
    "net/http"
)

func wsHandler(w http.ResponseWriter, r *http.Request) {
    // Upgrade http connection to websocket connection
    conn, err := websocket.Upgrade(w, r, nil, 1024, 1024)
    if err != nil {
        log.Println(err)
        return
    }
    // If the for loop should exit, close the connection
    // For more info on why this is here instead of at
    // the end of the function see: http://blog.golang.org/defer-panic-and-recover
    defer conn.Close()

    for {
        messageType, msg, err := conn.ReadMessage()
        if err != nil {
            return
        }

        // Print the message they have just sent to us
        log.Println(string(msg))

        // Print the message type, todo: not working well
        log.Println(string(messageType))

        //Send the message back to them
        if err = conn.WriteMessage(websocket.TextMessage, msg); err != nil {
            return
        }
    }
}

func main() {
    http.Handle("/", http.StripPrefix("/", http.FileServer(http.Dir("."))))
    http.HandleFunc("/ws", wsHandler)
    http.ListenAndServe(":8080", nil)
}
