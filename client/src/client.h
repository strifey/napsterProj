#ifndef CLIENT_H
#define CLIENT_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define PORT "12000"
#define MAXBUFF 100

typedef enum _type{LIST,ADD, NONE} commType;
commType client_comm = NONE;
char *IP;
struct addrinfo connInfo, *srvInfo, *pInfo;
int sock;
char buff[MAXBUFF];

#endif
