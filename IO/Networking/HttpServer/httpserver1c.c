#include <stdio.h>      // printf() etc.
#include <stdlib.h>     // exit(), malloc(), atoi()
#include <unistd.h>     // fork() & close()
#include <string.h>     // strlen etc
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> // sockaddr_in, socklen_t
#include <netdb.h>

char response[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=utf-8\r\n\r\n<h1>C : Hello, world!</h1>\r\n";
#define MYPORT "8080"
#define BACKLOG 10

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
        int client_fd = accept(socket_fd, (struct sockaddr *)&client_addr, &addr_size);
        // --

        // -- Wait for client to send a byte then send our default response and close the client
        char *b;
        recv(client_fd, b, 1, 0);
        send(client_fd, response, strlen(response), 0);
        close(client_fd);
        // --

        // -- close the socket and exit
        close(socket_fd);
        return 0;
        // --
}
