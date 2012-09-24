#ifndef CLIENT_H
#define CLIENT_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define PORT "12001"
#define MAXBUFF 100

char *IP;
struct addrinfo connInfo, *srvInfo, *pInfo;
int sock;
char buff[MAXBUFF];

#endif
