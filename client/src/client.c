#include "client.h"

int main(int argc, char *argv[]){
	//TODO PARSE INPUT
	


	//MAKE CONNECTION BASED ON THAT
	
	memset(&connInfo, 0, sizeof connInfo);
	connInfo.ai_family = AF_UNSPEC;
	connInfo.ai_socktype = SOCK_STREAM;
	connInfo.ai_flags = AI_PASSIVE;
	getaddrinfo(NULL, PORT, &connInfo, &srvInfo);
	sock = socket(srvInfo->ai_family, srvInfo->ai_socktype, srvInfo->ai_protocol);

	//GET LIST FROM SERVER
	
	//ADD FILES TO SERVER
	
	//GET CONFIRMATION FROM SERVER THAT LIST WAS UPDATED
	
	//CLOSE SOCKET
	close(sock);
	printf("Socket closed\n");
	//print output
	return 0;
}

