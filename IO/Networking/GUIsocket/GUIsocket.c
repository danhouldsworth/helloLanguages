/*
'GUIsocket.c' - A library to serve and connect to a browser front end, while exposing an API to send graphical commands.
Usage           : Include this file and then invoke the API commands below to manipulate the GUI display.
Weakness        : i) Manually hardcoding the served file lengths. Abort trap if forget.
                : ii) accept() and recv() are BLOCKING. A mis behaving browser, could easily clog it.
                : Chrome seems to request /favicon before the WS in full screen (non-console mode). NOT FOR PRODUCTION USE.
                : TODO - split basic file server on one process & port, and WebSocket server on seperate process & port
Dependancies    : Only standard string functions that we could easily hand roll. The hard work is already done. [Edit: and now the signal.h for kill]
Memory          : Pretty sure temporary stack only. Not certain about the literals and whether in ProgMem, but minor size / use.
Elegance        : Yes. Useful, self explanatory functions for sending headers, strings, binaries. GUI API clear and extendable.
*/

#include <string.h>             // strlen(), and strstr() etc
#include <signal.h>
#include "listenTCP.c"
#include "acceptWebSocket.c"

// -- Setting declarations
#define MAX_RECV_BUFFER 1000
#define PACKETS_PER_FRAME 31 // Min 16 while we use 16bit multipayload
#define WS_HEADER_BYTES 4    // FIN+OPCODE / PAYLOAD TYPE / 16bit PAYLOAD
#define GUI_HEADER_BYTES 1
#define GUI_OPCODE_WIPE 0
#define GUI_OPCODE_PLOT 2
#define GUI_OPCODE_RECT 4
#define GUI_OPCODE_STOP 7
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

int socket_fd, client_fd; // Put these in the global namespace
unsigned char guiPlotQueue[PACKETS_PER_FRAME * 8 + WS_HEADER_BYTES + GUI_HEADER_BYTES];
unsigned char guiRectQueue[PACKETS_PER_FRAME * 12 + WS_HEADER_BYTES + GUI_HEADER_BYTES];
unsigned char *ptrPlotQue = guiPlotQueue + WS_HEADER_BYTES + GUI_HEADER_BYTES;
unsigned char *ptrRectQue = guiRectQueue + WS_HEADER_BYTES + GUI_HEADER_BYTES;
//
// -- Expose runtime API
void closeGUIsocket();
void guiWipe() { // Effectively used to start
        unsigned char wsFrame = 1*128 + 1*2; // FIN bit & Binary Type
        unsigned char wsPayloadLen = 0+1;      // 0 guiData bytes + 1 guiCmd byte
        unsigned char guiCmd = GUI_OPCODE_WIPE + (1<<3);   // guiCmd code 0(of 0-7) + single guiPacket
        unsigned char wsPacket[] = {wsFrame, wsPayloadLen, guiCmd};
        responseSendBin(wsPacket , 3);
}
void guiPlot(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
        unsigned char wsFrame = 1*128 + 1*2; // FIN bit & Binary Type
        unsigned char wsPayloadLen = 8+1;      // 8 guiData bytes + 1 guiCmd byte
        unsigned char guiCmd = GUI_OPCODE_PLOT + (1<<3);   // guiCmd code 2(of 0-7) + single guiPacket
        unsigned char wsPacket[] = {wsFrame, wsPayloadLen, guiCmd, hiByte(x), lowByte(x), hiByte(y), lowByte(y), r, g, b, a};
        responseSendBin(wsPacket , 11);
}
void guiPlotFlush() {
        unsigned char wsFrame = 1*128 + 1*2; // FIN bit & Binary Type
        unsigned char exendedPayload = 126;  // Signals that next 16bits will define payload length
        int wsPayloadLen = 8 * PACKETS_PER_FRAME + GUI_HEADER_BYTES;      // 8 guiData bytes + 1 guiCmd byte
        unsigned char guiCmd = GUI_OPCODE_PLOT + (PACKETS_PER_FRAME << 3);   // guiCmd code 2(of 0-7) + single guiPacket
        guiPlotQueue[0] = wsFrame;
        guiPlotQueue[1] = exendedPayload;
        guiPlotQueue[2] = hiByte(wsPayloadLen);
        guiPlotQueue[3] = lowByte(wsPayloadLen);
        guiPlotQueue[4] = guiCmd;
        responseSendBin(guiPlotQueue , WS_HEADER_BYTES + wsPayloadLen);
}
void guiPlotBuff(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
        *ptrPlotQue++ = hiByte(x);
        *ptrPlotQue++ = lowByte(x);
        *ptrPlotQue++ = hiByte(y);
        *ptrPlotQue++ = lowByte(y);
        *ptrPlotQue++ = r;
        *ptrPlotQue++ = g;
        *ptrPlotQue++ = b;
        *ptrPlotQue++ = a;
        if (ptrPlotQue >= guiPlotQueue + 8 * PACKETS_PER_FRAME){
                ptrPlotQue = guiPlotQueue + WS_HEADER_BYTES + GUI_HEADER_BYTES;
                guiPlotFlush();
        }
}
void guiFillRect(int x, int y, int w, int h, unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
        unsigned char wsFrame = 1*128 + 1*2;  // FIN bit & Binary Type
        unsigned char wsPayloadLen = 12+1;      // 12 guiData bytes + 1 guiCmd byte
        unsigned char guiCmd = GUI_OPCODE_RECT + (1<<3);    // guiCmd code 4(of 0-7) + single guiPacket
        unsigned char wsPacket[] = {wsFrame, wsPayloadLen, guiCmd, hiByte(x), lowByte(x), hiByte(y), lowByte(y), hiByte(w), lowByte(w), hiByte(h), lowByte(h), r, g, b, a};
        responseSendBin(wsPacket , 15);
}
void guiRectFlush() {
        unsigned char wsFrame = 1*128 + 1*2; // FIN bit & Binary Type
        unsigned char exendedPayload = 126;  // Signals that next 16bits will define payload length
        int wsPayloadLen = 12 * PACKETS_PER_FRAME + GUI_HEADER_BYTES;      // 8 guiData bytes + 1 guiCmd byte
        unsigned char guiCmd = GUI_OPCODE_RECT + (PACKETS_PER_FRAME << 3);   // guiCmd code 2(of 0-7) + single guiPacket
        guiRectQueue[0] = wsFrame;
        guiRectQueue[1] = exendedPayload;
        guiRectQueue[2] = hiByte(wsPayloadLen);
        guiRectQueue[3] = lowByte(wsPayloadLen);
        guiRectQueue[4] = guiCmd;
        responseSendBin(guiRectQueue , WS_HEADER_BYTES + wsPayloadLen);
}
void guiFillRectBuff(int x, int y, int w, int h, unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
        *ptrRectQue++ = hiByte(x);
        *ptrRectQue++ = lowByte(x);
        *ptrRectQue++ = hiByte(y);
        *ptrRectQue++ = lowByte(y);
        *ptrRectQue++ = hiByte(w);
        *ptrRectQue++ = lowByte(w);
        *ptrRectQue++ = hiByte(h);
        *ptrRectQue++ = lowByte(h);
        *ptrRectQue++ = r;
        *ptrRectQue++ = g;
        *ptrRectQue++ = b;
        *ptrRectQue++ = a;
        if (ptrRectQue >= guiRectQueue + 12 * PACKETS_PER_FRAME){
                ptrRectQue = guiRectQueue + WS_HEADER_BYTES + GUI_HEADER_BYTES;
                guiRectFlush();
        }
}
void closeGUIsocket(){
        guiPlotFlush();
        guiRectFlush();
        unsigned char wsFrame = 1*128 + 1*2;  // FIN bit & Binary Type
        unsigned char wsPayloadLen = 0+1;       // 0 guiData bytes + 1 guiCmd byte
        unsigned char guiCmd = 7 + (1<<3);    // guiCmd code 7(of 0-7) + single guiPacket
        unsigned char wsPacket[] = {wsFrame, wsPayloadLen, guiCmd};
        responseSendBin(wsPacket , 3);
        responseSendBin(wsPacket , 3);        // Send a spare just to be sure
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

        // -- Create a client addr struct and (blocking) accept next client connection
        struct sockaddr_storage client_addr;            // IP4 & IP6 capable client address
        socklen_t addr_size = sizeof client_addr;
        int recv_len;
        pid_t child_pid;
        char recvBuff[MAX_RECV_BUFFER];
        // --

        if ((child_pid = fork()) == 0){ // Child process

                socket_fd = listenTCP("8080"); // PORT for GET

                // Continue to serve (albeit in a blocking fashion)
                while ((client_fd = accept(socket_fd, (struct sockaddr *)&client_addr, &addr_size)) != -1){
                        printf("P_ID %d : Processing an accept()ed client connection...", getpid());
                        memset(recvBuff, 0, MAX_RECV_BUFFER);
                        // -- Wait for client to send request then serve HTTP
                        if ((recv_len = recv(client_fd, recvBuff, MAX_RECV_BUFFER, 0)) != 0) serveGET(recv_len, recvBuff);
                        close(client_fd);
                        // --
                }
                printf("P_ID %d : Browser not playing nice with socket :-(\nClosing HTTP process...", getpid());
        } else { // Parent process

                socket_fd = listenTCP("8081"); // PORT for WS

                // Single Use for GUIsocket
                if ((client_fd = accept(socket_fd, (struct sockaddr *)&client_addr, &addr_size)) != -1){
                        printf("P_ID %d : Processing an accept()ed client connection...", getpid());
                        memset(recvBuff, 0, MAX_RECV_BUFFER);
                        // -- Wait for client to send request then decide between HTTP and WebSocket accept
                        recv_len = recv(client_fd, recvBuff, MAX_RECV_BUFFER, 0);
                        acceptWebSocket(recvBuff);
                        printf("Done. GUIsocket is established. Terminating HTTP server process %d.\n", child_pid);
                        kill(child_pid, SIGKILL);
                        return;
                        // --
                }
                printf("Error with WS accept(). Waiting on HTTP child process %d...\n", child_pid);
                int status;
                waitpid(child_pid, &status, 0);
        }

        // [Child can fall through and exit here, while parent WS keeps running.]
        // [Parent arriving here will have waited for Child process to end. Hence no zombie or background processes should remain]
        // -- error with accept().
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
                unsigned char indexHTML[4959]; // !! Must increase this if extend GUIdisplay.html
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
        // Note : this method ignores string terminators and sends length bytes of responseBuffer
        send(client_fd, responseBuffer,  length,  0);
        // printf("WSFrame:-->");
        // for(int i = 0; i < length; i++) printf("%d,", responseBuffer[i]);
        // printf("\b<--\n");
}
