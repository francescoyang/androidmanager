#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <pthread.h>
#include <netdb.h>

#define PORT 12580 
#define BACKLOG 10
#define MAXDATASIZE 1024

int sockfd;
pthread_t recthread;

/*接收信息函数*/
void recmessage(void){
	while(1){
		int numbytes;
		char buf[MAXDATASIZE];
		
		if((numbytes = recv(sockfd,buf,MAXDATASIZE,0))==-1){
			perror("recv");
			exit(1);
		}
		buf[numbytes]='\0';
		if(strcmp(buf,"exit")==0){
			printf("Server is closed\n");
			close(sockfd);
			exit(1);
		}
		printf("Server:%s\n",buf);
		sleep(2);
	}/*while*/
}

//int main(int argc,char *argv[]){
int sampleclient(){
	struct hostent *he;
	struct sockaddr_in their_addr;
	/*客户端输入方式:./client 172.31.100.236,若无输入后面IP地址，会提示错误*/
	/*
	if(argc != 2){
		fprintf(stderr,"usage:client hostname\n");
		exit(1);
	}
	*/
	/*获取主机IP地址*/
//	if((he = gethostbyname(argv[1])) == NULL){
	if((he = gethostbyname("127.0.0.1")) == NULL){
		herror("gethostbyname");
		exit(1);
	}
	/*创建套接字*/
	if((sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1){
		perror("socket");
		exit(1);
	}
	/*初始化sockaddr_in结构体*/
	their_addr.sin_family = AF_INET;
	their_addr.sin_port = htons(PORT);
	their_addr.sin_addr = *((struct in_addr *)he->h_addr);
	bzero(&(their_addr.sin_zero),8);
	/*向服务器发送连接请求*/
	if(connect(sockfd,(struct sockaddr *)&their_addr,sizeof(struct sockaddr)) == -1){
		perror("connect");
		exit(1);
	}
	/*创建子线程，用于接收信息*/
	if((pthread_create(&recthread,NULL,(void*)recmessage,NULL))!= 0){
		printf("create thread error!\r\n");
		exit(1);
	}
	/*发送信息。接收发送信息用的是同一端口，都 是sockfd*/
	while(1){
		char msg[MAXDATASIZE];
//		scanf("%s",msg);
		if(send(sockfd,"qt",strlen("qt"),0) == -1){
			perror("send");
			exit(1);
		}
		if(strcmp(msg,"exit") ==0){
			printf("byebye\n");
			close(sockfd);
			exit(1);
		}
		sleep(2);
	}/*while*/
	return 0;
}
