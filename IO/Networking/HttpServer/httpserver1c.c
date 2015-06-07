// !!! Still need to reap zombie child processes !!!

#include <stdio.h>      // printf() etc.
#include <stdlib.h>     // exit(), malloc(), atoi()
#include <unistd.h>     // fork() & close()
#include <string.h>     // strlen etc
// #include <sys/types.h>
// #include <sys/socket.h>
#include <netinet/in.h> // sockaddr_in, socklen_t
#include <netdb.h>      // getaddrinfo() etc
#include <openssl/sha.h>// OS X has deprecated this so need to compile wiht -Wno-deprecated-declarations -lcrypto

// char response[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html;\r\n\r\n<img src='http://i.imgur.com/HrxE1Oi.png'>\n<script>\nvar ws = new WebSocket('ws://127.0.0.1:8080/');\n</script>\r\n";
char response[]      = "HTTP/1.1 200 OK\r\nContent-Type: text/html;\r\n\r\n<img src='http://i.imgur.com/HrxE1Oi.png'>\n<script>\nvar ws = new WebSocket('ws://10.0.1.8:8080/');\n</script>\r\n";
char acceptUpgrade[] = "HTTP/1.1 101 Switching Protocols\r\nUpgrade: websocket\r\nConnection: Upgrade\r\nSec-WebSocket-Accept: ";
char custom_response[1000];

#define MYPORT "8080"
#define BACKLOG 10
#define MAX_RECV_BUFFER 1000

// -- declarations
void processGET(int client_fd, int counter, int recv_len, char *recvBuff);
int isUpgrade(char *recvBuff, int recv_len);
void processWS(int client_fd, char *recvBuff);
void getFourBytesFromThree(unsigned char *src, unsigned char *m, unsigned char *four);
unsigned char *base64(unsigned char *inputMsg, unsigned char *outputMsgBuf);
// --

int main(void) {

        // -- Set minimal hints and store our address info in server_info
        struct addrinfo hints, *server_info, *p;
        memset(&hints, 0, sizeof hints);
        hints.ai_family         = AF_UNSPEC;            // IP4 & IP6 capable server address
        hints.ai_socktype       = SOCK_STREAM;          // TCP
        hints.ai_flags          = AI_PASSIVE;           // Fill in our IP for us
        getaddrinfo(NULL, MYPORT, &hints, &server_info);
        // --

        // -- Use this info to get a socket file descripter, and bind to it
        int socket_fd, yes = 1;
        for (p = server_info; p != NULL; p = p->ai_next){
                printf("Looking at server socket...\n");
                if ((socket_fd = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol)) == -1){
                        perror("socket");
                        continue;
                }
                if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof (int)) == -1){
                        perror("setsockopt");
                        exit(1);
                }
                if (bind(socket_fd, server_info->ai_addr, server_info->ai_addrlen) == -1){
                        close(socket_fd);
                        perror("bind");
                        continue;
                } else break;
        }
        if (p == NULL){
                printf("Failed to bind.\n");
                exit(1);
        }
        freeaddrinfo(server_info);
        // -- We now have a file descriptor socket_fd that is correctly bound to our server address & port


        if (listen(socket_fd, BACKLOG) == -1){
                perror("listen");
                exit(1);
        }
        printf("Listening for connections...\n");

        // -- Create a client addr struct and (blocking) accept next client connection
        struct sockaddr_storage client_addr;            // IP4 & IP6 capable client address
        socklen_t addr_size = sizeof client_addr;
        int client_fd, recv_len, counter = 0;
        char recvBuff[MAX_RECV_BUFFER];
        // --

        while ((client_fd = accept(socket_fd, (struct sockaddr *)&client_addr, &addr_size)) != -1){
                // printf("\x1b[31mParent Thread : accepting the client attempt #%d on file descriptor #%d\n\x1b[0m", counter, client_fd);
                if (!fork()){
                        close(socket_fd);
                        // -- Wait for client to send a byte then send our default response and close the client
                        recv_len = recv(client_fd, recvBuff, MAX_RECV_BUFFER, 0);
                        // if (isUpgrade(recvBuff, recv_len) == 1) processWS(recvBuff);
                        if (strstr(recvBuff, "Connection: Upgrade")) processWS(client_fd, recvBuff);
                        else processGET(client_fd, counter, recv_len, recvBuff);

                        close(client_fd);
                        // --
                        // printf("\x1b[32mChild Thread #%d: Served site & closed client connection to clientID:%d. Now terminating...\n\x1b[0m", counter, client_fd );
                        exit(0);
                }
                counter++;
                close(client_fd);
                // printf("\x1b[31mParent Thread : closed client connection #%d to clientID:%d\n\x1b[0m", counter++, client_fd );
        }

        // -- close the socket and exit
        close(socket_fd);
        return 0;
        // --
}
void processWS(int client_fd, char *recvBuff){
        unsigned char clientKey[24+1+36];
        printf("UPGRADE HEADER RECIEVED!!\n");
        memcpy(clientKey, 19+strstr(recvBuff, "Sec-WebSocket-Key: "), 24);
        printf("Client Key = -->%s<--\n", clientKey);
        memcpy(clientKey+24, "258EAFA5-E914-47DA-95CA-C5AB0DC85B11", 36);
        printf("MagicKey: -->%s<--\n", clientKey);
        unsigned char hash[20];
        SHA1(clientKey, 60, hash);
        printf("MagicKey Hashed: "); for (int i = 0; i < 20; i++) printf("%x ", hash[i]);
        unsigned char b64buff[28];
        printf("\nSec-WebSocket-Accept: -->%s<--\n", base64(hash, b64buff));
        send(client_fd, acceptUpgrade, strlen(acceptUpgrade), 0);
        send(client_fd, b64buff, 28, 0);
        send(client_fd, "\r\n\r\n", 4, 0);
}

void processGET(int client_fd, int counter, int recv_len, char *recvBuff){

        printf("Serving GET request!\n");
        // printf("\x1b[32mChild Thread #%d: recieved request of length %d from clientID %d : \n\x1b[37;2m%s[EOF]\x1b[0m\n", counter, recv_len, client_fd, recvBuff);
        send(client_fd, response, strlen(response), 0);
        memset(custom_response, 0, 1000);
        sprintf(custom_response, "<h1>I am a spawned server - you are my first, and last ever client!</h1><h1>But you are client #%d of my parent :-)</h1><h2>I will now quietly terminate myself, while my parent thread continues listening for connections...</h2>", counter);
        send(client_fd, custom_response, strlen(custom_response), 0);
}
void getFourBytesFromThree(unsigned char *src, unsigned char *m, unsigned char *four) {

        // -- Get first 3 chars of string (Padded with 0 where empty)
        unsigned int stringLength = strlen((char *)src);
        unsigned char three[3];
        switch (stringLength) {
        case 1:
                three[0] = src[0];
                three[1] = 0;
                three[2] = 0;
        case 2:
                three[0] = src[0];
                three[1] = src[1];
                three[2] = 0;
        default:
                three[0] = src[0];
                three[1] = src[1];
                three[2] = src[2];
        }
        // --

        // -- Create bitmask to convert 3xOctets to 4xSextets
        unsigned char bitMask[] = {
                0b11111100,
                0b00000011,
                0b11110000,
                0b00001111,
                0b11000000,
                0b00111111
        };

        four[0]  = (three[0] & bitMask[0]) >> 2;                // Amusingly <<>> have higher precidence then & in C than Go
        four[1]  = (three[0] & bitMask[1]) << 4;
        four[1] += (three[1] & bitMask[2]) >> 4;
        four[2]  = (three[1] & bitMask[3]) << 2;
        four[2] += (three[2] & bitMask[4]) >> 6;
        four[3]  = (three[2] & bitMask[5]);
        // --

        // -- Encode into base64 using 4 Sextets as indices
        four[0] = m[four[0]];
        four[1] = m[four[1]];
        four[2] = m[four[2]];
        four[3] = m[four[3]];
        // --

        // -- Pad out if shorter than 3 bytes to this block
        switch (stringLength) {
        case 1:
                four[2] = '=';
                four[3] = '=';
        case 2:
                four[3] = '=';
        }
        // --
}

unsigned char *base64(unsigned char *inputMsg, unsigned char *outputMsgBuf){

        unsigned char mapPtr[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"; // Std encoding OR unsigned char m[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_"; // URL encoding
        unsigned char *buf4 = (unsigned char *)malloc(4);

        int i = 0;
        int j = 0;

        while (i < strlen((char *)inputMsg)){
                getFourBytesFromThree((inputMsg+i), mapPtr, buf4);
                outputMsgBuf[j + 0] = buf4[0];
                outputMsgBuf[j + 1] = buf4[1];
                outputMsgBuf[j + 2] = buf4[2];
                outputMsgBuf[j + 3] = buf4[3];
                i += 3;
                j += 4;
        }

        free(buf4);
        return outputMsgBuf;
}
