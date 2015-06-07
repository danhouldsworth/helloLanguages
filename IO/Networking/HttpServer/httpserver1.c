// 1. Done.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <err.h>

#include <time.h>

char response[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=utf-8\r\n\r\n<h1>C : Hello, world!</h1><h1>C : Hello, world!</h1><h1>C : Hello, world!</h1><h1>C : Hello, world!</h1><h1>C : Hello, world!</h1><h1>C : Hello, world!</h1><h1>C : Hello, world!</h1><h1>C : Hello, world!</h1><h1>C : Hello, world!</h1><h1>C : Hello, world!</h1>\r\n";

int main()
{
  int one = 1, client_fd;
  struct sockaddr_in svr_addr, cli_addr;
  socklen_t sin_len = sizeof(cli_addr);

  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0)
    err(1, "can't open socket");

  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int));

  int port = 8888;
  svr_addr.sin_family = AF_INET;
  svr_addr.sin_addr.s_addr = INADDR_ANY;
  svr_addr.sin_port = htons(port);

  if (bind(sock, (struct sockaddr *) &svr_addr, sizeof(svr_addr)) == -1) {
    close(sock);
    err(1, "Can't bind");
  }

  listen(sock, 5);
  // while (1) {
    client_fd = accept(sock, (struct sockaddr *) &cli_addr, &sin_len);
    printf("Got connection...\n");

    if (client_fd == -1) {
      perror("Can't accept");
      // continue;
    }

    send(client_fd, response, sizeof(response), 0); /*-1:'\0'*/
    printf("Writing response...\n%s\n", response);
    // -- Socket closing before response finished
    // int delay = 0;
    // while (delay++<100000);
    // printf("Closing connection after delay of %d empty loops.\n", delay);
    // --
    close(client_fd);
  // }
}
