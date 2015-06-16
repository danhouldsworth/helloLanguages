/*
'listenTCP.c' - Tidy away the process of getting, binding, and listening to a socket for TCP connections.
Usage   : Include this file and invoke listenTCP(PORT) and get back the socket file descriptor to send / recieve on

Weakness        : Although good error checking, NOT FOR PRODUCTION USE as will exit on errors.
Dependancies    : See notes below on low level libraries used for system calls
Memory          : Valgrind errors that pointing to uninitialised bytes, but this is a known error with getaddrinfo()
Elegance        : Yes. Clear, standalone, useful and extendable.
*/

#include <stdio.h>      // printf() etc.
#include <stdlib.h>     // exit(), malloc(), atoi()
#include <unistd.h>     // fork() & close()
#include <netinet/in.h> // sockaddr_in, socklen_t
#include <arpa/inet.h>  // inet_ntop() Network to presentation
#include <netdb.h>      // getaddrinfo() etc

#define BACKLOG 10      // The number of client connections that can queue for me to accept()
                        // BACKLOG limited silently by OS to 128.
                        // Does not necessarily reject. If TCP then may ignore, so it retries.

int listenTCP(const char *MYPORT){
        // -- Set minimal hints and store our address info in server_info
        struct addrinfo hints, *server_info, *p;
        memset(&hints, 0, sizeof hints);
        hints.ai_family         = AF_INET;            // IP4 & IP6 capable server address
        hints.ai_socktype       = SOCK_STREAM;          // TCP
        hints.ai_protocol       = IPPROTO_TCP;          // TCP v UDP
        hints.ai_flags          = AI_PASSIVE;           // Fill in our IP for us
        getaddrinfo(NULL, MYPORT, &hints, &server_info);
        // --

        // -- Use this info to get a socket file descripter, and bind to it
        int socket_fd, yes = 1;
        for (p = server_info; p != NULL; p = p->ai_next){
                if ((socket_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1){
                        perror("socket");
                        continue;
                }
                if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof (int)) == -1){
                        perror("setsockopt");
                        exit(1);
                }
                if (bind(socket_fd, p->ai_addr, p->ai_addrlen) == -1){
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
        printf("Process_ID : %d. Listening for connections on %s : ...\n", getpid(), MYPORT);

        return socket_fd;
}
