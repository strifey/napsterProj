#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "../../lib/napster.h"
#include "../../lib/fllist.h"

char *ip, *port, *file_in, comm='E';
struct addrinfo connInfo, *srvInfo, *pInfo;
int sock;
char buff[MAXBUFF];

char handle_ad(int sock);
void handle_list(int sock);
void die_gracefully(int sock, int errval);
#endif
