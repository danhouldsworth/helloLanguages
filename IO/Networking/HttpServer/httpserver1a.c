#include <stdio.h>      // printf() etc.
#include <stdlib.h>     // exit(), malloc(), atoi()
#include <unistd.h>     // fork() & close()
#include <netinet/in.h> // sockaddr_in, socklen_t
#include <string.h>     // strlen etc

char response[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=utf-8\r\n\r\n<h1>C : Hello, world!</h1>\r\n";
int port        = 8080;

int main() {

        int sock = socket(AF_INET, SOCK_STREAM, 0);
        int one = 1;
        setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int));

        struct sockaddr_in svr_addr;
        svr_addr.sin_family = AF_INET;
        svr_addr.sin_addr.s_addr = INADDR_ANY;
        svr_addr.sin_port = htons(port);

        bind(sock, (struct sockaddr *) &svr_addr, sizeof(svr_addr));
        listen(sock, 1);

        struct sockaddr_in cli_addr;
        socklen_t sin_len = sizeof(cli_addr);
        int client_fd;

        int counter = 0;

        while ((client_fd = accept(sock, (struct sockaddr *) &cli_addr, &sin_len))){
                counter++;
                // -- Server
                printf("\x1b[31mParent%d : accepting the clientID %d\n\x1b[0m", counter, client_fd);
                if (!fork()){
                        printf("\x1b[32mChild%d : closing socket ID %d\x1b[0m\n", counter, sock);
                        close(sock);            // Child doesn't need to listen anymore
                        char b[1000];
                        recv(client_fd, b, 1000, 0);
                        printf("\x1b[32mChild%d : recieved request from clientID %d : \n\x1b[37;2m%s[EOF]\x1b[0m\n", counter, client_fd, b);
                        send(client_fd, response, strlen(response), 0);
                        close(client_fd);
                        printf("\x1b[32mChild%d : closed client connection to ID:%d\n\x1b[0m", counter, client_fd );
                        exit(0);
                }
                close(client_fd);               // Parent doesn't need the client anymore
                printf("\x1b[31mParent%d : closed client connection to ID:%d\n\x1b[0m", counter, client_fd );
                // --
        }
        // --
}
