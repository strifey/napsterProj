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

	/*FOR loop here*/
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
	printf("Now listening\n");
	while(1){
		/*ACCEPT connections and return what is queried for*/
		cStorlen = sizeof(cStor);
		client_sock = accept(sock, (struct sockaddr *)&cStor, &cStorlen);
		printf("Accepted connection\n");fflush(stdout);
		if(client_sock < 0){
			perror("Error accepting connection\n");
			exit(1);
		}
		char *c_comm = malloc(sizeof(char)*3);
		recv(client_sock, c_comm, 3, 0);
		c_comm[3] = '\0';
		printf("%s\n", c_comm);
		if(!strcmp(c_comm, "ADD")){
			//addfile requested
			int res = handle_add(client_sock);
			if(res == 0)
				printf("Handled add successfully\n");
			else
				perror("Error occurred handling add\n");
		}
		else if(!strcmp(c_comm, "LST")){
			//filelist requested
			int res = handle_list(client_sock);
			if(res == 0)
				printf("Handled list successfully\n");
			else
				perror("Error occurred handling list\n");
		}
		close(client_sock);
	}
	/*CLOSE SOCKET*/
	close(sock);
	printf("Server closing, socket closed\n");
	return 0;
}

int handle_add(int client_sock){
	int recv_res = 0;
	printf("Add recieved\n");
	char fn_size = 0;
	recv_res = recv(client_sock, &recv_res, 1, 0);
	if (recv_res < 0){
		//handle error
	}
	char *fn = (char*)malloc(sizeof(char)*fn_size);
	recv_res = recv(client_sock, fn, fn_size, 0);
	if(recv_res <= 0){
		//handle error
	}
	fn[(int)fn_size] = '\0';
	char d = 0;
	recv_res = recv(client_sock, &d, 1, 0);
	if(recv_res <= 0){
		//handle error continue
	}
	char res_a = -1;
	if(d == 'D');
		//call delete
		//res_a = (char) del_node(file_list, fn);
	else if(d == 'N'){
		res_a = (char) add_node(file_list, fn);
	}
	if(!res_a){
		char s = 'S';
		int send_res = send(client_sock, &s, 1, 0);
		if(send_res == 1)
			return 0;
		else{
			//handle failure to confirm
		}
	}
	else{
		char u = 'U';
		int send_res = send(client_sock, &u, 1, 0);
		if(send_res == 1)
			return 0;
		else{
			//handle failure to confirm
		}
	}
	return -1;
}

int handle_list(int client_sock){
	printf("Add recieved\n");
	send(client_sock, "Y", 1, 0);
}
