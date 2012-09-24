#include "client.h"

int main(int argc, char *argv[]){
	/*TODO PARSE INPUT*/
	if (argc < 1){
		printf("Usage: \n\n\t");
		printf("./nClient IP PORT listfiles|addfiles file1...\n");
		exit(0);
	}

	/*MAKE CONNECTION BASED ON THAT*/
	memset(&connInfo, 0, sizeof connInfo);
	connInfo.ai_family = AF_UNSPEC;
	connInfo.ai_socktype = SOCK_STREAM;
	connInfo.ai_flags = AI_PASSIVE;
	getaddrinfo(NULL, PORT, &connInfo, &srvInfo);
	sock = socket(srvInfo->ai_family, srvInfo->ai_socktype, srvInfo->ai_protocol);
	if(sock < 0){
		printf("Error setting up socket\n");
		exit(1);
	}
	for(pInfo = srvInfo; pInfo != NULL; pInfo = pInfo->ai_next){
		sock = socket(srvInfo->ai_family, srvInfo->ai_socktype, srvInfo->ai_protocol);
		if(sock <0){
			printf("Failed to create socket\n");
			continue;
		}
		if(connect(sock, srvInfo->ai_addr, srvInfo->ai_addrlen) < 0){
			close(sock);
			printf("Failed to connect to server\n");
			continue;
		}
		printf("Found a socket and bound\n");
		break;
	}
	if(pInfo == NULL){
		printf("Failed to conect\n");
		exit(1);
	}
	recv(sock, buff, MAXBUFF-1, 0);
	buff[MAXBUFF] = '\0';
	printf("%s\n", buff);

	/*GET LIST FROM SERVER*/
	
	/*ADD FILES TO SERVER*/
	
	/*GET CONFIRMATION FROM SERVER THAT LIST WAS UPDATED*/
	
	/*CLOSE SOCKET*/
	close(sock);
	printf("Program ending. Byyyyyye\n");
	return 0;
}

