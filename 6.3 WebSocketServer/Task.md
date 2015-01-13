#Task

1. Accept a single WebSocket client connection, provide an echo response for data recieved.
2. Accept two client connections, providing a relay between the two.
3. Accept unlimited number of connections, broadcasting all incoming messages to all others.

Bonus : Establish a message protocol of {'command', 'message'}, where command can either be sendToID, or sendToAll.
