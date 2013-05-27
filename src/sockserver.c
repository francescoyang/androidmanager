#include "sockserver.h"
#include <stdio.h>
#include <sys/select.h>

/* According to earlier standards */
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif


	static cmr_msglib_t msglibfd[MAXSOCKETNO];

	msglib_errno_t msgliberr_table[] = {
		{ERR_TOOMANYSOCKET, "Socket Number >> Msglib Suport Socket Number(1024)!\n"},
		{ERR_MALLOC, "Malloc Error!\n"},
		{ERR_CREATSOCKET, "Creat Socket Error!\n"},
		{ERR_CONNECT, "Connect Error!\n"},
		{ERR_BIND, "Bind Error!\n"},
		{ERR_LINSTEN, "Linsten Error!\n"},
		{ERR_FD, "FD Error, Invalid FD!\n"},
		{ERR_SEND, "Send Error!\n"},
		{ERR_RECV, "Recv Error!\n"},
		{MAXERRNO, "Invalid  Errorno!\n"},
		{ERR_UDP_SEND, "UDP Send Error!\n"},
		{ERR_UDP_RECV, "UDP recv Error!\n"},
		{0, NULL}
	};


	static inline int getminmsglibfd(void)
	{
		int i;
		for (i = 1; i < MAXSOCKETNO;i++) {
			if (msglibfd[i].msgfd != i) {
				break;
			}
		}
		if (i >= MAXSOCKETNO) {
			return 0;
		}
		msglibfd[i].msgfd = i;
		return i;
	}

	static inline int judgefd(int fd, int flags)
	{
		if ((fd <= 0) || (fd >= MAXSOCKETNO)) {
			return ERR_FD;
		}	
		if (msglibfd[fd].msgfd != fd) {
			return ERR_FD;	
		}
		if (!msglibfd[fd].dtmsg) {
			msglibfd[fd].msgfd = 0;
			return ERR_FD;
		}
		switch (flags) {
			case JUDGESFD:
				if (!msglibfd[fd].dtmsg->sfd) {
					return ERR_FD;
				}
				break;
			case JUDGECFD:
				if (!msglibfd[fd].dtmsg->cfd) {
					return ERR_FD;
				}
				break;
			default:
				break;
		}
		return SUCCEESS;
	}


	static inline void freeresource(int fd) 
	{
		if (judgefd(fd, INVALIDFD)) {
			return ;
		}	
		if (msglibfd[fd].dtmsg->cfd) {
			close(msglibfd[fd].dtmsg->cfd);
			msglibfd[fd].dtmsg->cfd = 0;
		}	

		if (msglibfd[fd].dtmsg->sfd) {
			close(msglibfd[fd].dtmsg->sfd);
			msglibfd[fd].dtmsg->sfd = 0;
		}	

		free(msglibfd[fd].dtmsg);
		msglibfd[fd].dtmsg = NULL;
		msglibfd[fd].msgfd = 0;
		return ;
	}

	int dtcmr_client_creat(char *serverip, short port, int type)
	{
		int i;
		if (!(i = getminmsglibfd())) {	
			return ERR_TOOMANYSOCKET;
		}
		msglibfd[i].dtmsg = malloc(sizeof(dtcmr_msg_t));
		if (!msglibfd[i].dtmsg) {
			msglibfd[i].msgfd = 0;
			return ERR_MALLOC;
		}
		memset(msglibfd[i].dtmsg, 0, sizeof(dtcmr_msg_t));

		if(type == IPPROTO_TCP){
			msglibfd[i].dtmsg->cfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		} else if(type == IPPROTO_UDP){
			msglibfd[i].dtmsg->cfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		} else {
			return ERR_TYPE;
		}
		if (msglibfd[i].dtmsg->cfd == -1) {
			freeresource(i);
			handle_error("socket");
			return ERR_CREATSOCKET;
		}
		msglibfd[i].dtmsg->s_addrsize = sizeof(struct sockaddr);
		msglibfd[i].dtmsg->c_addrsize = sizeof(struct sockaddr);

		memset(&msglibfd[i].dtmsg->s_addr, 0, msglibfd[i].dtmsg->s_addrsize);
		memset(&msglibfd[i].dtmsg->c_addr, 0, msglibfd[i].dtmsg->c_addrsize);

		msglibfd[i].dtmsg->s_addr.sin_family = AF_INET;
		msglibfd[i].dtmsg->s_addr.sin_port = htons(port);
		msglibfd[i].dtmsg->s_addr.sin_addr.s_addr = inet_addr(serverip);	

		if(IPPROTO_TCP == type){
			if (connect(msglibfd[i].dtmsg->cfd, 
						(struct sockaddr *)&msglibfd[i].dtmsg->s_addr, 
						msglibfd[i].dtmsg->s_addrsize) == -1) {
				freeresource(i);
				handle_error("connect");
				return ERR_CONNECT;
			}
			printf("connect ok\n");
		}

		printf("fd i %d\n",i);
		printf("recv msglibfd[i].dtmsg->cfd %d\n",msglibfd[i].dtmsg->cfd);
		return i;
	}


	int dtcmr_serv_creat(short sport, int listenback, int type)
	{
		int i;
		if (!(i = getminmsglibfd())) {	
			return ERR_TOOMANYSOCKET;
		}
		msglibfd[i].dtmsg = malloc(sizeof(dtcmr_msg_t));
		if (!msglibfd[i].dtmsg) {
			msglibfd[i].msgfd = 0;
			return ERR_MALLOC;
		}
		memset(msglibfd[i].dtmsg, 0, sizeof(dtcmr_msg_t));

		if(type == IPPROTO_TCP){
			msglibfd[i].dtmsg->sfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		} else if(type == IPPROTO_UDP){
			msglibfd[i].dtmsg->sfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		}
		if (msglibfd[i].dtmsg->sfd == -1) {
			freeresource(i);
			return ERR_CREATSOCKET;
		}
		msglibfd[i].dtmsg->s_addrsize = sizeof(struct sockaddr);
		msglibfd[i].dtmsg->c_addrsize = sizeof(struct sockaddr);

		memset(&msglibfd[i].dtmsg->s_addr, 0, msglibfd[i].dtmsg->s_addrsize);
		memset(&msglibfd[i].dtmsg->c_addr, 0, msglibfd[i].dtmsg->c_addrsize);

		msglibfd[i].dtmsg->s_addr.sin_family = AF_INET;
		msglibfd[i].dtmsg->s_addr.sin_port = htons(sport);
		msglibfd[i].dtmsg->s_addr.sin_addr.s_addr = INADDR_ANY;	

		if (bind(msglibfd[i].dtmsg->sfd, 
					(struct sockaddr *)&msglibfd[i].dtmsg->s_addr, 
					msglibfd[i].dtmsg->s_addrsize) == -1) {
			freeresource(i);	
			handle_error("bind");
			return ERR_BIND;
		}

		if(type){
			if (listen(msglibfd[i].dtmsg->sfd, listenback) == -1) {
				freeresource(i);
				handle_error("listen");
				return ERR_LINSTEN;
			}
		}

		return i;
	}


	int dtcmr_accept(int fd)
	{	
		if (judgefd(fd, JUDGESFD)) {
			return ERR_FD;
		}
		msglibfd[fd].dtmsg->cfd = accept(msglibfd[fd].dtmsg->sfd, 
				(struct sockaddr *)&msglibfd[fd].dtmsg->c_addr, 
				&msglibfd[fd].dtmsg->c_addrsize);
		if (msglibfd[fd].dtmsg->cfd == -1) {
			handle_error("accept");
			return ERR_ACCEPT;
		}
		//	printf("cfd=%d\n", msglibfd[fd].dtmsg->cfd);
		return SUCCEESS;
	}


	int dtcmr_send(int fd, char *buf, int leng)
	{
		int ret;
		assert(NULL != buf);
		if (judgefd(fd, JUDGECFD)) {
			return ERR_FD;
		}
		if ((ret = send(msglibfd[fd].dtmsg->cfd, buf, leng, MSG_NOSIGNAL)) < 0) {
			printf("send error\n");
			return ERR_SEND;
		}
		return ret;
	}

	int dtcmr_recv(int fd, char *buf, int leng) 
	{
		int ret;
		int rl = 0;
		int times = 0;
		assert(NULL != buf);
		if (judgefd(fd, JUDGECFD)) {
			return ERR_FD;
		}
		while (rl < leng) {

			printf("msglibfd[fd].dtmsg->cfd  %d\n",msglibfd[fd].dtmsg->cfd);
			ret = recv(msglibfd[fd].dtmsg->cfd, buf+rl, leng-rl, 0);
			if (ret < 0) {
				printf("recv error %d!\n", ret);
				return ERR_RECV;
			} else {
				if (times++ > JPNETRECVTRYTIME) {
					return rl;
				}
			}
		}

//		printf("recvleng = 0x%x\n", ret);
		return ret;
	}

	static int dtcmr_rcvtimeout(int fd, char *buf, int leng, struct timeval *timeout)
	{
		int ret;
		int recved;
		fd_set fd_read;

		FD_ZERO(&fd_read);
		FD_SET(fd, &fd_read);
		struct timeval tout;

		tout.tv_sec = timeout->tv_sec;
		tout.tv_usec = timeout->tv_usec;

		ret = select(fd + 1, &fd_read, NULL, NULL, &tout);
		if (ret == -1) {
			return -1;
		}	else if (ret){
			if(FD_ISSET(fd, &fd_read)) {
				recved = recv(fd, buf, leng, 0);
				//		for (i = 0; i < recved; i++) {
				//printf("0x%x, ", recved);
				//		}
				if (recved <=0) {
					return -1;
				} else {
					return recved;
				}
			}
		} else if (ret == 0) {
			printf("Receiving Timeout...\n");
			return 0;
		}

		return recved;
	}

	int dtcmr_recv_timeout(int fd, char *buf, int leng, struct timeval *timeout) 
	{
		assert(NULL != buf);
		if (judgefd(fd, JUDGECFD)) {
			return ERR_FD;
		}

		struct timeval tout;
		int ret  = 0;
		int rl=0;
		int i = 0;

		while (rl < leng) {
			tout.tv_sec = timeout->tv_sec;
			tout.tv_usec = timeout->tv_usec;
			ret = dtcmr_rcvtimeout(msglibfd[fd].dtmsg->cfd, buf+rl, leng-rl, &tout);
			if (ret < 0) {
				return ret;
			}else if(ret == 0) {
				if (i++> JPNETRECVTRYTIME) {
					return rl;
				}
			}else{
				i = 0;
				rl+=ret;
			}

		}

		return rl;
	}


	int dtcmr_udp_send(int fd, char *buf, int leng)
	{
		int ret;
		assert(NULL != buf);
		if (judgefd(fd, JUDGECFD)) {
			return ERR_FD;
		}
		if ((ret = sendto(msglibfd[fd].dtmsg->cfd, buf, leng, 0, 
						(struct sockaddr *)&msglibfd[fd].dtmsg->c_addr, 
						msglibfd[fd].dtmsg->c_addrsize)) < 0) {
			printf("send error\n");
			return ERR_UDP_SEND;
		}
		return ret;
	}

	int dtcmr_udp_recv(int fd, char *buf, int leng) 
	{
		int ret;
		assert(NULL != buf);
		if (judgefd(fd, JUDGECFD)) {
			return ERR_FD;
		}
		if((ret = recvfrom(msglibfd[fd].dtmsg->cfd, buf, leng, 0, 
						(struct sockaddr *)&msglibfd[fd].dtmsg->c_addr, 
						&msglibfd[fd].dtmsg->c_addrsize)) < 0){
			printf("recv error %d!\n", ret);
			return ERR_UDP_RECV;
		}
		return ret;
	}

	void dtcmr_shotdown(int fd, int flags)
	{
		if (judgefd(fd, 2)) {
			return ;
		}

		switch(flags) {
			case FREE_SERVER:
				if (msglibfd[fd].dtmsg->sfd) {
					close(msglibfd[fd].dtmsg->sfd);
					msglibfd[fd].dtmsg->sfd = 0;
				}
				break;
			case FREE_CLINT:
				if (msglibfd[fd].dtmsg->cfd) {
					close(msglibfd[fd].dtmsg->cfd);
					msglibfd[fd].dtmsg->cfd = 0;
				}
				break;
			default: break;
		}	
		return ;	
	}

	void dtcmr_free(int fd)
	{
		if (judgefd(fd, 2)) {
			return ;
		}
		dtcmr_shotdown(fd, FREE_SERVER);
		dtcmr_shotdown(fd, FREE_CLINT);

		freeresource(fd);
		return ;
	}

	void close_sockfd(int fd)
	{
		close(msglibfd[fd].dtmsg->cfd);
	}

	char *getmsgliberrinfo(int errnb)
	{
		int i;
		for (i = 0; i < MAXERRNO; i++) {
			if (msgliberr_table[i].errnb == errnb) {
				return msgliberr_table[i].errstr;
			}
		}
		return msgliberr_table[MAXERRNO-1].errstr;
	}


#ifdef __cplusplus
}
#endif
