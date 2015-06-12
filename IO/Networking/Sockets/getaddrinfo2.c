/*
 * getaddrinfo.c - Simple example of using getaddrinfo(3) function.
 *
 * Michal Ludvig <michal@logix.cz> (c) 2002, 2003
 * http://www.logix.cz/michal/devel/
 *
 * License: public domain.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int lookup_host (const char *PORT) {
  struct addrinfo hints, *res;
  int errcode;
  char myIP4addr[INET_ADDRSTRLEN];
  void *ptr;

  memset (&hints, 0, sizeof (hints));
  hints.ai_family   = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags    = AI_PASSIVE | AI_CANONNAME;

  getaddrinfo (NULL, PORT, &hints, &res);

  while(res){
      ptr = &((struct sockaddr_in *) res->ai_addr)->sin_addr;
      inet_ntop (res->ai_family, ptr, myIP4addr, INET_ADDRSTRLEN);
      printf ("IPv4 address: %s (%s)\n", myIP4addr, res->ai_canonname);
      res = res->ai_next;
  }

  return 0;
}

int main(int argc, char *argv[]) {
  printf ("PORT: %s\n", argv[1]);
  return lookup_host(argv[1]);
}
