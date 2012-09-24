#ifndef SERVER_H
#define SERVER_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define PORT "12000"
#define BACKLOG 5

struct addrinfo connInfo, *srvInfo, *pInfo;
struct sockaddr_storage cStor;
int sock, client_sock;
socklen_t cStorlen;

#endif
