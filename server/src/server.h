#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "../../lib/napster.h"
#include "../../lib/fllist.h"

#define BACKLOG 12

/*Variables*/
struct addrinfo connInfo, *srvInfo, *pInfo;
struct sockaddr_storage cStor;
int sock, client_sock, list_len;
socklen_t cStorlen;
fllist *file_list;
const char* lpath = "./.list";
char *c_comm;
char buff[MAXBUFF];

/*Delarations*/
void die_gracefully();
void handle_list(int client_sock);
int handle_add(int client_sock, char*filename);
int handle_del(int client_sock, char*filename);
#endif
