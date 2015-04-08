#Task

Write a program that hosts a TCP/IP socket that :

1. Provides a simple echo response to incoming connections.
2. Closes the connection if 'quit' is recieved.
3. Accepts multiple connections broadcasting incoming messages to all connections.
5. Emulates a basic webserver (as in previous challenge 06.1.1) to a browser. [No cheating using external HTTP libraries!]
6. Accepts a RFC5455 WebSocket handshake and provides an echo service to a compliant browser client.

*** Notes - See:
Network programming : http://www.beej.us/guide/bgnet/output/print/bgnet_A4.pdf
TCP structure : http://en.wikipedia.org/wiki/Transmission_Control_Protocol#TCP_segment_structure
WebSocket structure : https://tools.ietf.org/html/rfc6455#section-5.2
