#Task

Write a program that hosts a TCP/IP connection on port 4000 that :

1. Provides a simple echo response to incoming connections.
2. Closes the connection if 'quit' is recieved.
3. Accepts multiple connections broadcasting all messages to all connections.
5. Emulates a basic webserver (as in previous challenge 06.1.1) to a browser. [No cheating using external HTTP libraries!]
6. Accepts a RFC5455 WebSocket handshake and provides an echo service to a browser client.
