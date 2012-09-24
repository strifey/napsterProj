#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define PORT "12000"
#define BACKLOG 15

char *IP;
struct addrinfo connInfo, *srvInfo, *pInfo;
struct sockaddr_storage cStor;
int sock, client_sock;
socklen_t cStorlen = 0;

#endif
