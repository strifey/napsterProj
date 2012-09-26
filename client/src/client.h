#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "../../lib/fllist.h"

#define PORT "12001"

typedef enum _type{LIST,ADD, NONE} commType;
commType client_comm = NONE;
char ans, *ip, *port, *file_in;
struct addrinfo connInfo, *srvInfo, *pInfo;
int sock, del=0;

int handle_add(int client_sock);
int handle_list(int client_sock);
#endif
