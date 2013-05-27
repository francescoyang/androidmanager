#ifndef __SOCKSERVERLIB_API_H__
#define __SOCKSERVERLIB_API_H__


#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <sys/select.h>

/* According to earlier standards */
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>




#define  FREE_SERVER  1
#define FREE_CLIENT	2


//creat socket of tcp,and return fd 
int dtcmr_client_creat(char *serverip, short port, int type);
int dtcmr_serv_creat(short sport, int listenback, int type);
//type IPPROTO_TCP/IPPROTO_UDP
int dtcmr_accept(int fd);
int dtcmr_send(int fd, int buf, int leng);
int dtcmr_recv(int fd, char *buf, int leng) ;
int dtcmr_recv_timeout(int fd, char *buf, int leng, struct timeval *timeout);
int dtcmr_udp_send(int fd, char *buf, int leng);
int dtcmr_udp_recv(int fd, char *buf, int leng);
void dtcmr_shotdown(int fd, int flags);
void dtcmr_free(int fd);
char *getmsgliberrinfo(int errno);
void close_sockfd(int fd);

#ifdef __cplusplus
}
#endif

#endif

