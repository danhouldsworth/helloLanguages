/*
'GUIsocket.c' - A library to serve and connect to a browser front end, while exposing an API to send graphical commands.
Usage           : Include this file and then invoke the API commands below to manipulate the GUI display.
Weakness        : i) Manually hardcoding the served file lengths. Abort trap if forget.
                : ii) accept() and recv() are BLOCKING. A mis behaving browser, could easily clog it.
                : Chrome seems to request /favicon before the WS in full screen (non-console mode). NOT FOR PRODUCTION USE.
Dependancies    : Only standard string functions that we could easily hand roll. The hard work is already done.
Memory          : Pretty sure temporary stack only. Not certain about the literals and whether in ProgMem, but minor size / use.
Elegance        : Yes. Useful, self explanatory functions for sending headers, strings, binaries. GUI API clear and extendable.
*/

#include <string.h>             // strlen(), and strstr() etc
#include "listenTCP.c"
#include "acceptWebSocket.c"

// -- Setting declarations
#define MAX_RECV_BUFFER 1000
// --

// -- Functions
void serveGET(int recv_len, char *recvBuff);
void acceptWebSocket(char *recvBuff);
void responseSendStr(unsigned char *responseChunk);
void responseSendBin(unsigned char *responseBuffer, int length);
void responseSendHdr(char *headerLiteral);
unsigned char lowByte(int i);
unsigned char hiByte(int i);
// --

int socket_fd, client_fd; // Need this in the global namespace

//
// -- Expose runtime API
void guiWipe() { // Effectively used to start
        unsigned char wsFrame = 1*128 + 1*2; // FIN bit & Binary Type
        unsigned char wsPayloadLen = 1;      // 0 guiData bytes + 1 guiCmd byte
        unsigned char guiCmd = 0 + (1<<3);   // guiCmd code 0(of 0-7) + single guiPacket
        unsigned char wsPacket[] = {wsFrame, wsPayloadLen, guiCmd};
        responseSendBin(wsPacket , 3);
}
void guiPlot(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
        unsigned char wsFrame = 1*128 + 1*2; // FIN bit & Binary Type
        unsigned char wsPayloadLen = 9;      // 8 guiData bytes + 1 guiCmd byte
        unsigned char guiCmd = 2 + (1<<3);   // guiCmd code 2(of 0-7) + single guiPacket
        unsigned char wsPacket[] = {wsFrame, wsPayloadLen, guiCmd, hiByte(x), lowByte(x), hiByte(y), lowByte(y), r, g, b, a};
        responseSendBin(wsPacket , 11);
}
void guiFillRect(int x, int y, int w, int h, unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
        unsigned char wsFrame = 1*128 + 1*2;  // FIN bit & Binary Type
        unsigned char wsPayloadLen = 13;      // 12 guiData bytes + 1 guiCmd byte
        unsigned char guiCmd = 4 + (1<<3);    // guiCmd code 4(of 0-7) + single guiPacket
        unsigned char wsPacket[] = {wsFrame, wsPayloadLen, guiCmd, hiByte(x), lowByte(x), hiByte(y), lowByte(y), hiByte(w), lowByte(w), hiByte(h), lowByte(h), r, g, b, a};
        responseSendBin(wsPacket , 15);
}
void closeGUIsocket(){
        unsigned char wsFrame = 1*128 + 1*2;  // FIN bit & Binary Type
        unsigned char wsPayloadLen = 1;       // 0 guiData bytes + 1 guiCmd byte
        unsigned char guiCmd = 7 + (1<<3);    // guiCmd code 7(of 0-7) + single guiPacket
        unsigned char wsPacket[] = {wsFrame, wsPayloadLen, guiCmd};
        responseSendBin(wsPacket , 3);
        close(client_fd);
        close(socket_fd);
}
// --


unsigned char lowByte(int i) {
        return (unsigned char)(i & 0x00ff);
}

unsigned char hiByte(int i) {
        return (unsigned char)((i & 0xff00) >> 8);
}


void initGUIsocket() {

        socket_fd = listenTCP("8080");

        // -- Create a client addr struct and (blocking) accept next client connection
        struct sockaddr_storage client_addr;            // IP4 & IP6 capable client address
        socklen_t addr_size = sizeof client_addr;
        int recv_len;
        char recvBuff[MAX_RECV_BUFFER];
        // --

        while ((client_fd = accept(socket_fd, (struct sockaddr *)&client_addr, &addr_size)) != -1){
                printf("Processing an accept()ed client connection...");
                memset(recvBuff, 0, MAX_RECV_BUFFER);

                // -- Wait for client to send request then decide between HTTP and WebSocket accept
                if ((recv_len = recv(client_fd, recvBuff, MAX_RECV_BUFFER, 0)) != 0){
                        if (strstr(recvBuff, "Connection: Upgrade")) {
                                acceptWebSocket(recvBuff);
                                return;
                        }
                        else serveGET(recv_len, recvBuff);
                }
                close(client_fd);
                // --
        }
        // -- error with accept()
        close(socket_fd);
        exit(1);
        // --
}

void acceptWebSocket(char *recvBuff){
        unsigned char *clientKey = (unsigned char*)strstr(recvBuff, "Sec-WebSocket-Key: ") + 19;
        unsigned char acceptKeyStr[28+1];

        responseSendHdr("HTTP/1.1 101 Switching Protocols");
        responseSendHdr("Upgrade: websocket");
        responseSendHdr("Connection: Upgrade");
        responseSendHdr("Sec-WebSocket-Protocol: guiSocket-protocol");
        responseSendStr((unsigned char*)"Sec-WebSocket-Accept: ");
        responseSendStr(createAcceptKeyStr(acceptKeyStr, (unsigned char*)clientKey));
        responseSendHdr("\r\n");
        printf("Accepted WS Handshake\n");
}

void serveGET(int recv_len, char *recvBuff){

        if (strstr(recvBuff, "GET / ") == recvBuff){
                unsigned char indexHTML[4669]; // !! Must increase this if extend GUIdisplay.html
                unsigned char *fp = indexHTML;
                FILE *ch = fopen("GUIdisplay.html", "r");
                while( (*fp++ = fgetc(ch)) != (unsigned char)EOF);
                *(--fp) = 0; // Terminate the string rather than send EOF === -1

                responseSendHdr("HTTP/1.0 200 OK");
                responseSendHdr("Content-Type: text/html; charset=utf-8");
                responseSendHdr("\r\n");
                responseSendStr(indexHTML);
                printf("Served GET / request\n");
        }
        else if (strstr(recvBuff, "GET /favicon") == recvBuff){ // Just to keep Chrome playing nice
                responseSendHdr("HTTP/1.0 200 OK");
                responseSendHdr("Content-Type: image/png");
                responseSendHdr("Content-Length: 1");
                responseSendHdr("\r\n");
                responseSendBin(0, 1);
                printf("Served [fake] GET /favicon request\n");
        }
        else {
                responseSendHdr("HTTP/1.0 404 Not Found");
                responseSendHdr("\r\n");
                responseSendHdr("Investigate if you see this.");
                printf("Served 404 to request recv_len = %d: ->%s<-\n", recv_len, recvBuff);
        }

}
void responseSendStr(unsigned char *responseChunk){
        // Note : this relies on detecting the length of a response as if a string
        // Hence it will fail (erroneously shorten response chunk) if you want to send
        // binary containing 0's
        send(client_fd, responseChunk,  strlen((char *)responseChunk),  0);
}

void responseSendHdr(char *headerLiteral){
        send(client_fd, (unsigned char*) headerLiteral, strlen(headerLiteral),  0);
        send(client_fd, (unsigned char*) "\r\n", 2, 0);
}

void responseSendBin(unsigned char *responseBuffer, int length){
        // Note : this will only send length bytes of the binary responseBuffer
        send(client_fd, responseBuffer,  length,  0);
}
