#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>


int main(int argc, char *argv[])
{
	int portno = 3306;
	char *hostname ="127.0.0.1";

	int sockfd;
	struct sockaddr_in serv_addr;
	struct hostent *server;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		error("Error opening socket");
	}

	server =gethostbyname(hostname);

	if(server==NULL){
		fprintf(stderr, "ERROR, no such host\n");
		exit(0);	
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	bcopy((char *)server->h_addr,
		(char *)&serv_addr.sin_addr.s_addr,
		server->h_length);

	serv_addr.sin_port=htons(portno);
	if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0){
		printf("Port is closed\n");
	}else{
		printf("port is active\n");
	}

	close(sockfd);
	printf("\n");
	return 0; 
	
}
