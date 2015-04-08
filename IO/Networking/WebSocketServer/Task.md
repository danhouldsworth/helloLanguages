#Task

1. Accept a single WebSocket client connection, provide an echo response for data recieved.
2. Accept unlimited number of connections, broadcasting all incoming messages to all others.
3. Accept two client connections per room, providing a relay between the two.

Bonus : Establish a message protocol of {'command', 'message'}, where command can either be sendToID, or sendToAll.

** Notes :
Specification          : https://tools.ietf.org/html/rfc6455
HTTP upgrade handshake : https://en.wikipedia.org/wiki/WebSocket#WebSocket_protocol_handshake
WebSocket Frame Bytes  : http://stackoverflow.com/questions/8125507/how-can-i-send-and-receive-websocket-messages-on-the-server-side
