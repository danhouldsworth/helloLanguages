/*
1. Create a single use telnet echo
2. Fork into a second thread to make it double use..?
*/

// #include <stdio.h>
#include "listenTCP.c"
#include <string.h>

#define MAX_RECV_BUFFER 1000

int main(void){

        // -- Create a client addr struct and (blocking) accept next client connection
        struct sockaddr_storage client_addr;            // IP4 & IP6 capable client address
        socklen_t addr_size = sizeof client_addr;
        int recv_len, client_fd;
        char recvBuff[MAX_RECV_BUFFER];
        memset(recvBuff, 0, MAX_RECV_BUFFER);
        // --

        int socket_fd = listenTCP("8080");

        if ((fork()) == 0){ // CHILD
            client_fd = accept(socket_fd, (struct sockaddr *)&client_addr, &addr_size);
            while ((recv_len = recv(client_fd, recvBuff, MAX_RECV_BUFFER, 0)) != 0){
                printf("Child0 Echoing : %s\n", recvBuff);
                send(client_fd, "Child0:",  8,  0);
                send(client_fd, recvBuff,  recv_len,  0);
            }

        } else if ((fork()) == 0){ // CHILD2
            client_fd = accept(socket_fd, (struct sockaddr *)&client_addr, &addr_size);
            while ((recv_len = recv(client_fd, recvBuff, MAX_RECV_BUFFER, 0)) != 0){
                printf("Child1 Echoing : %s\n", recvBuff);
                send(client_fd, "Child1:",  8,  0);
                send(client_fd, recvBuff,  recv_len,  0);
            }

        } else {                    // PARENT
            client_fd = accept(socket_fd, (struct sockaddr *)&client_addr, &addr_size);
            while ((recv_len = recv(client_fd, recvBuff, MAX_RECV_BUFFER, 0)) != 0){
                printf("Parent Echoing : %s\n", recvBuff);
                send(client_fd, "Parent:",  8,  0);
                send(client_fd, recvBuff,  recv_len,  0);
            }

        }

        close(client_fd);
        close(socket_fd);

        exit(1);
        // --
}
