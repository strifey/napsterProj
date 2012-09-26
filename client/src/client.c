#include "client.h"

int main(int argc, char *argv[]){
	/*TODO PARSE INPUT*/
	if (argc < 4){
		printf("Incorrect arguments. Usage: \n\t");
		printf("./nClient COMMAND(listfiles|addfiles) IP PORT [file1...]\n");
		exit(0);
	}
	if(!strcmp(argv[1], "addfiles") && argc >= 5){
		client_comm = ADD;
		file_in = argv[5];
		if(argc >= 6 && !strcmp(argv[6], "-d"))
			del =1;
	}	
	else if(!strcmp(argv[1], "listfiles"))
		client_comm = LIST;
	else{
		printf("Incorrect client command. Use addfiles or listfiles.\n");
		exit(1);
	}
	ip = argv[2];
	port = argv[3];

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
	if(client_comm == LIST){
		/*follow procedure for LIST*/
	}
	else if(client_comm == ADD){
		send(sock, "ADD", 3, 0);
		//send(sock, file_in, strlen(file_in), 0);
		recv(sock, &ans, 1, 0);
		if(ans == 'Y')
			printf("Recieved confirmation back\n");
	}
	close(sock);
	return 0;
}
