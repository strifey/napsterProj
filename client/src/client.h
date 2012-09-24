#ifndef CLIENT_H
#define CLIENT_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define PORT "12000"

char *IP;
struct addrinfo connInfo;
struct addrinfo *srvInfo;
int sock;

#endif
