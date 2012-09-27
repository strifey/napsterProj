#include "client.h"

int main(int argc, char *argv[]){
	/*PARSE INPUT*/
	//make sure there's at least bare input
	if (argc < 4){
		printf("Incorrect arguments. Usage: \n\t");
		printf("./nClient COMMAND(listfiles|addfile) IP PORT [FILE] [D]\n");
		exit(0);
	}
	//check if add
	if(!strcmp(argv[1], "addfile") && argc >= 5){
		comm = ADD;
		//check filename length
		if(strlen(argv[4]) > MAX_NAME_LEN){
			printf("Filename too long. Keep under %d characters\n", MAX_NAME_LEN);
			exit(1);
		}
		file_in = argv[4];
		//parse flag out to make a delete
		if(argc >= 6 && !strcmp(argv[5], "-d"))
			comm = DEL;
		//don't allow invalid flag
		else if(argc >= 6 && strcmp(argv[5], "-d")){
			printf("Incorrect flag. Please use -d to delete\n");
			exit(1);
		}
	}	
	//check if list
	else if(!strcmp(argv[1], "listfiles"))
		comm = LST;
	else{
		printf("Incorrect client command. Use addfile or listfiles.\n");
		exit(1);
	}
	//getaddrinfo will fail if ip isn't valid, so just accept
	ip = argv[2];
	//if can't convert port, reject input
	if(atoi(argv[3]) > 65000 || atoi(argv[3]) <= 0){
		printf("Invalid port. Please verify.");
		exit(1);
	}
	port = argv[3];

	/*MAKE CONNECTION BASED ON THAT*/
	memset(&connInfo, 0, sizeof connInfo);
	connInfo.ai_family = AF_INET;
	connInfo.ai_socktype = SOCK_STREAM;
	connInfo.ai_flags = AI_PASSIVE;
	getaddrinfo(argv[2], argv[3], &connInfo, &srvInfo);
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
	if(comm == LST){
		printf("Requesting list:\n");
		handle_list(sock);
		//handle_list
	}
	else if(comm == ADD || comm == DEL){
		printf("Sending add/del request: \n");
		handle_ad(sock);
		//handle_del(sock);
	}
	close(sock);
	return 0;
}

int handle_ad(int sock){
	char * pack = malloc(sizeof(char)*(MAX_NAME_LEN+3)); pack[0] = comm;
	pack[1] = '\0';
	strcat(pack, "|");
	strcat(pack, file_in);
	int res = send(sock, pack, strlen(pack), 0);
	if(res <= 0)
		die_gracefully(sock, res);
	return 0;
}

int handle_list(int sock){
	//TODO SEND COMMAND
	char * pack = malloc(sizeof(char)*(12));
	pack[0] = comm;
	pack[1] = '\0';
	strcat(pack, "|");
	strcat(pack, "garbage");
	int sent = send(sock, pack, strlen(pack), 0);
	if(sent <= 0)
		die_gracefully(sock, sent);
	int ret_len = recv(sock, buff, MAXBUFF, 0);
	while(ret_len > 1){
		buff[ret_len] = '\0';
		printf("%s\n", buff);
		memset(buff, 0, MAXBUFF);
		int sr = send(sock, &ACK, 1, 0);
		if(sr<=0)
			die_gracefully(sock, sr);
		ret_len = recv(sock, buff, MAXBUFF, 0);
	}
	memset(buff, 0, MAXBUFF);
	if(ret_len <= 0)
		die_gracefully(sock, ret_len);
	return 0;
}

void die_gracefully(int sock, int errval){
	close(sock);
	if(errval == 0)
		perror("Server closed connection unexpectedly. Shutting down\n");
	else if(errval < 0)
		perror("Error communicating with server. Shutting down\n");
	exit(1);
}
