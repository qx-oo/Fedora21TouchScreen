#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <strings.h>

#define SERVPORT 8888
#define SERVERIP "127.0.0.1"
#define MAXDATASIZE 100
struct coninfo{
	struct hostent *host;
	struct sockaddr_in serv_addr;
	int sockfd;
	char recvbuf[MAXDATASIZE];
	char sendbuf[MAXDATASIZE];
	int  recvbytes;
	int sendsize;
};
int initSocket(struct coninfo* info){
	info->host=gethostbyname(SERVERIP);
	if((info->sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		return -1;
	}
	info->serv_addr.sin_family=AF_INET;
	info->serv_addr.sin_port=htons(SERVPORT);
	info->serv_addr.sin_addr = *((struct in_addr *)(info->host)->h_addr);
	bzero(&(info->serv_addr.sin_zero),8);
	if (connect(info->sockfd, (struct sockaddr *)&(info->serv_addr),
		sizeof(struct sockaddr)) == -1) {
		return -1;
	}
	return 0;
}
int recvSocket(struct coninfo* info){
	if ((info->recvbytes=recv(info->sockfd, info->recvbuf, MAXDATASIZE, 0)) ==-1) {
		return -1;;
	}
	info->recvbuf[info->recvbytes] = '\0';
	return 0;
}
int sendSocket(struct coninfo* info){
	if (send(info->sockfd, info->sendbuf, info->sendsize, 0) == -1){
		return -1;
	}
	return 0;
}
int closeSocket(struct coninfo* info){
	close(info->sockfd);
	return 0;
}
