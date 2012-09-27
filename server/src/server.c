#include "server.h"

int main(){
	/*LOAD LIST*/
	file_list = create_list();
	load_list(file_list, lpath);

	/*START LISTENING*/
	memset(&connInfo, 0, sizeof connInfo);
	connInfo.ai_family = AF_INET;
	connInfo.ai_socktype = SOCK_STREAM;
	connInfo.ai_flags = AI_PASSIVE;
	getaddrinfo(NULL, PORT, &connInfo, &srvInfo);

	/*for loop to determine corr addr info*/
	for(pInfo = srvInfo; pInfo != NULL; pInfo = pInfo->ai_next){
		sock = socket(srvInfo->ai_family, srvInfo->ai_socktype, srvInfo->ai_protocol);
		if(sock <0){
			perror("Failed to create socket\n");
			continue;
		}
		if(bind(sock, srvInfo->ai_addr, srvInfo->ai_addrlen) < 0){
			close(sock);
			perror("Failed to bind socket\n");
			continue;
		}
		printf("Found a socket and bound\n");
		break;
	}
	if(pInfo == NULL){
		perror("Failed to find and bind a socket\n");
		exit(1);
	}
	if(listen(sock, BACKLOG) < 0){
		perror("listening failed\n");
		exit(1);
	}
	printf("Server now running and  listening\n");
	while(1){
		/*ACCEPT connections and return what is queried for*/
		cStorlen = sizeof(cStor);
		client_sock = accept(sock, (struct sockaddr *)&cStor, &cStorlen);
		printf("Accepted connection\n");fflush(stdout);
		if(client_sock < 0){
			perror("Error accepting connection\n");
			close(client_sock);
			continue;
		}
		int res_recv = recv(client_sock, buff, MAXBUFF, 0);
		if(res_recv <= 0){
			perror("Error recieving intial command/file from client\n");
			close(client_sock);
			continue;
		}
		char delim = DELIM;
		c_comm = strtok(buff, &delim);
		if(c_comm == NULL)
			perror("ERROR PARSING COMMAND FROM BUFFER\n");
		else if(!strcmp(c_comm, ADD_S)){
			int ret = handle_add(client_sock, strtok(NULL, &delim));
			if(!ret)
				printf("Sucessfully added file\n");
			else
				perror("There was an issue adding the file\n");
		}
		else if(!strcmp(c_comm, DEL_S)){
			int ret = handle_del(client_sock, strtok(NULL, &delim));
			if(!ret)
				printf("Sucessfully deleted file\n");
			else
				perror("There was an issue deleting the file\n");
		}
		else if(!strcmp(c_comm, LST_S)){
			handle_list(client_sock);
			printf("Sent list to client\n");
		}
		memset(buff, 0, MAXBUFF);
	}
}

void handle_list(int client_sock){
	char eof = EOF;
	if(file_list->size == 0){
		send(client_sock, &eof, 1, 0);
		return;
	}
	for(filenode *i = file_list->head; i != NULL; i=i->next){
		char*s_node = serialize_node(i);
		strcpy(buff,s_node);
		if(send(client_sock, buff, strlen(buff), 0) <= 0){
			perror("Client closed connection or there was a issue in the connection. Closing.\n");
			return;
		}
		printf("Sent: %s\n", buff);
		if(recv(client_sock, &ACK, 1, 0) <= 0){
			perror("Client closed connection or there was a issue in the connection. Closing.\n");
			return;
		}
		memset(buff, 0, MAXBUFF);
		free(s_node);
	}
	if(send(client_sock, &eof, 1, 0) <= 0){
			perror("Client closed connection or there was a issue in the connection. Closing.\n");
			return;
	}
	return;
}

int handle_add(int client_sock, char*filename){
	char *new_ip = (char*)malloc(sizeof(char)*(INET_ADDRSTRLEN+1));
	inet_ntop(AF_INET, &((struct sockaddr_in *)&cStor)->sin_addr, new_ip, cStorlen);
	int res_add = add_node(file_list, filename, new_ip);
	int res_save = save_list(file_list, lpath);
	int t_res = res_add || res_save;
	if(!t_res)
		send(client_sock, &SUCESS, 1, 0);
	else
		send(client_sock, &UNSCESS, 1, 0);
	free(new_ip);
	print_list(file_list);
	return t_res;
}

int handle_del(int client_sock, char*filename){
	char *new_ip = (char*)malloc(sizeof(char)*(INET_ADDRSTRLEN+1));
	inet_ntop(AF_INET, &((struct sockaddr_in *)&cStor)->sin_addr, new_ip, cStorlen);
	int res_del = del_node(file_list, filename, new_ip);
	int res_save = save_list(file_list, lpath);
	int t_res = res_del || res_save;
	if(!t_res)
		send(client_sock, &SUCESS, 1, 0);
	else
		send(client_sock, &UNSCESS, 1, 0);
	free(new_ip);
	print_list(file_list);
	return t_res;
}
