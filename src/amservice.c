#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <pthread.h>
#include "sockserverlib_api.h"
#include "sockserver.h"
#include "manager_api.h"
#include "typestruct.h"


#define SERVPORT 12580 
char recv_buf = 0;
int recv_leng = 0;
int SIZE = 0;
char tosize[4] = {0};

char getbuf[1024 * 1000] = {0};
char getbookbuf[1024 * 1000] = {0};
char getmmsbuf[1024 * 10000] = {0};
char getstoragebuf[200] = {0};

char SEND_CMD = 0;
int OVERSIGN = 0;
int REFRESHSIGN = 0;


int sockfd;
int i = 0;
char send_num = 4;
int ret;
int num=1;

int sddata[1024];
int ACK		= 0x01;
int RESEND	= 0x02;
int tmpreturn = 0;

struct timeval tout;
typedef struct __sockthread{
	void *managerp;
	pthread_t tid;
	pthread_attr_t tattr;
}sockthread_t;


static sockthread_t sendthread;
static pthread_mutex_t net_mutex;

sem_t reget[10]; 

void seminit()
{
	for(i = 0; i < 10; i++)
	{
		sem_init(&reget[i],0,0);
	}
}

int refreshinfo()
{
	//	printf("test refreshinfo %d\n",REFRESHSIGN);
	tmpreturn = 0;
	tmpreturn = REFRESHSIGN;
	REFRESHSIGN  = 0;
	return tmpreturn;

}

void setmessageinfo(char *char_mmsnumber,char *char_mmsdata)
{
	memcpy(sendmessage.mmsnumber,char_mmsnumber,strlen(char_mmsnumber));
	memcpy(sendmessage.mmsdata,char_mmsdata,strlen(char_mmsdata));
}

void setcallphone(char *phonenumber)
{
	memcpy(sendmessage.mmsnumber,phonenumber,strlen(phonenumber));
}

int waitdata()
{
	tmpreturn = 0;
	tmpreturn = OVERSIGN;
	OVERSIGN = 0;
	//	printf("tmpreturn = %d\n",tmpreturn);
	return tmpreturn;
}

int mutexmanager()
{
	while(1)
	{
		pthread_mutex_lock(&net_mutex);
		printf("wait sem\n");
		sem_wait(&reget[1]);
		pthread_mutex_unlock(&net_mutex);
		usleep(5000);
	}
}

recv_pack()
{
	memset(getbuf,0, 1024*1000);
	tout.tv_sec = 3;
	tout.tv_usec = 0;
	for(i = 0; i < 4; i++)
	{
		dtcmr_recv_timeout(sockfd, &recv_buf, 1,&tout);
		if(recv_buf == 0x77){
			recv_buf = 0;
		}else{
			usleep(100000);
			i = 0;
			recv_buf = 0;
		}
	}

	dtcmr_recv_timeout(sockfd, &SEND_CMD, 1,&tout);
	switch(SEND_CMD)
	{
		case CMD_IMAGE:
			printf("SEND_CMD = %x\n",SEND_CMD);
			ret = dtcmr_recv_timeout(sockfd, &recv_leng, 4,&tout);
			printf("recv_leng= %d\n", recv_leng);
			if(ret < 0){
				printf("recv error");
			}

			ret = dtcmr_recv_timeout(sockfd, getbuf, recv_leng,&tout);
			allinfo_t *tmpinfo=(allinfo_t *)getbuf;
			memcpy(&imageinfo.count, &(tmpinfo->count), 4);
			printf("imageinfo.count = %d\n",imageinfo.count);


			for(i = 0;i <= imageinfo.count; i ++)
			{
				memcpy(imageinfo.get_info[i].filename,tmpinfo->get_info[i].filename,100);
				memcpy(imageinfo.get_info[i].filesize,tmpinfo->get_info[i].filesize,32);
				memcpy(imageinfo.get_info[i].filepath,tmpinfo->get_info[i].filepath,500);
			}
			break;

		case CMD_APP:
			memset(&appinfo, 0, sizeof(allappinfo_t));
			printf("SEND_CMD = %x\n",SEND_CMD);
			ret = dtcmr_recv_timeout(sockfd, &recv_leng, 4,&tout);

			printf("recv_leng= %d\n", recv_leng);
			if(ret < 0){
				printf("recv error");
			}
			memset(getbuf,0, 1024*1000);

			ret = dtcmr_recv_timeout(sockfd, getbuf, recv_leng,&tout);

			allappinfo_t *apptmpinfo=(allappinfo_t *)getbuf;
			memcpy(&appinfo.count, &(apptmpinfo->count), 4);
			printf("appinfo.count = %d\n",appinfo.count);
			for(i = 0;i <= appinfo.count; i ++)
			{
				appinfo.get_info[i].apppath = apptmpinfo->get_info[i].apppath;
				appinfo.get_info[i].appattribute = apptmpinfo->get_info[i].appattribute;

				memcpy(appinfo.get_info[i].appname,apptmpinfo->get_info[i].appname,50);
				memcpy(appinfo.get_info[i].apppackname,apptmpinfo->get_info[i].apppackname,100);
				memcpy(appinfo.get_info[i].appversion,apptmpinfo->get_info[i].appversion,15);
				memcpy(appinfo.get_info[i].appsize,apptmpinfo->get_info[i].appsize,16);
			}
			OVERSIGN = 1;
			REFRESHSIGN  = CMD_APP;
			SEND_CMD = 0;
			break;

		case CMD_BOOK:
			memset(&bookinfo, 0, sizeof(allbookinfo_t));
			printf("SEND_CMD = %x\n",SEND_CMD);
			ret = dtcmr_recv_timeout(sockfd, &recv_leng, 4,&tout);

			printf("recv_leng= %d\n", recv_leng);
			if(ret < 0){
				printf("recv error");
			}
			memset(getbookbuf,0, 1024*1000);

			ret = dtcmr_recv_timeout(sockfd, getbookbuf, recv_leng,&tout);

			allbookinfo_t *booktmpinfo=(allbookinfo_t *)getbookbuf;
			memcpy(&bookinfo.count, &(booktmpinfo->count), 4);
			printf("bookinfo.count = %d\n",bookinfo.count);
			for(i = 0;i <= bookinfo.count; i ++)
			{
				memcpy(bookinfo.get_info[i].bookname,booktmpinfo->get_info[i].bookname,20);
//				printf("bookname   = %s\n",booktmpinfo->get_info[i].bookname);
				memcpy(bookinfo.get_info[i].booknumber,booktmpinfo->get_info[i].booknumber,18);
//				printf("booknumber = %s\n",bookinfo.get_info[i].booknumber);
			}
			REFRESHSIGN  = CMD_BOOK;
			SEND_CMD = 0;
			break;

		case CMD_STORAGE:
			memset(&bookinfo, 0, sizeof(allbookinfo_t));
			printf("SEND_CMD = %x\n",SEND_CMD);
			ret = dtcmr_recv_timeout(sockfd, &recv_leng, 4,&tout);

			printf("recv_leng= %d\n", recv_leng);
			if(ret < 0){
				printf("recv error");
			}
			memset(getstoragebuf,0, 200);

			ret = dtcmr_recv_timeout(sockfd, getstoragebuf, recv_leng,&tout);

			storageinfo_t *storagetmpinfo=(storageinfo_t  *)getstoragebuf;

			memcpy(storageinfo.sdSize,storagetmpinfo->sdSize,32);
			memcpy(storageinfo.sdAvail,storagetmpinfo->sdAvail,32);
			memcpy(storageinfo.memorySize,storagetmpinfo->memorySize,32);
			memcpy(storageinfo.memoryAvail,storagetmpinfo->memoryAvail,32);
			printf("%s,%s,%s,%s",storageinfo.sdSize,storageinfo.sdAvail,storageinfo.memorySize,storageinfo.memoryAvail);

			REFRESHSIGN  = CMD_STORAGE;
			OVERSIGN = 1;
			SEND_CMD = 0;
			break;
		case CMD_CALLPHONE:
			printf("SEND_CMD = %x\n",CMD_CALLPHONE);
			break;
		case CMD_SENDMMS:
			printf("SEND_CMD = %x\n",CMD_SENDMMS);
			ret = dtcmr_recv_timeout(sockfd, &recv_leng, 4,&tout);
			if(recv_leng)
				printf("send message success\n");

			break;

		case CMD_MMS:
			memset(&mmsinfo, 0, sizeof(allmmsinfo_t));
			memset(getmmsbuf,0, 1024*10000);

			printf("RECV_CMD = %x\n",SEND_CMD);

			ret = dtcmr_recv_timeout(sockfd, &recv_leng, 4,&tout);

			printf("recv_leng= %d\n", recv_leng);
			if(ret < 0){
				printf("recv error");
			}

			ret = dtcmr_recv_timeout(sockfd, getmmsbuf, recv_leng,&tout);

			allmmsinfo_t *mmstmpinfo=(allmmsinfo_t *)getmmsbuf;
			mmsinfo.count = mmstmpinfo->count;
			printf("mmsinfo.count = %d\n",mmsinfo.count);
			for(i = 0;i <= mmsinfo.count; i ++)
			{
				memcpy(mmsinfo.get_info[i].mmsname,mmstmpinfo->get_info[i].mmsname,20);
				//				printf("mmsname   = %s\n",mmstmpinfo->get_info[i].mmsname);

				memcpy(mmsinfo.get_info[i].mmsnumber,mmstmpinfo->get_info[i].mmsnumber,18);
				//				printf("mmsnumber = %s\n",mmsinfo.get_info[i].mmsnumber);
				memcpy(mmsinfo.get_info[i].mmsbody,mmstmpinfo->get_info[i].mmsbody,1024*2);
//								printf("mmsbody   = %s\n",mmsinfo.get_info[i].mmsbody);
				memcpy(mmsinfo.get_info[i].mmsdate,mmstmpinfo->get_info[i].mmsdate,25);
				//				printf("mmsdate   = %s\n",mmsinfo.get_info[i].mmsdate);
				mmsinfo.get_info[i].typeId = mmstmpinfo->get_info[i].typeId;
				//				printf("mmstypeId = %d\n",mmsinfo.get_info[i].typeId);
			}
			OVERSIGN = 1;
			REFRESHSIGN  = CMD_MMS;
			SEND_CMD = 0; 
			break;

		default:
			break;
	}
}


send_pack()
{
	int ret = 0;
	char sig_start = 0x77;
	ret = dtcmr_send(sockfd, &sig_start, 1);
	ret = dtcmr_send(sockfd, &sig_start, 1);
	ret = dtcmr_send(sockfd, &sig_start, 1);
	ret = dtcmr_send(sockfd, &sig_start, 1);

	printf("send_pack SEND_CMD = %x\n",SEND_CMD);
	switch(SEND_CMD)
	{
		case CMD_MMS:
			printf("asking resend mmsinfo\n");
			ret = dtcmr_send(sockfd, &SEND_CMD, 1);
			SEND_CMD = 0;
			break;
		case CMD_IMAGE:
			printf("asking resend imageinfo\n");
			ret = dtcmr_send(sockfd, &SEND_CMD, 1);
			SEND_CMD = 0;
			break;
		case CMD_BOOK:
			printf("asking resend bookinfo\n");
			ret = dtcmr_send(sockfd, &SEND_CMD, 1);
			SEND_CMD = 0;
		case CMD_APP:
			printf("asking resend appinfo\n");
			ret = dtcmr_send(sockfd, &SEND_CMD, 1);
			SEND_CMD = 0;
			break;
		case CMD_CALLPHONE:
			printf("asking call phone%s\n",sendmessage.mmsnumber);
			ret = dtcmr_send(sockfd, &SEND_CMD, 1);

			SIZE = sizeof(sendmessage.mmsnumber);
			memcpy(tosize,&SIZE,4);
			ret = dtcmr_send(sockfd, tosize, 4);
			ret = dtcmr_send(sockfd,&(sendmessage.mmsnumber),sizeof(sendmessage.mmsnumber));
			SEND_CMD = 0;

			printf("int sizeof = %d\n",sizeof(int));
			printf("char sizeof = %d\n",sizeof(char));
			break;
		case CMD_SENDMMS:
			printf("asking resend sendmms %s,%s\n",sendmessage.mmsnumber,sendmessage.mmsdata);
			ret = dtcmr_send(sockfd, &SEND_CMD, 1);

			SIZE = sizeof(sendmessage_t);
			memcpy(tosize,&SIZE,4);
			ret = dtcmr_send(sockfd, tosize, 4);
			ret = dtcmr_send(sockfd,&sendmessage,sizeof(sendmessage_t));
			SEND_CMD = 0;

			printf("int sizeof = %d\n",sizeof(int));
			printf("char sizeof = %d\n",sizeof(char));
			break;

		default :
			break;
	}
}



int regetinfo(int argc)
{
	printf("regetinfo SEDN_CMD = %d\n",argc);
	SEND_CMD = argc;
	sem_post(&reget[1]);
	sleep(1);
	return 0;
}

void exit_sock()
{
	for(i = 0; i < 10; i++)
	{
		sem_destroy(&reget[i]);
	}
	pthread_mutex_destroy(&net_mutex);
	close_sockfd(sockfd);
}

int amservicestart() 
{

	pthread_mutex_init(&net_mutex, NULL);
	seminit();

	sockfd = dtcmr_client_creat("127.0.0.1",12580, IPPROTO_TCP);
	if (sockfd<0){
		printf("dtcmr_client_creat is error\n");	
		return -1;
	}
	memset(sddata,2,1024);

	send_pthread_init();

	while(1)
	{
		pthread_mutex_lock(&net_mutex);
		printf("while recv_pack\n");
		recv_pack();
		pthread_mutex_unlock(&net_mutex);
		usleep(5000);
	}
}

void* send_pthread(void* arg) 
{
	while(1)
	{
		printf("wait mutex unlock\n");
		pthread_mutex_lock(&net_mutex);
		sem_wait(&reget[1]);
		printf("get reget[1] sem\n");
		send_pack();
		pthread_mutex_unlock(&net_mutex);
		usleep(5000);

	}
}



int send_pthread_init()
{

	if (!pthread_attr_init(&sendthread.tattr)) {
		if (!pthread_attr_setdetachstate(&sendthread.tattr, PTHREAD_CREATE_DETACHED)) {
			pthread_create(&sendthread.tid, &sendthread.tattr, send_pthread, NULL);
			pthread_attr_destroy(&sendthread.tattr);
		} else {
			return -1;
		}	
	} else {
		return -1;
	}

	return 0;
}



void cleansig()
{
	SEND_CMD = 0;
	OVERSIGN = 0;
	REFRESHSIGN = 0;
}
