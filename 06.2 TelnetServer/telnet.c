// 1. Done

#include <unistd.h>
#include <netinet/in.h>

int main()
{
  char buffer[] = "";
  int one = 1, client_fd;
  struct sockaddr_in svr_addr, cli_addr;
  socklen_t sin_len = sizeof(cli_addr);

  int sock = socket(AF_INET, SOCK_STREAM, 0);
  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int));

  svr_addr.sin_family = AF_INET;
  svr_addr.sin_addr.s_addr = INADDR_ANY;
  svr_addr.sin_port = htons(8888);
  bind(sock, (struct sockaddr *) &svr_addr, sizeof(svr_addr));
  listen(sock, 5);

  while (1) {
    client_fd = accept(sock, (struct sockaddr *) &cli_addr, &sin_len);
    buffer[0] = 0;

    while (buffer[0] != '!'){ // Terminate with !
      read(client_fd, buffer, 1);
      write(client_fd, buffer, 1);
    }

    close(client_fd);
  }
}
