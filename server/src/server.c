#include "server.h"

int main(int argc, char *argv[]){
	/*LOAD LIST*/

	/*START LISTENING*/
	memset(&connInfo, 0, sizeof connInfo);
	connInfo.ai_family = AF_UNSPEC;
	connInfo.ai_socktype = SOCK_STREAM;
	connInfo.ai_flags = AI_PASSIVE;
	getaddrinfo(NULL, PORT, &connInfo, &srvInfo);
	/*FOR loop here*/
	for(pInfo = srvInfo; pInfo != NULL; pInfo = pInfo->ai_next){
		sock = socket(srvInfo->ai_family, srvInfo->ai_socktype, srvInfo->ai_protocol);
		if(sock <0){
			printf("Failed to create socket\n");
			continue;
		}
		if(bind(sock, srvInfo->ai_addr, srvInfo->ai_addrlen) < 0){
			close(sock);
			printf("Failed to bind socket\n");
			continue;
		}
		printf("Found a socket and bound\n");
		break;
	}
	if(pInfo == NULL){
		printf("Failed to find and bind a socket\n");
		exit(1);
	}
	if(listen(sock, BACKLOG) < 0){
		printf("listening failed\n");
		exit(1);
	}
	printf("Now listening\n");
	while(1){
		/*ACCEPT connections and return what is queried for*/
		cStorlen = sizeof(cStor);
		client_sock = accept(sock, (struct sockaddr *)&cStor, &cStorlen);
		printf("Accepted connection");
		if(client_sock < 0){
			printf("Error accepting connection\n");
			exit(1);
		}
		char* hi = "hello!";
		int hi_len = strlen(hi);
		send(client_sock, hi, hi_len, 0);

		close(client_sock);
	}
	/*CLOSE SOCKET*/
	close(sock);
	printf("Server closing, socket closed\n");
	return 0;
}
